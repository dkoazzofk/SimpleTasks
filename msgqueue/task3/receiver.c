#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define BUF_SIZE 100

struct message{
    long mtype;
    char mtext[BUF_SIZE];
};

int main(){
    int msgid;
    int flag = 0;
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

    while(!flag){

        if (msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0) == -1){
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Sender: %s\n", msg.mtext);

        printf(">> ");
        fgets(msg.mtext, BUF_SIZE, stdin);
        if (strncmp(msg.mtext, "exit", 4) == 0) flag = 1;
        msg.mtype = 2;
        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1){
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1){
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}