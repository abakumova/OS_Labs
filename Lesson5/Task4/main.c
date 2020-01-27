#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>

void help() {
    printf("This program is created for emulating real terminal machine.\n");
    printf("Options -b or --buffer to change size of buffer,\n");
    printf("\"stop\" if you want to close the program.\n\n");
}

void close_prog() {
    printf("Wait 3 seconds...\n");
    sleep(3);
    system("clear");
}

int main(int argc, char *argv[]) {
    atexit(close_prog);
    int buffer_size = 127;
    const struct option long_options[] = {
            {"help",   0, NULL, 'h'},
            {"buffer", 1, NULL, 'b'},
            {NULL,     0, NULL, 0}
    };

    char option = 0;
    while ((option = getopt_long(argc, argv, "hb:", long_options, NULL)) != -1) {
        switch (option) {
            case 'h':
                help();
                break;
            case 'b':
                if (atoi(optarg) < 1) {
                    printf("Invalid value\n");
                    return 1;
                }
                buffer_size = atoi(optarg);
                printf("The buffer size has been changed to %i\n", buffer_size);
                break;
        }
    }

    char buffer[buffer_size];
    printf("At the moment the program is working with '%s'\n", getpwuid(getuid())->pw_gecos);
    char *user_name = getenv("USER");
    printf("%s$", user_name);
    while (1) {
        if (strlen(buffer) > buffer_size) {
            printf("Command size exceeded\n");
            continue;
        }
        if (strcmp(buffer, "stop") == 0) {
            printf("%s\n", "Wait 3 seconds...");
            system("sleep 3");
            system("clear");
            exit(0);
        }
        break;
    }

    return 0;
}
