#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdbool.h>


pid_t pid;
_Bool flag = false;

void sigusr1d_handler(int signo) {
    // printf("DAUGHTER msg\n");
    printf("Receive msg from main\n");
    kill(pid, SIGUSR1);
    flag = true;
}

void sigusr1m_handler(int signo) {
    printf("Receive msg from daughter\n");
    // printf("MAIN msg\n");
    kill(pid, SIGUSR1);
    flag = true;
}

void proof_start(int signo) {
    printf("Signal received\n");
    flag = true;
}

void clear_cahth(int signo) {

}

int main(int argc, char const *argv[]) {
    if (signal(SIGUSR1, clear_cahth) == SIG_ERR)
        printf("Error SIGUSR1\n");
    pid = fork();
    if (pid == 0) {
        //daugter
        printf("DAUGHTER WORK\n");
        pause();
        pid = getppid();
        if (signal(SIGUSR1, sigusr1d_handler) == SIG_ERR)
            printf("Error SIGUSR1\n");
        // pause();
        printf("all set\n");
        kill(pid, SIGUSR1);
        while (1) {
            // printf("D pause\n");
            // while(!flag)
            pause();
            // kill(pid,SIGUSR1);
            flag = false;
        }
        while (1);
    } else if (pid > 0) {
        //parent
        printf("MAIN WORK\n");
        // if (signal(SIGUSR1,proof_start)==SIG_ERR)
        // printf("Error SIGUSR1\n");
        if (signal(SIGUSR1, sigusr1m_handler) == SIG_ERR)
            printf("Error SIGUSR1\n");
        while (!flag) {
            // printf("Send\n");
            kill(pid, SIGUSR1);
        }
        flag = false;
        kill(pid, SIGUSR1);
        while (1) {
            // kill(pid,SIGUSR1);
            // printf("M pause\n");
            // while(!flag)
            pause();
            flag = false;
        }
    } else printf("Error\n");
    return 0;
}
