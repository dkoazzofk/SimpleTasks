#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#define BUF_SIZE 100
#define MTYPE_NUM 3

struct message{
    long mtype;
    char mtext[BUF_SIZE];
};

int main(){
    int msgid;
    struct message msg;
    key_t key;

    key = ftok("sender", 65);
    if (key == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    for (int i = MTYPE_NUM; i >= 1; i--){
        if (msgrcv(msgid, &msg, sizeof(msg.mtext), i, IPC_NOWAIT) == -1){
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Accepted message %d: %s\n", i, msg.mtext);
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1){
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}