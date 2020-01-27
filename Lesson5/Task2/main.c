#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void getfuncs(char *cComLine);

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Without options\n");
        exit(0);
    }
    getfuncs(argv[1]);
    return 0;
}

void getfuncs(char *cComLine) {
    char *buffer = NULL;
    for (int i = 0, start = 0; cComLine[i] != '\0'; i++) {
        if (cComLine[i] == ';') {
            buffer = (char *) realloc(buffer, (i - start + 1) * sizeof(char));
            strncpy(buffer, cComLine + start, i - start);
            printf("%s%i\n", "Exit code = ", system(buffer));
            start = i + 1;
            free(buffer);
        }
    }
    free(buffer);
}