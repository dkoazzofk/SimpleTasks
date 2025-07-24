#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_SIZE 1024

int main(){
    int shmid;
    key_t key = ftok("/shmfile", 65);

    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    char *buf = (char *) shmat(shmid, NULL, 0);

    printf("Accepted message: %s\n", buf);

    shmdt(buf);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}