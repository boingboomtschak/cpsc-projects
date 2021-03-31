// Program includes
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Program defines
#define MAX_COMMANDS 10
#define MAX_COMMAND_TOKENS 20
#define MAX_TOKEN_LENGTH 20
#define PIPE_DELIM "|"
#define PROMPT "myshell$"

// Trims leading and trailing whitespace from char* (modifies given char*)
char *trim_string(char *str);

int main() {
    int i;
    int sfd[2] = {dup(0), dup(1)}; // saving stdin/stdout file descriptors for restoration later
    int cmd_err = 0; // flag in case there is an error executing commands
    char *s; // string input buffer
    char **cmds; // command buffer
    int cmds_n = 0; 
    size_t mem_s = sizeof(char)*MAX_COMMANDS*MAX_COMMAND_TOKENS*MAX_TOKEN_LENGTH;
    size_t mem_cmds = sizeof(void *)*MAX_COMMANDS;
    pid_t pid;

    // Allocating buffer for command input and command pointers
    s = (char *)malloc(mem_s);
    cmds = (char **)malloc(mem_cmds);

    // Checking for failed malloc
    if(s == NULL || cmds == NULL) {
        perror("failed to allocate memory");
        exit(1);
    }

    printf(PROMPT);
    
    // Read to string buffer from stdin, error if overflow
    if (fgets(s, mem_s, stdin) == NULL) { 
        perror("input larger than string buffer");
        exit(1);
    }
    
    // Separate commands by "|" character 
    char *s_buf = s; // Retain original pointer to free() later
    while ((*(cmds+cmds_n) = strsep(&s_buf, PIPE_DELIM)) != NULL) {
        cmds_n++;
    }
    
    // Iterate through commands, fork and execute
    for (i = 0; i < cmds_n; i++) {
        // Trim whitespace from head and tail of commands
        cmds[i] = trim_string(cmds[i]);
        
        // Create pipe from fd[]
        int fd[2];
        if (pipe(fd) < 0) {
            perror("failed to create pipe");
            cmd_err = 1;
        }

        // If last command, redirect stdout to stdout file descriptor saved at beginning, otherwise redirect to pipe write end
        if (i == (cmds_n - 1)) {
            if (dup2(sfd[1], 1) < 0) {
                perror("error redirecting stdout");
                cmd_err = 1;
            }
            close(sfd[1]);
        } else {
            if (dup2(fd[1], 1) < 0) {
                perror("error redirecting stdout");
                cmd_err = 1;
            }
            close(fd[1]);
        }

        // Fork process 
        pid = fork();

        if (pid == 0) {
            // In child process
            char *cmd_buf = cmds[i]; 
            char **tokens; // token buffer
            int tokens_n = 0; 
            size_t mem_tokens = sizeof(void *)*MAX_COMMAND_TOKENS;
            
            // Allocating buffer for pointers to command tokens
            tokens = (char **)malloc(mem_tokens);

            // Separate command tokens by " " character
            while((*(tokens+tokens_n) = strsep(&cmd_buf, " ")) != NULL) {
                tokens_n++;
            }
            
            char **tokens_cp = tokens;
            // Verify execvp() call returned with valid exit code
            if(execvp(tokens[0], tokens) < 0) {
                perror("child process failed");
                exit(1);
            }               

            // Child process ends - char **tokens is freed by OS because child process ends due to execvp(), is freed manually if not
        } else if(pid > 0) {
            // In parent process
            int status;
            pid_t rec_pid; // pid received from wait()

            // Waiting for each child within the cmd iteration loop ensures they execute in the correct order
            while((rec_pid = wait(&status)) != pid) {
                if(rec_pid == -1) {
                    perror("waiting for child process failed");
                    cmd_err = 1;
                }
            }

            if (WEXITSTATUS(status) == 1) {
                cmd_err = 1;
            }

            // Printing exit pids and statuses to stderr so they don't interfere with the output from commands
            fprintf(stderr, "[%d] exited with code %d\n", rec_pid, WEXITSTATUS(status)); 
        } else {
            perror("failed to create fork");
            exit(1);
        }

        // Redirect stdin to pipe read end for next command, close file descriptor so it can be reused
        if (dup2(fd[0], 0) < 0) {
            perror("error redirecting stdout");
            cmd_err = 1;
        }
        close(fd[0]);
    }

    // Cleanup, cleanup, everybody cleanup
    free(s); 
    free(cmds); // Only need to free cmds as elements of cmds[i] are pointers to original string

    // Main program should exit with code 1 if there was an error executing a command
    if(cmd_err) {
        exit(1);
    } else {
        exit(0);
    }
}

char *trim_string(char *str) {
    char *tail;
    // Move head pointer forward until non-whitespace character
    while(isspace((unsigned char) *str)) { 
        str++;
    }

    // If string is all whitespace, return
    if(*str == 0) { return str; }

    // Move tail pointer backwards until non-whitespace character encountered, then null-terminate string
    tail = str + strlen(str) - 1; 
    while(tail > str && isspace((unsigned char) *tail)) { tail--; }
    tail[1] = '\0';
    return str;
}