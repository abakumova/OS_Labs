#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

int size = 0;
int *arr = NULL;

void *controller(void *arg) {
    _Bool flag = true;
    while (flag) {
        flag = false;
        printf("Controller: ");
        for (int i = 0; i < size; i++) {
            if (*(arr + i) == 0) flag = true;
            printf("arr[%i]=%i ", i, *(arr + i));
        }
        printf("\n");
        if (flag)printf("Controller sleep\n");
        else printf("Controller exit\n");
        sleep(1);
    }
}

void *th_func(void *arg) {
    printf("%i th sleep %i seconds\n", *(int *) arg, *(int *) arg);
    sleep(*(int *) arg);
    srand(time(NULL));
    *(arr + *(int *) arg) = 1 + rand() % 10;
    printf("%i th sleep %i seconds\n", *(int *) arg, *(arr + *(int *) arg));
    sleep(*(arr + *(int *) arg));
    printf("%i th exit\n", *(int *) arg);
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Wrong number of parameters\n");
        return -1;
    }
    int count_th = atoi(argv[1]);
    size = count_th;
    int numb_th[count_th];
    for (int i = 0; i < count_th; i++) {
        numb_th[i] = i;
    }
    pthread_t pthread[count_th];
    arr = malloc(sizeof(int) * count_th);
    pthread_attr_t attr;
    pthread_t thread_controller;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    for (int i = 0; i < count_th; i++) {
        pthread_create(&pthread[i], NULL, &th_func, &numb_th[i]);
    }
    pthread_create(&thread_controller, &attr, &controller, NULL);
    pthread_attr_destroy(&attr);
    while (1);
    return 0;
}