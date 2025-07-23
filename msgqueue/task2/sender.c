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

    for (int i = 1; i <= MTYPE_NUM; i++){
        msg.mtype = i;
        printf("Put your %d message: ", i);
        fgets(msg.mtext, BUF_SIZE, stdin);

        if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1){
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        printf("Sended message %d: %s\n", i, msg.mtext);
    }

    return 0;
}