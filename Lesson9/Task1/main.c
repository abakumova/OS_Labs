#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <stdio.h>

int glob_data = 0;

void *th_func_plus(void *arg) {
    for (int i = 0; i < *(int *) arg; ++i)
        glob_data++;
    printf("Data th_func_plus = %i\n", glob_data);
}

void *th_func_minus(void *arg) {
    for (int i = 0; i < *(int *) arg; ++i)
        glob_data--;
    printf("Data th_func_minus = %i\n", glob_data);
}

int main(int argc, char *argv[]) {
    int count_threads = 100;
    int count_operations = 10;
    const struct option long_opt[] = {
            {"threads",    optional_argument, NULL, 't'},
            {"operations", optional_argument, NULL, 'o'},
            {NULL,         0,                 NULL, 0}
    };
    char ch = -1;
    while ((ch = getopt_long(argc, argv, "t:o:", long_opt, NULL)) != -1)
        switch (ch) {
            case 't':
                count_threads = atoi(optarg);
                printf("%i\n", atoi(optarg));
                break;
            case 'o':
                count_operations = atoi(optarg);
                printf("%i\n", atoi(optarg));
                break;
        }
    pthread_t pthread_minus[count_threads];
    pthread_t pthread_plus[count_threads];
    for (int i = 0; i < count_threads; ++i) {
        pthread_create(&pthread_plus[i], NULL, &th_func_plus, &count_operations);
        pthread_create(&pthread_minus[i], NULL, &th_func_minus, &count_operations);
    }
    for (int i = 0; i < count_threads; i++) {
        pthread_join(pthread_minus[i], NULL);
        pthread_join(pthread_plus[i], NULL);
    }
    printf("	Data = %i\n", glob_data);
    return 0;
}
