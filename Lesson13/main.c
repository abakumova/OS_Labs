#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>


int id_sh_mem;//ид общей области памяти
int id_sh_sem;//ид общего семафора
int *arr = NULL;//указатель на общую облась памяти

void exit_handler(int signo) {//обработчик сигнала SIGINT
    printf("Exit from MAIN\n");
    //detach
    if (shmdt(arr) < 0)//отсоеденение общей области памяти
        printf("Can not detach shared memory segment\n");
    //delete
    if (shmctl(id_sh_mem, IPC_RMID, NULL) < 0)//удаление общей области памяти
        printf("Can not delete shared memory segment\n");
    //delete sem
    if (semctl(id_sh_sem, 0, IPC_RMID, NULL) < 0)//удаление общего семафора
        printf("Can not delete sem segment\n");
    exit(0);
}

int main(int argc, char const *argv[]) {
    int size_of_buffer = 5;//кол-во целых чисел в общей области памяти
    int result = 0;//итоговый результат
    struct sembuf sem_arg[2];//массив структур с настройками для семафора

    if (signal(SIGINT, exit_handler) == SIG_ERR) {//регистрация оьработчика
        printf("Error SIGUSR1\n");
        return 0;
    }
    //create
    if ((id_sh_mem = shmget(ftok("/home/viktoriia/OS_LABS/Lesson13/file.txt", 1), sizeof(int) * size_of_buffer,
                            IPC_CREAT | 0666)) < 0) {//создание общей области памяти с доступом по файлу
        printf("Can not create shared memory segment\n");
        return 0;
    }
    if ((id_sh_sem = semget(ftok("/home/viktoriia/OS_LABS/Lesson13/file.txt", 2), 2, IPC_CREAT | 0666)) <
        0) {//создание общего семафора с доступом по файлу
        printf("Can not create sem shared segment\n");
        return 0;
    }
    printf("id_sh_mem %i\n", id_sh_mem);
    //attach
    if ((arr = (int *) shmat(id_sh_mem, NULL, 0)) == NULL) {//подключаем к указателю созданную область памяти
        printf("Can not attach shared memory segment\n");
        return 0;
    }
    //проводим настройку семафоров
    sem_arg[0].sem_num = 0;//порядковый номер
    sem_arg[0].sem_op = -1;//операция(-1)
    sem_arg[0].sem_flg = 0;

    sem_arg[1].sem_num = 1;//порядковый номер
    sem_arg[1].sem_op = 1;//операция(1)
    sem_arg[1].sem_flg = 0;

    while (1) {
        semop(id_sh_sem, sem_arg, 1);//применение настроек sem_arg[0] к семафору id_sh_sem 1 раз
        result = 0;
        for (int i = 0; i < size_of_buffer; ++i)//подсчет суммы
            result += *(arr + i);
        *arr = result;
        semop(id_sh_sem, sem_arg + 1, 1);//применение настроек sem_arg[1] к семафору id_sh_sem 1 раз
    }
    //сюда, как правило, не доходим
    //detach
    if (shmdt(arr) < 0)
        printf("Can not detach shared memory segment\n");
    //delete
    if (shmctl(id_sh_mem, IPC_RMID, NULL) < 0)
        printf("Can not delete shared memory segment\n");
    //delete sem
    if (semctl(id_sh_sem, 0, IPC_RMID, NULL) < 0)
        printf("Can not delete sem segment\n");
    return 0;
}
