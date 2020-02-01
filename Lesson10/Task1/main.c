#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>

sem_t empty_items;
sem_t fill_items;
int *arr = NULL;
int count_el = 10;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    srand(time(NULL) + pthread_self());
    int rand_var = 0;
    int count = 0;
    while (1) {
        rand_var = rand() % 10;
        sem_wait(&empty_items);
        pthread_mutex_lock(&lock);

        sem_getvalue(&fill_items, &count);
        printf("producer produces %i count=%i\n", rand_var, count);
        *(arr + count) = rand_var;
        for (int i = 0; i < count_el; ++i) {
            printf("arr[%i]=%i\t", i, *(arr + i));
        }
        printf("\n");
        printf("producer sleeps\n");
        pthread_mutex_unlock(&lock);
        sem_post(&fill_items);
    }
}

void *consumer(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    srand(time(NULL) + pthread_self());
    int count = 0;
    while (1) {
        sem_wait(&fill_items);
        pthread_mutex_lock(&lock);

        sem_getvalue(&fill_items, &count);
        printf("consumer consumes %icount=%i\n", *(arr + count), count);
        *(arr + count) = 0;
        for (int i = 0; i < count_el; ++i) {
            printf("//arr[%i]=%i\t", i, *(arr + i));
        }
        printf("\n");
        printf("consumer sleeps\n");
        pthread_mutex_unlock(&lock);
        sem_post(&empty_items);
    }

}

int main(int argc, char *argv[]) {
    pthread_t thread_consumer, thread_producer;

    const struct option long_opt[] = {
            {"count", optional_argument, NULL, 'c'},
            {NULL,    0,                 NULL, 0}
    };
    char ch = -1;
    while ((ch = getopt_long(argc, argv, "c::", long_opt, NULL)) != -1)
        switch (ch) {
            case 'c':
                count_el = atoi(optarg);
                break;
        }
    arr = malloc(sizeof(int) * count_el);
    sem_init(&empty_items, 0, count_el - 1);
    sem_init(&fill_items, 0, 0);
    pthread_create(&thread_producer, NULL, &producer, &count_el);
    pthread_create(&thread_consumer, NULL, &consumer, &count_el);
    sleep(4);
    printf("cancelling\n");
    pthread_cancel(thread_consumer);
    pthread_cancel(thread_producer);
    sem_destroy(&empty_items);
    sem_destroy(&fill_items);
    pthread_mutex_destroy(&lock);
    return 0;
}

