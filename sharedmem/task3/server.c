#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

#define SHM_SIZE 1024

struct message{
    long mtype;
    int SHMessage;
};

int main(){
    int msgid;
    struct message msg;
    key_t message_key = ftok("/msgqueue", 66);

    msgid = msgget(message_key, 0666 | IPC_CREAT);
    if (msgid == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    int shmid;
    key_t key = ftok("/shmfile", 65);
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1){
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    msg.SHMessage = shmid;
    msg.mtype = 1;
    if (msgsnd(msgid, &msg, sizeof(msg.SHMessage), 0) == -1){
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    getchar();

    char *buf = (char *) shmat(shmid, NULL, 0);

    printf("Enter message: ");
    fgets(buf, SHM_SIZE, stdin);

    shmdt(buf);

    return 0;
}