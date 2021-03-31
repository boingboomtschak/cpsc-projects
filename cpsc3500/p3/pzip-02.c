#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <unistd.h>

#define BLOCK_SIZE 16384

struct Block {
    char *ptr;
    int size;
    int num;
};

struct ThreadInfo {
    struct Block *block;
    int stay_alive;
};

void *consumer(void *param);

sem_t mutex, bready, bwritex, breadx, open_threads;
// mutex : locks stdout so multiple threads don't write at once
// bready : causes threads to wait until a block is ready
// bwritex / breadx : locks read + write of block so main thread writes dont interfere with thread reads
// open_threads : tracks open threads so file is not unmapped before threads finish with file
atomic_int block_cur; // keeps track of current block to output (stdout coordination)

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        int proc = get_nprocs_conf(); // # of configured processors
        int err, fd, i, b, t, blocks; 
        char *src; // pointer for mmapped file
        struct stat src_stat; // stat struct for file info
        struct ThreadInfo *thread_info; // info for thread
        pthread_t *tid; // thread pool pointer
        size_t mem_tid = sizeof(pthread_t)*proc; // size of thread pool
        size_t mem_thread_info = sizeof(struct ThreadInfo); // size of thread info
        size_t mem_block = sizeof(struct Block); // size of block

        // Initialize all semaphores
        sem_init(&mutex, 0, 1);
        sem_init(&bready, 0, 0);
        sem_init(&bwritex, 0, 1);
        sem_init(&breadx, 0, 0);
        sem_init(&open_threads, 0, 0);

        // Initialize thread info struct
        thread_info = malloc(mem_thread_info);
        thread_info->block = malloc(mem_block);
        thread_info->stay_alive = 1;

        // Allocate thread pool, create threads, and pass thread info to newly-created threads
        tid = (pthread_t *)malloc(mem_tid);
        for(i = 0; i < proc; i++) {
            pthread_create(&tid[i], NULL, consumer, (void *) thread_info);
        }

        // Work on each file in argv[]
        for (i = 1; i < argc; i++) {
            // Open file and save file descriptor
            fd = open(argv[i], O_RDWR);
            if (fd < 0) {
                perror("pzip: could not open file");
                exit(EXIT_FAILURE);
            }

            // fstat to check file size for mmap
            err = fstat(fd, &src_stat);
            if (err < 0) {
                perror("pzip: could not open file");
                exit(EXIT_FAILURE);
            }

            // mmap file into memory and close file descriptor
            src = mmap(NULL, src_stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
            if (src == MAP_FAILED) {
                perror("pzip: failed to map file into memory");
                exit(EXIT_FAILURE);
            }
            close(fd);

            // Split file into blocks (pointers to sections of mmapped file) and pass to threads
            block_cur = 1;
            thread_info->block->num = 0;
            blocks = 0;
            for (b = 0; b < src_stat.st_size; b += BLOCK_SIZE) {
                // Wait for write lock to be released (no threads are using block)
                sem_wait(&bwritex);
                if ((b + BLOCK_SIZE) <= src_stat.st_size) {
                    
                    thread_info->block->ptr = src + b;
                    thread_info->block->size = BLOCK_SIZE;
                    thread_info->block->num++;

                } else {
                    thread_info->block->ptr = src + b;
                    thread_info->block->size = src_stat.st_size - b;
                    thread_info->block->num++;
                }
                // Unlock block for threads to read
                sem_post(&breadx);
                // Post new block for threads
                sem_post(&bready);
                blocks++;
            }

            // Wait until there are no more threads accessing the fille
            for(t = 0; t < blocks; t++) {
                sem_wait(&open_threads);
            }

            // Unmap file from memory
            err = munmap(src, src_stat.st_size);
            if(err < 0) {
                perror("pzip: failed to unmap file from memory");
                exit(EXIT_FAILURE);
            }
        }

        // After all files are finished, turn off flag to keep threads alive and post to bready to update threads
        thread_info->stay_alive = 0;
        for(i = 0; i < proc; i++) {
            sem_post(&bready);
        }

        // Wait for all threads to finish exiting
        for(i = 0; i < proc; i++) {
            pthread_join(tid[i], NULL);
        }
        
        // Destroy all semaphores
        sem_destroy(&mutex);
        sem_destroy(&bready);
        sem_destroy(&bwritex);
        sem_destroy(&breadx);

        // Free block, then thread info, then thread pool
        free(thread_info->block);
        free(thread_info);
        free(tid);

        // Exit
        exit(EXIT_SUCCESS);
    } else {
        printf("pzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }
}

void *consumer(void *param) {
    struct ThreadInfo *thread_info = (struct ThreadInfo *) param; 
    char *b; // pointer for block section in file
    char *char_buf; // char buffer
    char r; // current "run"
    uint32_t *uint_buf; // 4-byte int buffer
    int b_size, i, r_len, buf_i, b_num; // block size, i, run length, buffer i, block num

    // Allocating buffers for uint and char buffers
    size_t mem_uint_buf = sizeof(uint32_t)*BLOCK_SIZE;
    size_t mem_char_buf = sizeof(char)*BLOCK_SIZE;
    uint_buf = malloc(mem_uint_buf);
    char_buf = malloc(mem_char_buf);

    // Run until "stay alive" flag is turned off 
    while(1) {
        // Wait until block is ready
        sem_wait(&bready);
        
        // Exit if thread should be released
        if (!thread_info->stay_alive) {
            break;
        }

        // Wait until read lock released
        sem_wait(&breadx);
        
        // Consume block data
        b = thread_info->block->ptr;
        b_size = thread_info->block->size;
        b_num = thread_info->block->num;

        // Unlock block for writes
        sem_post(&bwritex);

        // Process block
        buf_i = 0;
        r = b[0];
        r_len = 1;
        for (i = 1; i <= b_size; i++) {
            if (b[i] == r) {
                r_len++;
            } else {
                uint_buf[buf_i] = r_len;
                char_buf[buf_i] = r;
                buf_i++;
                r = b[i];
                r_len = 1;
            }
        }

        
        // Lock mutex when released, if buffered block is not current block, release mutex
        while(1) {
            sem_wait(&mutex);
            if (block_cur != b_num) {
                sem_post(&mutex);
            } else {
                break;
            }
        }

        // Write buffers to stdout, iterate current block (atomically)
        for (i = 0; i < buf_i; i++) {
            fwrite(&uint_buf[i], sizeof(uint32_t), 1, stdout);
            fwrite(&char_buf[i], sizeof(char), 1, stdout);
        }
        block_cur++;
        
        // Release mutex, release lock on open file
        sem_post(&mutex);
        sem_post(&open_threads);
    }

    // Free buffers, exit thread
    free(uint_buf);
    free(char_buf);
    pthread_exit(NULL);
}
