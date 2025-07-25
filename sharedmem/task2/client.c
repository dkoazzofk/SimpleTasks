#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>

#define SHM_SIZE 1024

int main(){
    int shmid;
    key_t key = ftok("/shmfile", 65);

    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    int* counter = (int *) shmat(shmid, NULL, 0);

    sem_t *sem = sem_open("/mysem", 0);
    if (sem == SEM_FAILED){
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    
    pid_t pid = fork();

    if (pid == 0){
        printf("child process\n");
        sem_wait(sem);
        (*counter)++;
        sem_post(sem);
    } else if (pid < 0){
        perror("pid");
        exit(EXIT_FAILURE);
    } else{
        printf("parent process\n");
        sem_wait(sem);
        (*counter)++;
        sem_post(sem);
    }

    printf("Counter = %d\n", *counter);

    shmdt(counter);

    sem_close(sem);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}