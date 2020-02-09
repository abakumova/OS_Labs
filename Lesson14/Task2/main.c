#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>

#define SIZE_STR 50

int main(int argc, char const *argv[]) {
    pid_t pid;
    int fd_p_d;
    int fd_d_p;
    char str[SIZE_STR];
    char name_file_d_p[] = "fifo_d-p.file";
    char name_file_p_d[] = "fifo_p-d.file";
    unlink(name_file_d_p);
    unlink(name_file_p_d);
    if (mkfifo(name_file_d_p, 0666) < 0) {
        printf("Error mkfifo\n");
        return -1;
    }
    if (mkfifo(name_file_p_d, 0666) < 0) {
        printf("Error mkfifo\n");
        return -1;
    }
    pid = fork();
    if (pid == 0) {
        //daughter
        if ((fd_p_d = open(name_file_p_d, O_RDONLY)) < 0) {
            printf("Errord open read");
            return -1;
        }
        if ((fd_d_p = open(name_file_d_p, O_WRONLY)) < 0) {
            printf("Errord open write");
            return -1;
        }
        while (1) {
            if (!read(fd_p_d, str, SIZE_STR))
                return 0;
            for (int i = 0; str[i]; ++i) {
                str[i] = toupper(str[i]);
            }
            if (!write(fd_d_p, str, SIZE_STR))
                return 0;
        }
    } else if (pid > 0) {
        //parent
        if ((fd_p_d = open(name_file_p_d, O_WRONLY)) < 0) {
            printf("Errorp open write");
            return -1;
        }
        if ((fd_d_p = open(name_file_d_p, O_RDONLY)) < 0) {
            printf("Errorp open read");
            return -1;
        }
        while (1) {
            printf("Enter str\n");
            gets(str);
            if (!write(fd_p_d, str, SIZE_STR))
                return 0;
            if (!read(fd_d_p, str, SIZE_STR))
                return 0;
            printf("Result:%s\n", str);
        }
    }
    printf("%s\n", str);
    return 0;
}