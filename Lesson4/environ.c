#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "functions.h"

extern char **environ;

int main(int argc, char *argv[]) {
    const struct option long_opt[] = {
            {"help",   no_argument,       NULL, 'h'},
            {"info",   required_argument, NULL, 'i'},
            {"set",    required_argument, NULL, 's'},
            {"assign", required_argument, NULL, 'a'},
            {"value",  optional_argument, NULL, 'v'},
            {"del",    required_argument, NULL, 'd'},
            {"clear",  no_argument,       NULL, 'c'},
            {NULL,     0,                 NULL, 0}
    };

    char z = 0;
    switch (z = getopt_long(argc, argv, "i:s:a:v::d:ch", long_opt, NULL)) {
        case -1:
            print_all_env();
            break;
        case 'h':
            printf("%s \n", "INFO str");
            break;
        case 'i':
            info();
            break;
        case 's':
            set();
            break;
        case 'v':
        case 'a':
            assign(argc, argv, long_opt);
            break;
        case 'd':
            del();
            break;
        case 'c':
            clearenv();
            if (environ == NULL)
                printf("%s\n", "Environment variables are cleared");
            break;
        default:
            printf("Char %c\n", z);
            break;
    }
    return 0;
}