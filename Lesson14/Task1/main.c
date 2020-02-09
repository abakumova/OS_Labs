#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

#define SIZE_STR 50

int main(int argc, char const *argv[]) {
    pid_t pid;
    int fd_p_d[2];
    int fd_d_p[2];
    char str[SIZE_STR];
    if (pipe(fd_p_d) < 0) {
        printf("Error pipe()\n");
        return -1;
    }
    if (pipe(fd_d_p) < 0) {
        printf("Error pipe()\n");
        return -1;
    }
    pid = fork();
    if (pid == 0) {
        //daughter
        close(fd_p_d[1]);
        close(fd_d_p[0]);
        while (1) {
            if (!read(fd_p_d[0], str, SIZE_STR))
                return 0;
            for (int i = 0; str[i]; ++i) {
                str[i] = toupper(str[i]);
            }
            if (!write(fd_d_p[1], str, SIZE_STR))
                return 0;
        }
    } else if (pid > 0) {
        //parent
        close(fd_p_d[0]);
        close(fd_d_p[1]);
        while (1) {
            printf("Enter str\n");
            gets(str);
            if (!write(fd_p_d[1], str, SIZE_STR))
                return 0;
            if (!read(fd_d_p[0], str, SIZE_STR))
                return 0;
            printf("Result:%s\n", str);
        }
    }
    printf("%s\n", str);
    return 0;
}