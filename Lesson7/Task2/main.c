#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

struct data {
    char name[4];
    int count;
};

void *th_func(void *arg) {
    struct data info = *(struct data *) arg;
    for (int i = 0; i < info.count; ++i) {
        printf("Thread %s\t%i\n", info.name, i + 1);
    }
}


int main(int argc, char const *argv[]) {
    struct data arg[4] = {{"th1", 3},
                          {"th2", 2},
                          {"th3", 5},
                          {"th4", 7}};
    pthread_t pthread;
    for (int i = 0; i < 4; ++i) {
        pthread_create(&pthread, NULL, &th_func, &arg[i]);
    }

    sleep(2);
    return 0;
}