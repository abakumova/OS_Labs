#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

int glob_var = 0;
pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    srand(time(NULL) + pthread_self());
    int rand_var = 0;
    int count = 0;
    while (1) {
        rand_var = 1 + rand() % 10;
        pthread_mutex_lock(&mx);
        printf("producer generates var=%i\n", rand_var);
        glob_var = rand_var;
        pthread_cond_signal(&cond_var);
        pthread_mutex_unlock(&mx);
        sleep(2);
    }
}

void *consumer(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    srand(time(NULL) + pthread_self());
    int count = 0;
    while (1) {
        pthread_mutex_lock(&mx);
        while (!glob_var) {
            pthread_cond_wait(&cond_var, &mx);
        }
        printf("consumer consumes var=%i\n", glob_var);
        glob_var = 0;
        pthread_mutex_unlock(&mx);
    }

}

int main(int argc, char *argv[]) {
    pthread_t thread_consumer, thread_producer;
    pthread_create(&thread_producer, NULL, &producer, NULL);
    pthread_create(&thread_consumer, NULL, &consumer, NULL);
    sleep(10);
    printf("cancelling\n");
    pthread_cancel(thread_consumer);
    pthread_cancel(thread_producer);
    pthread_cond_destroy(&cond_var);
    pthread_mutex_destroy(&mx);
    return 0;
}

