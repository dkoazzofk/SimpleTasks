#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/msg.h>

#define SHM_SIZE 1024

struct message{
    long mtype;
    int SHMessage;
};

int main(){
    int msgid, shmid;
    struct message msg;
    key_t message_key = ftok("/msgqueue", 66);

    msgid = msgget(message_key, 0666 | IPC_CREAT);

    if (msgrcv(msgid, &msg, sizeof(msg.SHMessage), 1, 0) == -1){
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    shmid = msg.SHMessage;

    char *buf = (char *) shmat(shmid, NULL, 0);

    printf("Accepted message: %s\n", buf);

    shmdt(buf);

    shmctl(shmid, IPC_RMID, NULL);

    if (msgctl(msgid, IPC_RMID, NULL) == -1){
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}