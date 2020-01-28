#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>

#define SECONDS 3

int main(int argc, char const *argv[]) {
    pid_t pid;
    printf("FORK \n");
    pid = fork();
    if (pid == 0) {
        time_t now = time(NULL);
        int count = 0;
        while (time(NULL) != now + SECONDS)
            count++;
        printf("Child ID = %i count = %d\n", getpid(), count);
    } else if (pid > 0) {
        time_t now = time(NULL);
        int count = 0;
        while (time(NULL) != now + SECONDS)
            count++;
        printf("Parent ID = %i count = %d\n", getpid(), count);
    } else printf("Error\n");
    return 0;
}