#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

#define MSG_SIZE 100
#define QUEUE_NAME "/myqueue"

int main(){
    unsigned int flag = 0;
    unsigned int prio;
    mqd_t mq;
    char buffer[MSG_SIZE];

    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, NULL);
    if (mq == (mqd_t)-1){
        perror("mq_open");
        exit(EXIT_FAILURE);
    }

    while(!flag){
        printf(">> ");
        fgets(buffer, MSG_SIZE, stdin);

        if (mq_send(mq, buffer, strlen(buffer) + 1, 0) == -1){
            perror("mq_send");
            exit(EXIT_FAILURE);
        }

        if (mq_receive(mq, buffer, MSG_SIZE, &prio) == -1){
            perror("mq_receive");
            exit(EXIT_FAILURE);
        }

        printf("Accepted message: %s\n", buffer);
    }

    mq_close(mq);
    return 0;
}