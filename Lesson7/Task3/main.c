#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *th_func1(void *arg) {
    for (int i = 0; i < 100; i++)
        printf("Child th str\n");
}

void *th_func2(void *arg) {
    long ltime = time(NULL);
    int stime = (unsigned int) ltime / 2;
    srand(stime);
    int number;
    for (int i = 0; i < 100; ++i) {
        number = rand() % 10;
        printf("Child th number - %i\n", number);
        if (number == 8) {
            printf("Child th exit\n");
            pthread_exit(NULL);
        }
    }

}


int main(int argc, char const *argv[]) {
    pthread_t pthread1;
    pthread_t pthread2;
    pthread_create(&pthread1, NULL, &th_func1, NULL);
    pthread_create(&pthread2, NULL, &th_func2, NULL);
    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
    printf("MAIN exit\n");
    return 0;
}