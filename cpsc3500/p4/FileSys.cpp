// CPSC 3500: File System
// Implements the file system commands that are available to the shell.

#include <cstring>
#include <iostream>
#include <unistd.h>
using namespace std;

#include "FileSys.h"
#include "BasicFileSys.h"
#include "Blocks.h"

bool is_directory(void *block);



// mounts the file system
void FileSys::mount(int sock) {
  bfs.mount();
  curr_dir = 1; //by default current directory is home directory, in disk block #1
  fs_sock = sock; //use this socket to receive file system operations from the client and send back response messages
}



// unmounts the file system
void FileSys::unmount() {
  bfs.unmount();
  close(fs_sock);
}



// make a directory
void FileSys::mkdir(const char *name) {
  int i;
  char s[64];

  // Checking if file name is short enough
  if (strlen(name) > MAX_FNAME_SIZE) {
    sprintf(s, "504 File name is too long\r\n");
    write(fs_sock, &s, strlen(s));
    sprintf(s, "Length:0\r\n\r\n");
    write(fs_sock, &s, strlen(s));
    return;
  } 

  // Read current dir, check if there is space in dir
  struct dirblock_t curr;
  bfs.read_block(curr_dir, &curr);
  if (curr.num_entries >= MAX_DIR_ENTRIES) {
    sprintf(s, "506 Directory is full\r\n");
    write(fs_sock, &s, strlen(s));
    sprintf(s, "Length:0\r\n\r\n");
    write(fs_sock, &s, strlen(s));
    return;
  }

  // Check if name already taken in current dir
  for (i = 0; i < curr.num_entries; i++) {
    if (strcmp(curr.dir_entries[i].name, name) == 0) {
      sprintf(s, "502 File exists\r\n");
      write(fs_sock, &s, strlen(s));
      sprintf(s, "Length:0\r\n\r\n");
      write(fs_sock, &s, strlen(s));
      return;
    }
  }

  // Grab free block, check if disk is full
  short b_num = bfs.get_free_block();
  if (b_num == 0) {
    sprintf(s, "505 Disk is full\r\n");
    write(fs_sock, &s, strlen(s));
    sprintf(s, "Length:0\r\n\r\n");
    write(fs_sock, &s, strlen(s));
    return;
  }
  
  // Create and initialize struct for dirblock and write to disk
  dirblock_t dir;
  dir.magic = DIR_MAGIC_NUM;
  dir.num_entries = 0;
  for (i = 0; i < MAX_DIR_ENTRIES; i++) {
    dir.dir_entries[i].block_num = 0;
  }
  bfs.write_block(b_num, &dir);

  // Add grabbed block to curr dir entries
  strcpy(curr.dir_entries[curr.num_entries].name, name);
  curr.dir_entries[curr.num_entries].block_num = b_num;
  curr.num_entries++;

  // Rewrite curr back to disk
  bfs.write_block(curr_dir, &curr);

  // Write success code if no errors
  sprintf(s, "200 OK\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:0\r\n\r\n");
  write(fs_sock, &s, strlen(s));
  return;
}



// switch to a directory
void FileSys::cd(const char *name) {
  int i;
  char s[64];
  struct dirblock_t curr, cdir;

  // Reading current directory
  bfs.read_block(curr_dir, &curr);
  
  for (i = 0; i < curr.num_entries; i++) {
    if (strcmp(curr.dir_entries[i].name, name) == 0) {
      // Read block of matching name
      bfs.read_block(curr.dir_entries[i].block_num, &cdir);

      // Check if name-matching block is directory
      if (!is_directory(&cdir)) {
        sprintf(s, "500 File is not a directory\r\n");
        write(fs_sock, &s, strlen(s));
        sprintf(s, "Length:0\r\n\r\n");
        write(fs_sock, &s, strlen(s));
        return;
      }

      // Set current directory to block number of new dir
      curr_dir = curr.dir_entries[i].block_num;

      // Write success code if no errors
      sprintf(s, "200 OK\r\n");
      write(fs_sock, &s, strlen(s));
      sprintf(s, "Length:0\r\n\r\n");
      write(fs_sock, &s, strlen(s));
      return;
    }
  }

  // If no matches, file does not exist
  sprintf(s, "503 File does not exist\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:0\r\n\r\n");
  write(fs_sock, &s, strlen(s));
  return;
}



