#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void reverse(char s[]) {
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[]) {
    int i, sign;

    if ((sign = n) < 0)          // record sign
        n = -n;                  // make n positive
    i = 0;
    do {                         // generate digits in reverse order
        s[i++] = n % 10 + '0';   // get next digit
    } while ((n /= 10) > 0);     // delete it
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}


int main(int argc, char *argv[]) {
    const struct option long_options[] = {
            {"file",   no_argument,       NULL, 'f'},
            {"number", required_argument, NULL, 'n'},
            {NULL,     0,                 NULL, 0}
    };
    int count_douter_progs = 0;
    char option = 0;
    while ((option = getopt_long(argc, argv, "f::n:", long_options, NULL)) != -1) {
        switch (option) {
            case 'f':
                if (optarg != NULL)
                    setenv("FILE_NAME", optarg, 1);
                break;
            case 'n':
                if (atoi(optarg) < 1) {
                    printf("Wrong value\n");
                    return 1;
                }
                count_douter_progs = atoi(optarg);
                break;
        }
    }
    for (int i = 1; i <= count_douter_progs; i++) {
        int k = 0; //character count
        double number = (double) i;
        while (number > 1) {
            number /= 10;
            k++;
        }
        char *rstr = realloc(rstr, sizeof(char) * (k + 9));
        sprintf(rstr, "%s%i", "./d.out ", i);
        system(rstr);
        free(rstr);
    }
    return 0;
}