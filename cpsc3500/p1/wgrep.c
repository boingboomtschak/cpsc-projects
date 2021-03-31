#include <stdio.h>
#include <string.h>
#include <sys/types.h> 

const int BUF_CHARS = 10000;

int main(int argc, char *argv[]) {
    if (argc == 2) { // Path if only a searchterm is passed (no files)
        char buf[BUF_CHARS];
        while (fgets(buf, BUF_CHARS, stdin)) {
            if (strstr(buf, argv[1])) {
                printf("%s", buf);
            }
        }
        return 0;
    } else if (argc >= 3) { // Path if searchterm and files are passed
        FILE *fp;
        char *buf = NULL; // Buffer is pointer to char so getline can resize it as needed
        size_t buf_size = 0; // Buffer size is initialized to 0 so it is resized immediately on first line read
        ssize_t lsize; // signed size_t so getline can return -1 on EOF
        for (int i = 2; i < argc; i++) { // Iterate through all passed files
            fp = fopen(argv[i], "r");
            if (fp == NULL) { // Passed file verification
                printf("wgrep: cannot open file\n");
                return 1;
            }
            lsize = getline(&buf, &buf_size, fp);
            while(lsize >= 0) {
                if (strstr(buf, argv[1])) {
                    printf("%s", buf);
                }
                lsize = getline(&buf, &buf_size, fp);
            }
            fclose(fp);
        }
        return 0;
    } else {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }
}