// switch to home directory
void FileSys::home() {
  // Change current directory to home directory
  char s[64];
  curr_dir = 1;

  // Write success code if no errors
  sprintf(s, "200 OK\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:0\r\n\r\n");
  write(fs_sock, &s, strlen(s));
  return;
}



// remove a directory
void FileSys::rmdir(const char *name) {
  int i, j;
  char s[64];
  struct dirblock_t curr, rdir;

  // Reading current directory block
  bfs.read_block(curr_dir, &curr);
  
  for (i = 0; i < curr.num_entries; i++) {
    if (strcmp(curr.dir_entries[i].name, name) == 0) {
      // Read block of matching name
      bfs.read_block(curr.dir_entries[i].block_num, &rdir);

      // Check if name-matching block is directory
      if (!is_directory(&rdir)) {
        sprintf(s, "500 File is not a directory\r\n");
        write(fs_sock, &s, strlen(s));
        sprintf(s, "Length:0\r\n\r\n");
        write(fs_sock, &s, strlen(s));
        return;
      }

      // Check directory empty
      if (rdir.num_entries != 0) {
        sprintf(s, "507 Directory is not empty\r\n");
        write(fs_sock, &s, strlen(s));
        sprintf(s, "Length:0\r\n\r\n");
        write(fs_sock, &s, strlen(s));
        return;
      }

      // Reclaim block, lower curr dir num entries and shift dir_entries entries back
      bfs.reclaim_block(curr.dir_entries[i].block_num);
      for (j = i + 1; j < curr.num_entries; j++) {
        curr.dir_entries[j - 1] = curr.dir_entries[j];
      }
      curr.num_entries--;

      // Rewrite curr back to disk
      bfs.write_block(curr_dir, &curr);

      // Write success code if no errors
      sprintf(s, "200 OK\r\n");
      write(fs_sock, &s, strlen(s));
      sprintf(s, "Length:0\r\n\r\n");
      write(fs_sock, &s, strlen(s));
      return;
    }
  }

  // If no matches, file does not exist
  sprintf(s, "503 File does not exist\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:0\r\n\r\n");
  write(fs_sock, &s, strlen(s));
  return;
}



// list the contents of current directory
void FileSys::ls() {
  int i;
  int buf_i = 0;
  struct dirblock_t curr, lsblk;
  char buf[MAX_DIR_ENTRIES * (MAX_FNAME_SIZE + 2) + 2];
  char s[64];
  memset(&buf, '\0', sizeof(buf));


  // Read current directory block
  bfs.read_block(curr_dir, &curr);

  for (i = 0; i < curr.num_entries; i++) {
    // Read block (need to check if directory or file)
    bfs.read_block(curr.dir_entries[i].block_num, &lsblk);

    // Add name and slash of each file/dir to buffer
    strcat(buf, curr.dir_entries[i].name);
    if (is_directory(&lsblk)) {
      strcat(buf, "/ ");
    } else {
      strcat(buf, " ");
    }
  }

  // Write success code if no errors
  sprintf(s, "200 OK\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:%lu\r\n\r\n", strlen(buf));
  write(fs_sock, &s, strlen(s));
  write(fs_sock, &buf, strlen(buf));
  return;
}



