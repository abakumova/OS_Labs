#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/signal.h>

void siginal_handler(int signo) {
    if (signo == SIGINT)
        printf("SIGINT\n");
    else if (signo == SIGTERM)
        printf("SIGTERM\n");
    else if (signo == SIGUSR1) {
        printf("SIGUSR1\n");
        exit(1);
    }
}

int main(int argc, char **argv) {
    struct sigaction sa;
    sigset_t newset;
    sigemptyset(&newset);
    sigaddset(&newset, SIGHUP);
    sigprocmask(SIG_BLOCK, &newset, 0);
    sa.sa_handler = siginal_handler;
    sigaction(SIGTERM, &sa, 0);
    sigaction(SIGINT, &sa, 0);
    sigaction(SIGUSR1, &sa, 0);
    printf("My pid is %i\n", getpid());
    printf("Waiting...\n");

    while (1)
        pause();
    return 0;
}
