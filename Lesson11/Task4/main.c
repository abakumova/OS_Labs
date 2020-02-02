#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <stdbool.h>
#include <wait.h>
#include <sys/signal.h>


pid_t pid;
_Bool flag = false;

void sigusr1_handler(int signo, siginfo_t *si, void *ucontext) {
    printf("Receive i=%p\n", si->si_value);
}

int main(int argc, char const *argv[]) {
    struct sigaction sigact;
    sigact.sa_flags = SA_SIGINFO;
    sigact.sa_sigaction = sigusr1_handler;
    if (sigaction(SIGUSR1, &sigact, NULL) == SIG_ERR)
        printf("Error SIGUSR1\n");
    pid = fork();
    if (pid == 0) {
        //daughter
        printf("daughter work\n");
        while (1)
            pause();
    } else if (pid > 0) {
        //parent
        printf("MAIN WORK\n");
        union sigval value;
        sleep(1);
        for (int i = 0; i < 10; ++i) {
            value.sival_int = i;
            printf("Send daughter value %i\n", i);
            sigqueue(pid, SIGUSR1, value);
            sleep(1);
        }
        kill(pid, SIGTERM);
        wait(NULL);
        printf("Daughter finishes work\n");
    } else printf("Error\n");
    return 0;
}