// create an empty data file
void FileSys::create(const char *name) {
  int i;
  char s[64];
  struct dirblock_t curr;
  struct inode_t dfile;

  // Checking if file name is short enough
  if (strlen(name) > MAX_FNAME_SIZE) {
    sprintf(s, "504 File name is too long\r\n");
    write(fs_sock, &s, strlen(s));
    sprintf(s, "Length:0\r\n\r\n");
    write(fs_sock, &s, strlen(s));
    return;
  } 

  // Reading current directory
  bfs.read_block(curr_dir, &curr);

  // Checking if directory is full
  if (curr.num_entries >= MAX_DIR_ENTRIES) {
    sprintf(s, "506 Directory is full\r\n");
      write(fs_sock, &s, strlen(s));
      sprintf(s, "Length:0\r\n\r\n");
      write(fs_sock, &s, strlen(s));
    return;
  }

  // Checking if file exists
  for (i = 0; i < curr.num_entries; i++) {
    if (strcmp(curr.dir_entries[i].name, name) == 0) {
      sprintf(s, "502 File exists\r\n");
      write(fs_sock, &s, strlen(s));
      sprintf(s, "Length:0\r\n\r\n");
      write(fs_sock, &s, strlen(s));
      return;
    }
  }

  // Grabbing next free block from disk
  short b_num = bfs.get_free_block();
  if (b_num == 0) {
    sprintf(s, "505 Disk is full\r\n");
    write(fs_sock, &s, strlen(s));
    sprintf(s, "Length:0\r\n\r\n");
    write(fs_sock, &s, strlen(s));
    return;
  }

  // Setting up inode
  dfile.magic = INODE_MAGIC_NUM;
  dfile.size = 0;
  for (i = 0; i < MAX_DATA_BLOCKS; i++) {
    dfile.blocks[i] = 0;
  }

  // Adding inode to current directory
  strcpy(curr.dir_entries[curr.num_entries].name, name);
  curr.dir_entries[curr.num_entries].block_num = b_num;
  curr.num_entries++;

  // Writing current directory block back to disk
  bfs.write_block(curr_dir, &curr);

  // Writing inode to disk
  bfs.write_block(b_num, &dfile);

  // Write success code if no errors
  sprintf(s, "200 OK\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:0\r\n\r\n");
  write(fs_sock, &s, strlen(s));
  return;
}



// append data to a data file
void FileSys::append(const char *name, const char *data) {
  // 505 Disk is full
  int i, b;
  int block, block_i;
  char s[64];
  struct dirblock_t curr;
  struct inode_t inode;
  struct datablock_t dblock;

  // Loading current directory
  bfs.read_block(curr_dir, &curr);

  for (i = 0; i < curr.num_entries; i++) {
    if (strcmp(curr.dir_entries[i].name, name) == 0) {
      // Load name-matching file block into inode
      bfs.read_block(curr.dir_entries[i].block_num, &inode);

      // Check if appending file is a directory
      if(is_directory(&inode)) {
        sprintf(s, "501 File is a directory\r\n");
        write(fs_sock, &s, strlen(s));
        sprintf(s, "Length:0\r\n\r\n");
        write(fs_sock, &s, strlen(s));
        return;
      }

      // Check if append would exceed maximum file size
      if ((inode.size + sizeof(data)) >= MAX_FILE_SIZE) {
        sprintf(s, "508 Append exceeds maximum file size\r\n");
        write(fs_sock, &s, strlen(s));
        sprintf(s, "Length:0\r\n\r\n");
        write(fs_sock, &s, strlen(s));
        return;
      }

      block = inode.size / BLOCK_SIZE;
      block_i = inode.size - (block * BLOCK_SIZE);
      for (b = 0; b < strlen(data); b++) {
        // If next block is initialized, read it, otherwise zero out array
        if ((b % BLOCK_SIZE) == 0 && inode.blocks[block] == 0) {
          memset(&dblock.data, 0, BLOCK_SIZE);
        } else if((b % BLOCK_SIZE) == 0) {
          bfs.read_block(inode.blocks[block], &dblock);
        }
        // Write char from data to dblock
        dblock.data[block_i] = data[b];

        // If next block is not initialized, create and write it, otherwise just write
        if ((b % BLOCK_SIZE) == 0  && inode.blocks[block] == 0) {
          short b_num = bfs.get_free_block();
          if (b_num == 0) {
            sprintf(s, "505 Disk is full\r\n");
            write(fs_sock, &s, strlen(s));
            sprintf(s, "Length:0\r\n\r\n");
            write(fs_sock, &s, strlen(s));
            return;
          }
          bfs.write_block(b_num, &dblock);
          inode.blocks[block] = b_num;
          
        } else if ((b % BLOCK_SIZE) == 0) {
          bfs.write_block(inode.blocks[block], &dblock);
        }
        // Increment 
        block_i++;
        inode.size++;
      }

      bfs.write_block(inode.blocks[block], &dblock);

      // Write inode back to disk
      bfs.write_block(curr.dir_entries[i].block_num, &inode);

      // Write success code if no errors
      sprintf(s, "200 OK\r\n");
      write(fs_sock, &s, strlen(s));
      sprintf(s, "Length:0\r\n\r\n");
      write(fs_sock, &s, strlen(s));
      return;
    }
  }

  // If no matches, file does not exist
  sprintf(s, "503 File does not exist\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:0\r\n\r\n");
  write(fs_sock, &s, strlen(s));
  return;
}



