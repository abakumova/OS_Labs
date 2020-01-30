#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

void *th_func(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    for (int i = 0; i < INT_MAX; ++i) {
        printf("Daughter th i=%i\n", i);
        sleep(1);
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Wrong number of parameters\n");
        return -1;
    }
    int time_sleep = atoi(argv[1]);

    pthread_t thread;
    void *result = NULL;
    pthread_create(&thread, NULL, th_func, NULL);

    sleep(time_sleep);
    pthread_cancel(thread);
    pthread_join(thread, &result);
    if (result == PTHREAD_CANCELED)
        printf("thread canceled\n");
    return 0;
}
