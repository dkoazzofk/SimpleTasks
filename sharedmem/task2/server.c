#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

#define SHM_SIZE 1024

int main(){
    int shmid;
    key_t key = ftok("/shmfile", 65);

    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    int *couter = (int *) shmat(shmid, NULL, 0);

    sem_t *sem = sem_open("/mysem", O_CREAT, 0666, 1);
    if (sem == SEM_FAILED){
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    printf("Wait couner. Press Enter to continue\n");
    getchar();

    printf("Server: counter = %d\n", *couter);

    getchar();

    shmdt(couter);

    return 0;
}