// display the contents of a data file
void FileSys::cat(const char *name) {
  int i, j, blk, size, buf_i;
  char buf[MAX_FILE_SIZE];
  char s[64];
  struct dirblock_t curr;
  struct inode_t inode;
  struct datablock_t dblock;
  memset(&buf, '\0', sizeof(buf));

  // Reading current directory
  bfs.read_block(curr_dir, &curr);

  for (i = 0; i < curr.num_entries; i++) {
    if (strcmp(curr.dir_entries[i].name, name) == 0) {
      // Reading name-matching block into inode
      bfs.read_block(curr.dir_entries[i].block_num, &inode);

      // Checking if file is directory
      if (is_directory(&inode)) {
        sprintf(s, "501 File is a directory\r\n");
        write(fs_sock, &s, strlen(s));
        sprintf(s, "Length:0\r\n\r\n");
        write(fs_sock, &s, strlen(s));
        return;
      }
      
      buf_i = 0;
      blk = 0;
      size = inode.size;
      bfs.read_block(inode.blocks[blk], &dblock);
      for (j = 0; j < size; j++) {
        if(j % BLOCK_SIZE == 0 && j != 0 && size - BLOCK_SIZE > 0) {
          j = 0;
          size -= BLOCK_SIZE;
          blk++;
          bfs.read_block(inode.blocks[blk], &dblock);
        }
        buf[buf_i] = dblock.data[j];
        buf_i++;
      }
      buf[buf_i] = '\0';

      // Write success code if no errors
      sprintf(s, "200 OK\r\n");
      write(fs_sock, &s, strlen(s));
      sprintf(s, "Length:%lu\r\n\r\n", strlen(buf));
      write(fs_sock, &s, strlen(s));
      write(fs_sock, &buf, strlen(buf));
      return;
    }
  }
  // If no matches, file does not exist
  sprintf(s, "503 File does not exist\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:0\r\n\r\n");
  write(fs_sock, &s, strlen(s));
  return;
}



// display the first N bytes of the file
void FileSys::head(const char *name, unsigned int n) {
  int i, j, buf_i, blk, size;
  char buf[MAX_FILE_SIZE];
  char s[64];
  struct dirblock_t curr;
  struct inode_t inode;
  struct datablock_t dblock;
  memset(&buf, '\0', sizeof(buf));

  // Reading current directory
  bfs.read_block(curr_dir, &curr);

  for (i = 0; i < curr.num_entries; i++) {
    if (strcmp(curr.dir_entries[i].name, name) == 0) {
      // Reading name-matching block into inode
      bfs.read_block(curr.dir_entries[i].block_num, &inode);

      // Checking if file is directory
      if (is_directory(&inode)) {
        sprintf(s, "501 File is a directory\r\n");
        write(fs_sock, &s, strlen(s));
        sprintf(s, "Length:0\r\n\r\n");
        write(fs_sock, &s, strlen(s));
        return;
      }

      // Read n bytes from inode's datablocks into buf
      buf_i = 0;
      blk = 0;
      size = inode.size;
      bfs.read_block(inode.blocks[blk], &dblock);
      for (j = 0; j < n; j++) {
        if(j % BLOCK_SIZE == 0 && j != 0 && size - BLOCK_SIZE > 0) {
          j = 0;
          size -= BLOCK_SIZE;
          blk++;
          bfs.read_block(inode.blocks[blk], &dblock);
        }
        buf[buf_i] = dblock.data[j];
        buf_i++;
      }
      buf[buf_i] = '\0';

      // Write success code if no errors
      sprintf(s, "200 OK\r\n");
      write(fs_sock, &s, strlen(s));
      sprintf(s, "Length:%lu\r\n\r\n", strlen(buf));
      write(fs_sock, &s, strlen(s));
      write(fs_sock, &buf, strlen(buf));
      return;
    }
  }

  // If no matches, file does not exist
  sprintf(s, "503 File does not exist\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:0\r\n\r\n");
  write(fs_sock, &s, strlen(s));
  return;
}



