#include <stdio.h>

const int MAX_CHARS = 10000;

int main(int argc, char *argv[]) {
	if (argc >= 2) { // Path if at least 1 argument is passed
		FILE *fp;
		char str[MAX_CHARS]; // Internal buffer of 10k characters at a time
		for (int i = 1; i < argc; i++) { // Iterate through all passed files
			fp = fopen(argv[i], "r");
			if (fp == NULL) { // Passed file verification
				printf("wcat: cannot open file\n");
				return 1;
			}
			while(fgets(str, MAX_CHARS, fp)) { // Reads from file until EOF
				printf("%s", str);
			}
			fclose(fp);
		}
		return 0;
	} else { // Path is no argument is passed
		printf("wcat: file [file ...]\n");
		return 1;
	}
}
