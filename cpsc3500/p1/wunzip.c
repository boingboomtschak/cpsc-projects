#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        FILE *fp;
        char run;
        uint32_t run_len;
        for (int i = 1; i < argc; i++) { // Iterate through all passed files
            fp = fopen(argv[i], "r");
            if (fp == NULL) { // Passed file verification
                printf("wunzip: cannot open file\n");
                return 1;
            }       
            while (fread(&run_len, sizeof(uint32_t), 1, fp) == 1) { // Read until fread() for run length reads single byte (usually EOF) instead of 4 bytes
                fread(&run, sizeof(char), 1, fp);
                for (int i = 0; i < run_len; i++) { // Write run char to stdout run_len # of times
                    putc(run, stdout); 
                }
            }
            fclose(fp);
        }
        return 0;
    } else {
        printf("wunzip: file1 [file2...]\n");
        return 1;
    }
}