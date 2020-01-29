#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

struct data {
    int *arr;
};

_Bool isPrime(int n) {
    if (n == 1) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

uint64_t factorial(uint64_t n) {
    uint64_t i;
    for (i = 1; n > 1; i *= (n--));
    return i;
}

void *th_func1(void *arg) {
    int count = 0;
    struct data *numbers = ((struct data *) arg);
    numbers->arr = realloc(numbers->arr, sizeof(int) * 100);
    for (int i = 1; i < 100; ++i) {
        if (isPrime(i)) {
            count++;
            *(numbers->arr + i) = i;
        }
    }
    printf("Exit\n");
}

void *th_func2(void *arg) {
    int *arr = (int *) malloc(sizeof(int) * 10);
    struct data *numbers = ((struct data *) arg);
    numbers->arr = realloc(numbers->arr, sizeof(int) * 10);
    for (int i = 0; i < 10; ++i) {
        *(arr + i) = factorial(2 * i) / (factorial(i + 1) * factorial(i));
    }
    return arr;
}


int main(int argc, char const *argv[]) {
    void *nums;
    int *primes;
    struct data th_data1;
    struct data th_data2;
    th_data1.arr = NULL;
    th_data2.arr = NULL;
    pthread_t pthread1;
    pthread_t pthread2;
    pthread_create(&pthread1, NULL, &th_func1, &th_data1);
    pthread_create(&pthread2, NULL, &th_func2, &th_data2);

    //waiting without status
    pthread_join(pthread1, NULL);
    pthread_join(pthread2, &nums);

    for (int i = 0; i < 10; ++i) {
        printf("%d\n", ((int *) nums)[i]);
    }
    printf("MAIN exit\n");
    th_data1.arr = NULL;
    th_data2.arr = NULL;
    free(th_data1.arr);
    free(th_data2.arr);
    return 0;
}
