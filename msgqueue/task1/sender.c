#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#define BUF_SIZE 100

struct message{
    long mtype;
    char mtext[BUF_SIZE];
};

int main(){
    key_t key = ftok("sender", 65);
    int msgid;
    struct message msg;

    if(key == -1){
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1){
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    msg.mtype = 1;

    printf("Put your message: ");
    fgets(msg.mtext, BUF_SIZE, stdin);

    if (msgsnd(msgid, &msg, sizeof(msg.mtext), 0) == -1){
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Message send: %s\n", msg.mtext);

    return 0;
}