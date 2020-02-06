#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>

int main(int argc, char const *argv[]) {
    int id_sh_sem = 0;//ид общего семафора
    int id_sh_mem = 0;//ид общей области памяти
    struct shmid_ds ds;//структура с информацией об общей области памяти
    int size_arr = 0;//кол-во целых чисел в общей области памяти
    int *arr = NULL;//указатель на общую облась памяти
    //проводим настройку семафоров
    struct sembuf sem_arg[2];
    sem_arg[0].sem_num = 0;//порядковый номер
    sem_arg[0].sem_op = 1;//операция(-1)
    sem_arg[0].sem_flg = 0;

    sem_arg[1].sem_num = 1;//порядковый номер
    sem_arg[1].sem_op = -1;//операция(1)
    sem_arg[1].sem_flg = 0;

    if ((id_sh_mem = shmget(ftok("/home/viktoriia/OS_LABS/Lesson13/file.txt", 1), 0, 0666)) <
        0) {//подключаемся к общей области памяти по файлу
        printf("Can not attach shared memory segment\n");
        return 0;
    }
    if ((id_sh_sem = semget(ftok("/home/viktoriia/OS_LABS/Lesson13/file.txt", 2), 1, 0666)) <
        0) {//подключаемся к общему семафору
        printf("Can not attach sem shared segment\n");
        return 0;
    }
    if ((arr = (int *) shmat(id_sh_mem, NULL, 0)) == NULL) {//подключаем к указателю общую область памяти
        printf("Can not get shared memory segment\n");
        return 0;
    }
    //get size about size arr
    shmctl(id_sh_mem, IPC_STAT, &ds);
    size_arr = ds.shm_segsz / sizeof(int);

    while (1) {
        for (int i = 0; i < size_arr; ++i) {//заполняем общую область памяти числами пользователя
            printf("Enter %i number\n", i + 1);
            scanf("%i", (arr + i));
        }
        semop(id_sh_sem, sem_arg, 1);//применение настроек sem_arg[0] к семафору id_sh_sem 1 раз
        semop(id_sh_sem, sem_arg + 1, 1);//применение настроек sem_arg[1] к семафору id_sh_sem 1 раз
        printf("Result = %i\n", *arr);
    }

    return 0;
}
