#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

int id_sh_mem = 0;
int *arr = NULL;
int size = 0;
pid_t pid_parent;

void SEGUSR1_H(int signo) {
    kill(pid_parent, SIGUSR1);
    int result = 0;
    for (int i = 0; i < size; ++i)
        result += *(arr + i);
    *arr = result;
}

void EXIT_H(int signo) {
    printf("Not main has been finished\n");
    shmdt(arr);
    exit(0);
}

int main(int argc, char const *argv[]) {
    struct shmid_ds ds;
    signal(SIGINT, EXIT_H);
    signal(SIGUSR1, SEGUSR1_H);
    id_sh_mem = atoi(argv[1]);

    shmctl(id_sh_mem, IPC_STAT, &ds);
    size = ds.shm_segsz / sizeof(int);
    arr = (int *) shmat(id_sh_mem, NULL, 0);
    pid_parent = getppid();
    while (1) {
        pause();
    }

    return 0;
}