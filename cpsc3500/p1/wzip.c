#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        FILE *fp;
        char c; // Current char being read
        char run; // Current char of "run"
        uint32_t run_len; // Run length stored in uint32_t to ensure 4 byte integer size
        for (int i = 1; i < argc; i++) { // Iterate through all passed files
            fp = fopen(argv[i], "r");
            if (fp == NULL) { // Passed file verification
                printf("wzip: cannot open file\n");
                return 1;
            }
            c = fgetc(fp);
            run = c;
            run_len = 1;
            while(c != EOF) { // Read char by char until EOF
                c = fgetc(fp);
                if (c == run) {
                    run_len++;
                } else {
                    fwrite(&run_len, sizeof(uint32_t), 1, stdout); // At end of run, write run length (4 byte int) and run (1 byte char) to stdout
                    fwrite(&run, sizeof(char), 1, stdout);
                    run = c;
                    run_len = 1;
                }
            }
            fclose(fp);
        }
        return 0;
    } else {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }
}