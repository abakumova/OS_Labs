#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    printf("%s\n", argv[1]);
    char *file_name;
    if (getenv("FILE_NAME") != NULL) {
        file_name = malloc(sizeof(char) * (strlen(getenv("FILE_NAME")) + 3));
        sprintf(file_name, "%s№%s", getenv("FILE_NAME"), argv[1]);
    } else {
        file_name = malloc(sizeof(char) * (10));
        sprintf(file_name, "%s№%s", "defName", argv[1]);
    }
    printf("res %s\n", file_name);
    FILE *file;
    file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error file not open\n");
        return 1;
    }
    srand(time(NULL));
    double rNum = 0;
    for (int i = 0; i < atoi(argv[1]); i++) {
        fprintf(file, "%f\n", (double) rand() / (double) RAND_MAX);
    }
    fclose(file);
    return 0;
}
