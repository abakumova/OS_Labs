#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

char *msg = NULL;
int seconds = 2;

void alarm_handler(int signo) {
    printf("%s\n", msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    _Bool flag = false;
    const struct option long_opt[] = {
            {"seconds", required_argument, NULL, 's'},
            {"message", required_argument, NULL, 'm'},
            {NULL,      0,                 NULL, 0}
    };
    char ch = -2;
    while ((ch = getopt_long(argc, argv, "s:m:", long_opt, NULL)) != -1) {
        flag = true;
        switch (ch) {
            case 'm':
                msg = malloc(strlen(optarg) + 1);
                sprintf(msg, "%s\n", optarg);
                *(msg + strlen(optarg)) = '\0';
                break;
            case 's':
                seconds = atoi(optarg);
                break;
        }
    }
    if (!flag) {
        printf("program running without params\n");
        return 0;
    }
    pid_t pid;
    if (signal(SIGALRM, alarm_handler) == SIG_ERR)
        printf("Error SIGINT\n");
    pid = fork();
    if (pid == 0) {
        //daughter
        alarm(seconds);
        pause();
    } else if (pid > 0) {
        //parent
        return 0;
    } else printf("Error\n");
    return 0;
}