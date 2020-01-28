#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include <unistd.h>

#define A 0
#define B 10
#define C 10
#define D 20
#define R 5

int main(int argc, char const *argv[]) {
    pid_t pid;
    int count_dots =/*2147483646*/100000;
    char str[11];
    int result = 0;
    int check[(int) (ceil((double) count_dots / 250.0))];
    for (int i = 0; i < (int) ceil((double) count_dots / 250.0); i++) {
        pid = fork();
        if (pid == 0) {
            if ((i == (ceil((double) count_dots / 250.0) - 1)) && ((count_dots % 250) != 0))
                sprintf(str, "%i", count_dots % 250);
            else
                sprintf(str, "%i", 250);
            execlp("./d.out", "d.out", str, NULL);
            printf("%s\n", "Error");
        } else if (pid > 0) {
            if (wait(&result) == -1) {
                printf("error wait\n");
                return 1;
            }
            if (WIFEXITED(result))
                check[i] = WEXITSTATUS(result);
        }
    }
    double hit = 0;
    for (int i = 0; i < (int) ceil((double) count_dots / 250.0); i++)
        hit += (double) check[i];
    double square = (double) ((B - A) * (D - C));
    printf("square %f\n", square);
    double square_fig = (((double) hit) * square) / ((double) count_dots);
    printf("The area of \u200B\u200Bthe figure = %f\n", square_fig);
    printf("pi = %f\n", square_fig / (double) (R * R));

    return 0;
}
