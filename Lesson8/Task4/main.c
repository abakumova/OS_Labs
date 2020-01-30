#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

void *th_func(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
    double *pi = malloc(sizeof(double));
    *pi = 0;
    for (int i = 0; i < /*INT_MAX*/100000; i++) {
        *pi += pow(-1.0, i) / (2.0 * ((double) i) + 1.0);
        pthread_testcancel();
    }

    printf("thread exit\n");
    return pi;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Wrong number of parameters\n");
        return -1;
    }
    int time_sleep = atoi(argv[1]);

    pthread_t thread;
    void *result = NULL;
    pthread_create(&thread, NULL, th_func, &time_sleep);

    sleep(time_sleep);
    printf("Try to cancel thread\n");
    pthread_cancel(thread);
    printf("Join the tread\n");
    pthread_join(thread, &result);
    if (result == PTHREAD_CANCELED)
        printf("thread canceled\n");
    else printf("th returned %f\n", 4 * *(double *) result);
    return 0;
}
