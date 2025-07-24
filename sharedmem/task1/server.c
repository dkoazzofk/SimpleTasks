#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

#define SHM_SIZE 1024

int main(){
    int shmid;
    key_t key = ftok("/shmfile", 65);

    shmid = shmget(key, SHM_SIZE, 0666|IPC_CREAT);
    if (shmid == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    char *buf = (char *) shmat(shmid, NULL, 0);

    printf("Enter message: ");
    fgets(buf, SHM_SIZE, stdin);

    // printf("Message sended in shared memory. Press Enter to exit...\n");
    // getchar();

    shmdt(buf);

    return 0;
}