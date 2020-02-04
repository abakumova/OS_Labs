#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

int *data = NULL;
pid_t pid_daughter;
int id_sh_mem;

void SEGUSR1_H(int signo) {
    printf("Result:%d\n", *data);
}

void EXIT_H(int signo) {
    printf("Main has been finished\n");
    kill(pid_daughter, SIGINT);
    shmdt(data);
    shmctl(id_sh_mem, IPC_RMID, NULL);
    exit(0);
}

int main(int argc, char const *argv[]) {
    int size_of_buffer = 10;
    signal(SIGUSR1, SEGUSR1_H);
    signal(SIGINT, EXIT_H);

    printf("Set buffer size:\n");
    scanf("%i", &size_of_buffer);
    id_sh_mem = shmget(IPC_PRIVATE, sizeof(int) * size_of_buffer, IPC_CREAT | 0666);

    char *arg[3];
    arg[2] = NULL;
    arg[0] = malloc(sizeof(char) * (strlen("d.out") + 1));
    strncpy(arg[0], "d.out", 5);
    *(arg[0] + 12) = '\0';
    int k = 0;
    int number = id_sh_mem;
    while (number >= 1) {
        number /= 10;
        k++;
    }
    arg[1] = malloc(sizeof(char) * (k + 1));
    sprintf(arg[1], "%i", id_sh_mem);
    *(arg[1] + k) = '\0';

    pid_daughter = fork();
    if (pid_daughter == 0) {
        //daugter
        execvp("./a.out", arg);
    } else if (pid_daughter > 0) {
        //parent
        printf("Shared mem id:%d\n", id_sh_mem);
        data = (int *) shmat(id_sh_mem, NULL, 0);
        while (1) {
            for (int i = 0; i < size_of_buffer; ++i) {
                printf("Enter %d number\n", i + 1);
                scanf("%d", data + i);
            }
            kill(pid_daughter, SIGUSR1);
            printf("Wait signal\n");
            pause();
        }
    }
    return 0;
}
