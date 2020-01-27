#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int count;

void my_func(int status, void *arg) {
    sleep(1);
    printf("on_exit %ld\n", (long) arg);
    return;
}

void my_func2(void) {
    sleep(1);
    printf("atexit %i\n", count);
    count -= 1;
}

int main(int argc, char const *argv[]) {
    if (argc == 1 || argc > 2) {
        printf("Invalid value\n");
        return 0;
    }
    count = atoi(argv[1]);
    for (int i = 0; i < count; i++)
        if (on_exit(my_func, i)) printf("This function is not registered.\n");
    return 0;
}
