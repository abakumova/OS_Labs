#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

#define SIZE_BUFF 255

int main(int argc, char const *argv[]) {
    char str[SIZE_BUFF];
    char *arg[3];
    arg[2] = NULL;
    char *name_prog = NULL;
    char *options = NULL;
    int i = 0;
    pid_t pid;
    int status = 0;
    while (1) {
        printf("%s$", getenv("USER"));
        gets(str);

        if (strlen(str) > SIZE_BUFF) {
            printf("Error command\n");
            continue;
        }

        if (!strcmp(str, "stop"))
            exit(0);
        //finding a name by a space or the end of a line
        for (i = 0; (str[i] != ' ') && (str[i] != '\0'); i++);

        strncpy(name_prog = realloc(name_prog, sizeof(char) * (i + 1)), str, i);
        *(name_prog + i) = '\0';
        arg[0] = name_prog;
        if (i == strlen(str)) {
            arg[1] = NULL;
        } else {
            strncpy(options = realloc(options, (strlen(str) - i + 1)), str + i + 1, strlen(str) - i);
            *(options + strlen(str) - i) = '\0';
            arg[1] = options;
        }
        pid = fork();
        if (pid == 0) {
            execvp(name_prog, arg);
            printf("Error not found prog\n");
            system("ps");
        } else if (pid > 0) {
            wait(&status);
            printf("Result %i\n", status);
        }
    }
    free(name_prog);
    return 0;
}