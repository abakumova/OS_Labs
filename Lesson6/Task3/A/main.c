#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    setbuf(stdout, NULL);
    printf("MAIN %i\n", getpid());
    int local = 0;
    pid_t pid[2];
    pid[0] = fork();
    if (pid[0] == 0) {
        //child
        local++;
        printf("D\nVariable value = %d\nAddress = %p\nParent pid = %i\nOwn pid = %i\n", local, &local,
               getppid(), getpid());
        pid_t pidd[2];
        pidd[0] = fork();
        if (pidd[0] == 0) {
            //child
            local++;
            printf("D\nVariable value = %d\nAddress = %p\nParent pid = %i\nOwn pid = %i\n", local, &local,
                   getppid(), getpid());
        } else if (pidd[0] > 0) {
            //parent
            pidd[1] = fork();
            if (pidd[1] == 0) {
                //child
                local++;
                printf("D\nVariable value = %d\nAddress = %p\nParent pid = %i\nOwn pid = %i\n", local,
                       &local, getppid(), getpid());
            } else if (pidd[1] > 0) {
                //parent
                printf("Second MAIN IDs1 = %i IDs2 = %i\n", pidd[0], pidd[1]);
                wait(NULL);
            }
        }
    } else if (pid[0] > 0) {
        //parent
        pid[1] = fork();
        if (pid[1] == 0) {
            //child
            local++;
            printf("D\nVariable value = %d\nAddress = %p\nParent pid = %i\nOwn pid = %i\n", local, &local,
                   getppid(), getpid());
            pid_t pidd[2];
            pidd[0] = fork();
            if (pidd[0] == 0) {
                //child
                local++;
                printf("D\nVariable value = %d\nAddress = %p\nParent pid = %i\nOwn pid = %i\n", local,
                       &local, getppid(), getpid());
            } else if (pidd[0] > 0) {
                //parent
                pidd[1] = fork();
                if (pidd[1] == 0) {
                    //child
                    local++;
                    printf("D\nVariable value = %d\nAddress = %p\nParent pid = %i\nOwn pid = %i\n", local,
                           &local, getppid(), getpid());
                } else if (pidd[1] > 0) {
                    //parent
                    printf("Second MAIN IDs1 = %i IDs2 = %i\n", pidd[0], pidd[1]);
                }
            }
        } else if (pid[1] > 0) {
            //parent
            printf("MAIN ID1 = %i ID2 = %i\n", pid[0], pid[1]);
            wait(NULL);
        }
    }
    return 0;
}