// delete a data file
void FileSys::rm(const char *name) {
  int i, j;
  char s[64];
  struct dirblock_t curr;
  struct inode_t rfile;

  // Loading current directory
  bfs.read_block(curr_dir, &curr);

  for (i = 0; i < curr.num_entries; i++) {
    if (strcmp(curr.dir_entries[i].name, name) == 0) {
      // Loading block to remove
      bfs.read_block(curr.dir_entries[i].block_num, &rfile);

      // Checking if file to remove is directory
      if (is_directory(&rfile)) {
        sprintf(s, "501 File is a directory\r\n");
        write(fs_sock, &s, strlen(s));
        sprintf(s, "Length:0\r\n\r\n");
        write(fs_sock, &s, strlen(s));
        return;
      }

      // Reclaiming all data blocks in file
      for (j = 0; j < rfile.size; j++) {
        bfs.reclaim_block(rfile.blocks[j]);
      }

      // Remove file from current directory
      for (j = i + 1; j < curr.num_entries; j++) {
        curr.dir_entries[j - 1] = curr.dir_entries[j];
      }
      curr.num_entries--;

      // Reclaim file block from disk
      bfs.reclaim_block(curr.dir_entries[i].block_num);

      // Write current dir back to disk
      bfs.write_block(curr_dir, &curr);

      // Write success code if no errors
      sprintf(s, "200 OK\r\n");
      write(fs_sock, &s, strlen(s));
      sprintf(s, "Length:0\r\n\r\n");
      write(fs_sock, &s, strlen(s));
      return;
    }
  }

  // If no matches, file does not exist
  sprintf(s, "503 File does not exist\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:0\r\n\r\n");
  write(fs_sock, &s, strlen(s));
  return;
}



// display stats about file or directory
void FileSys::stat(const char *name) {
  int i;
  char buf[256];
  char s[64];
  struct dirblock_t curr, sdir;
  struct inode_t sfile;

  // Fill buffer with null chars ('\0')
  memset(&buf, '\0', sizeof(buf));

  // Load current directory block
  bfs.read_block(curr_dir, &curr);

  for (i = 0; i < curr.num_entries; i++) {
    if (strcmp(curr.dir_entries[i].name, name) == 0) {
      // Read matching block into sfile at first
      bfs.read_block(curr.dir_entries[i].block_num, &sfile);

      // If block is actually a directory, read into sdir and return dir stats
      if (is_directory(&sfile)) {
        bfs.read_block(curr.dir_entries[i].block_num, &sdir);
        
        sprintf(s, "Directory name: %s/\n", curr.dir_entries[i].name);
        strcat(buf, s);
        sprintf(s, "Directory block: %u\n", curr.dir_entries[i].block_num);
        strcat(buf, s);

        // Write success code and dir stats
        sprintf(s, "200 OK\r\n");
        write(fs_sock, &s, strlen(s));
        sprintf(s, "Length:%lu\r\n\r\n", strlen(buf));
        write(fs_sock, &s, strlen(s));
        write(fs_sock, &buf, strlen(buf));
        return;
      }


      sprintf(s, "Inode block: %u\r\n", curr.dir_entries[i].block_num);
      strcat(buf, s);

      sprintf(s, "Bytes in file: %u\r\n", sfile.size);
      strcat(buf, s);

      sprintf(s, "Number of blocks: %u\r\n", (sfile.size + BLOCK_SIZE - 1) / BLOCK_SIZE);
      strcat(buf, s);

      if (sfile.size == 0) {
        sprintf(s, "First block: 0");
      } else {
        sprintf(s, "First block: %u", sfile.blocks[0]);
      }
      strcat(buf, s);

      // Write success code and file stats
      sprintf(s, "200 OK\r\n");
      write(fs_sock, &s, strlen(s));
      sprintf(s, "Length:%lu\r\n\r\n", strlen(buf));
      write(fs_sock, &s, strlen(s));
      write(fs_sock, &buf, strlen(buf));
      return;
    }
  }

  
  // If no matches, file does not exist
  sprintf(s, "503 File does not exist\r\n");
  write(fs_sock, &s, strlen(s));
  sprintf(s, "Length:0\r\n\r\n");
  write(fs_sock, &s, strlen(s));
  return;
}



// HELPER FUNCTIONS (optional)

bool FileSys::is_directory(void *block) {
  inode_t *b = (inode_t *) block;
  if (b->magic == DIR_MAGIC_NUM) {
    return true;
  } else {
    return false;
  }
}