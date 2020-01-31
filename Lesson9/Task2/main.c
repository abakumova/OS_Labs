#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <math.h>
#include <stdio.h>

double result = 0;
pthread_mutex_t mx = PTHREAD_MUTEX_INITIALIZER;
#define a 0
#define b 2

struct diap {
    double start;
    double end;
};

double calc_i(int n, double h, double x0) {
    double in = 0;
    double x = x0;
    for (int i = 0; i <= n - 1; ++i) {
        in += 4 - (x + h / 2.0) * (x + h / 2.0);
        x += h;
    }
    return h * in;
}

void *calculating(void *arg) {
    double e = 0.0001;
    int n = 1;
    double in = calc_i(n, (((struct diap *) arg)->end - ((struct diap *) arg)->start) / (double) n,
                       ((struct diap *) arg)->start),
            inn = calc_i(2 * n, (((struct diap *) arg)->end - ((struct diap *) arg)->start) / (2.0 * (double) n),
                         ((struct diap *) arg)->start);

    while (fabs(in - inn) > e) {
        n++;
        in = calc_i(n, (((struct diap *) arg)->end - ((struct diap *) arg)->start) / (double) n,
                    ((struct diap *) arg)->start);
        inn = calc_i(2 * n, (((struct diap *) arg)->end - ((struct diap *) arg)->start) / (2.0 * (double) n),
                     ((struct diap *) arg)->start);
    }
    // printf("in=%f\tinn=%f\n",in,inn);
    pthread_mutex_lock(&mx);
    result += inn;
    pthread_mutex_unlock(&mx);
}

int main(int argc, char *argv[]) {
    int count_threads = 4;
    const struct option long_opt[] = {
            {"threads", optional_argument, NULL, 't'},
            {NULL,      0,                 NULL, 0}
    };
    char ch = -1;
    while ((ch = getopt_long(argc, argv, "t::", long_opt, NULL)) != -1)
        switch (ch) {
            case 't':
                count_threads = atoi(optarg);
                // printf("%i\n",atoi(optarg));
                break;
        }
    pthread_t pthread[count_threads];
    double h = ((double) (b - a)) / (double) count_threads;
    struct diap diaps[count_threads];
    for (double i = 0, d = 0; i < count_threads; ++i, d += h) {
        diaps[(int) i].start = d;
        diaps[(int) i].end = d + h;
    }
    for (int i = 0; i < count_threads; ++i) {
        pthread_create(&pthread[i], NULL, &calculating, &diaps[i]);
    }
    for (int i = 0; i < count_threads; i++)
        pthread_join(pthread[i], NULL);
    printf("result = %f\n", result);
    pthread_mutex_destroy(&mx);
    return 0;
}