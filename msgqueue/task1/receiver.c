#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUF_SIZE 100

struct message{
    long mtype;
    char mtext[BUF_SIZE];
};

int main(){
    int msgid;
    struct message msg;

    key_t key = ftok("sender", 65);

    if (key == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1){
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Message accepted: %s\n", msg.mtext);

    if (msgctl(msgid, IPC_RMID, NULL) == -1){
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}