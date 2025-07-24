#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

#define MSG_SIZE 100
#define QUEUE_NAME "/myqueue"

int main(){
    mqd_t mq;
    char buffer[MSG_SIZE];
    unsigned int prio;
    unsigned int flag = 0;

    mq = mq_open(QUEUE_NAME, O_RDWR | O_CREAT, 0666, NULL); //O_RDWR - для чтения и записи
    if (mq == (mqd_t)-1){                                   //O_CREAT - создаст очередь, если ее нет
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    while(!flag){
        if (mq_receive(mq, buffer, MSG_SIZE, &prio) == -1){
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }

        printf("Accepted message: %s\n", buffer);

        printf(">> ");
        fgets(buffer, MSG_SIZE, stdin);

        if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1){
            perror("mq_send");
            exit(EXIT_FAILURE);
        }

    }


    mq_close(mq);
    mq_unlink("sender");

    return 0;
}