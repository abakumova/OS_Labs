#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

pthread_key_t thread_key;

void *th_func(void *arg) {
    char *str = malloc(sizeof(char) * 8);
    sprintf(str, "%s", "message");
    *(str + 7) = '\0';
    pthread_setspecific(thread_key, str);

    srand(time(NULL) + *(int *) arg);
    int count = 1 + rand() % 10;
    printf("count %i\n", count);
    for (int i = 0; i < count; ++i) {
        printf("%i thread: message:\"%s\" number: %i\n", *(int *) arg, (char *) pthread_getspecific(thread_key),
               1 + rand() % 10);
    }
    return 0;
}

int main(int argc, char const *argv[]) {

    if (argc != 2) {
        printf("Wrong number of parameters\n");
        return -1;
    }
    int count_th = atoi(argv[1]);
    int numb_th[count_th];
    pthread_t pthread[count_th];
    pthread_key_create(&thread_key, NULL);

    for (int i = 0; i < count_th; i++) {
        numb_th[i] = i;
        pthread_create(&pthread[i], NULL, &th_func, &numb_th[i]);
    }
    for (int i = 0; i < count_th; ++i)
        pthread_join(pthread[i], NULL);
    return 0;
}