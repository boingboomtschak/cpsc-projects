#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <unistd.h>

struct Block {
    char *ptr;
    int size;
};

void *consumer(void *param);

sem_t *sem_pool; // semaphore pool for threads
sem_t mutex, block_mutex; // mutex for stdout
struct Block *block; // blocks for passing to threads
int files; // number of files to process

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        int proc = get_nprocs_conf(); // number of configured processors
        char *src; // pointer to mmapped file
        char *l; // for checking if block boundaries split runs
        struct stat src_stat; // fstat buffer for file
        int err, fd, i, block_size, l_offset, b_offset; // error, file descriptor, index
        pthread_t *tid; // thread pool pointer
        size_t mem_tid = sizeof(pthread_t)*proc; // thread pool size
        size_t mem_sem_pool = sizeof(sem_t)*proc; // semaphore pool size
        size_t mem_block = sizeof(struct Block)*proc; // Block pool size
        files = argc - 1;

        // Initializing mutex, allocating blocks
        sem_init(&mutex, 0, 1);
        sem_init(&block_mutex, 0, 1);
        block = (struct Block *)malloc(mem_block);

        // Initializing and allocating semaphore pool
        sem_pool = (sem_t *)malloc(mem_sem_pool);
        for (i = 0; i < proc; i++) {
            sem_init(&sem_pool[i], 0, 0);
        }

        // Initializing and allocating thread pool
        tid = (pthread_t *)malloc(mem_tid);
        for (i = 0; i < proc; i++) {
            pthread_create(&tid[i], NULL, consumer, (void *) (intptr_t)i);
            pthread_detach(tid[i]);
        }

        // Working through each file passed in argv
        for (i = 1; i < argc; i++) {
            // Attempt to open file for reading
            fd = open(argv[i], O_RDWR);
            if (fd < 0) {
                perror("pzip: could not open file");   
                exit(EXIT_FAILURE);
            }

            // Attempt to read file information with fstat
            err = fstat(fd, &src_stat);
            if (err < 0) {
                perror("pzip: could not open file");
                exit(EXIT_FAILURE);
            }
            block_size = src_stat.st_size / proc;
            
            // Attempting to map fd into memory
            src = mmap(NULL, src_stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
            if (src == MAP_FAILED) {
                perror("pzip: failed to map file into memory");
                exit(EXIT_FAILURE);
            }
            close(fd);

            // Starting threads with blocks of file
            b_offset = 0;
            for (i = 0; i < proc; i++) {
                if (i < proc - 1) {
                    l_offset = 0;
                    l = src + b_offset + block_size;
                    while (*l == *(l + 1)) {
                        l_offset++;
                        l++;
                    }
                    block[i].ptr = src + b_offset;
                    block[i].size = block_size + l_offset;
                    fprintf(stderr, "thread %d at block offset %d with block size %d and l_offset %d\n", i, b_offset, block_size + l_offset, l_offset);
                    b_offset += (block_size + l_offset);
                } else {
                    block[i].ptr = src + b_offset;
                    block[i].size = src_stat.st_size - (i * block_size);
                    fprintf(stderr, "final thread %d at block offset %d with block size %lu and l_offset %d\n", i, b_offset, src_stat.st_size - (i * block_size), l_offset);
                }
                sem_post(&sem_pool[i]);
            }

            // Coordinating thread output to stdout
            for (i = 0; i < proc; i++) {
                sem_wait(&mutex);
                sem_post(&sem_pool[i]);
            }
           
            // Attempting to unmap fd from memory
            err = munmap(src, src_stat.st_size);
            if(err < 0) {
                perror("pzip: failed to unmap file from memory");
                exit(EXIT_FAILURE);
            }
        }

        // Destroy semaphores in semaphore pool and mutex
        for (i = 0; i < proc; i++) {
            sem_destroy(&sem_pool[i]);
        }
        sem_destroy(&mutex);

        // Free semaphore pool, thread pool and block
        free(sem_pool);
        free(tid);
        free(block);

        exit(EXIT_SUCCESS);
    } else {
        printf("pzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    }
}

void *consumer(void *param) {
    char *b;
    char *char_buf;
    uint32_t *uint_buf;
    size_t mem_uint_buf, mem_char_buf;
    char run;
    int run_len, b_size, f, i, buf_i;
    int n = (intptr_t )param;
    for (f = 0; f < files; f++) {
        // Wait for first sem signal to consume block 
        sem_wait(&sem_pool[n]);

        sem_wait(&block_mutex);
        // Consume block
        b = block[n].ptr;
        b_size = block[n].size;
        sem_post(&block_mutex);

        // Allocate buffers for worst case scenario (one run for each character in the block)
        mem_uint_buf = sizeof(uint32_t)*b_size;
        uint_buf = (uint32_t *)malloc(mem_uint_buf);
        mem_char_buf = sizeof(char)*b_size;
        char_buf = (char *)malloc(mem_char_buf);
        buf_i = 0;

        // Calculate runs and write to buffers
        run = b[0];
        run_len = 1;
        for (i = 1; i < b_size; i++) {
            if (b[i] == run) {
                run_len++;
            } else {
                uint_buf[buf_i] = run_len;
                char_buf[buf_i] = run;
                buf_i++;
                run = b[i];
                run_len = 1;
            }
        } 

        // Wait for second sem signal to write to stdout
        sem_wait(&sem_pool[n]);

        // Write from buffer to stdout
        for (i = 0; i < buf_i; i++) {
            fwrite(&uint_buf[i], sizeof(uint32_t), 1, stdout);
            fwrite(&char_buf[i], sizeof(char), 1, stdout);
        }
        
        // Free buffers, post to mutex to allow more writes to stdout
        free(uint_buf);
        free(char_buf);
        sem_post(&mutex);
    }
    pthread_exit(NULL);
}
