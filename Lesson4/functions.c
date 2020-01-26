#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

extern char **environ;

void assign(int argc, char *argv[], const struct option *long_opt) {
    int i = 0;
    for (char c = *optarg; c != '\0'; i++, c = *(optarg + i));
    char *out;
    if (optarg != NULL)
        out = strcpy((char *) malloc(sizeof(char) * (i + 1)), optarg);
    else {
        out = (char *) calloc(2, sizeof(char));
        *out = ' ';
        *(out + 1) = '\0';
    }
    switch ((char) getopt_long(argc, argv, "i:s:a:v::d:ch", long_opt, NULL)) {
        case 'v':
            if (optarg != NULL) {
                setenv(out, optarg, 1);
                printf("%s = %s\n", out, getenv(out));

            } else {
                setenv(out, " ", 1);
                printf("%s = %s\n", out, getenv(out));
            }
            break;
        case 'a':
            if (optarg != NULL) {
                setenv(optarg, out, 1);
                printf("%s = %s\n", optarg, getenv(optarg));
            } else
                printf("%s\n", "No variable specified.");
            break;
        default:
            printf("%s\n", "No variable specified.");
    }
    free(out);
}

void print_all_env() {
    int i = 0;
    char *out = NULL;
    if (environ != NULL)
        while ((out = *(environ + i)) != NULL) {
            printf("%s\n", out);
            i++;
        }
}

void info() {
    if (getenv(optarg) != NULL)
        printf("%s\n", getenv(optarg));
    else
        printf("%s - %s\n", optarg, "No environment variable.");
}

void set() {
    putenv(optarg);
    int i = 0;
    for (char c = *optarg; c != '='; i++, c = *(optarg + i));
    char *out = (char *) malloc(sizeof(char) * i + 1);
    out = strncpy(out, optarg, i);
    printf("z%s = %s\n", out, getenv(out));
    free(out);
    out = NULL;
}

void del() {
    if (unsetenv(optarg) == -1) {
        printf("Error\n");
    }
    if (environ == NULL) {
        printf("No variables.\n");
        return;
    }
    int i = 0;
    char *out = NULL;
    while ((out = *(environ + i)) != NULL) {
        printf("%s\n", out);
        i++;
    }
}