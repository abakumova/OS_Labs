#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/signal.h>


pid_t pid;

void sigusr1d_handler(int signo) {
    printf("Received from main\n");
    kill(pid, SIGUSR1);
}

void sigusr1m_handler(int signo) {
    printf("Received from daughter\n");
    kill(pid, SIGUSR1);
}

int main(int argc, char const *argv[]) {
    sigset_t set;
    sigset_t oldset;
    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    sigprocmask(SIG_BLOCK, &set, &oldset);
    pid = fork();
    if (pid == 0) {
        //daugter
        pid = getppid();
        signal(SIGUSR1, sigusr1d_handler);
        while (1) {
            sigsuspend(&oldset);
        }
    } else if (pid > 0) {
        //parent        
        signal(SIGUSR1, sigusr1m_handler);
        kill(pid, SIGUSR1);
        while (1) {
            sigsuspend(&oldset);
        }
    }
    return 0;
}
