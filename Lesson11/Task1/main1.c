#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

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

int main(int argc, char const *argv[]) {

    if (signal(SIGINT, siginal_handler) == SIG_ERR)
        printf("Error SIGINT\n");
    if (signal(SIGTERM, siginal_handler) == SIG_ERR)
        printf("Error SIG_ERR\n");
    if (signal(SIGUSR1, siginal_handler) == SIG_ERR)
        printf("Error SIGUSR1\n");
    if (signal(SIGHUP, SIG_IGN) == SIG_ERR)
        printf("Error SIGHUP\n");
    if (signal(SIGPROF, SIG_DFL) == SIG_ERR)
        printf("Error SIGPROF\n");
    printf("My pid is %i\n", getpid());
    printf("Waiting...\n");
    while (1)
        pause();
    return 0;
}