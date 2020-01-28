#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    printf("pid of process %d\n", getpid());
    printf("pid of parent process %d\n", getppid());
    printf("pid ргgroup %d\n", getpgrp());
    printf("ID of real user %d\n", getuid());
    printf("Effective ID of user %d\n", geteuid());
    printf("ID of group %d\n", getgid());
    printf("Effective ID of group %d\n", getegid());
    return 0;
}