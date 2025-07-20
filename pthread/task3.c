#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NULL ((void *)0)

#define NUMBER 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int flag = 0;

void* producer(void* arg){
    int* buffer = (int*)arg;
    sleep(2);
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < NUMBER; i++){
        buffer[i] = i;
    }
    flag = 1;
    printf("PRODUCER: Data ready\n");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* consumer(void* arg){
    int* buffer = (int*)arg;
    pthread_mutex_lock(&mutex);
    while (!flag){
        printf("CONSUMER: Waiting data\n");
        pthread_cond_wait(&cond, &mutex);
    }
    printf("CONSUMER: Data accepted\n");
    for (int i = 0; i < NUMBER; i++){
        printf("BUFFER = %d\n", buffer[i]);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    pthread_t prod, con;
    int buffer[NUMBER];

    if (pthread_create(&con, NULL, producer, buffer) != 0){
        perror("FAILED pthread create\n");
        return 1;
    }

    if (pthread_create(&prod, NULL, consumer, buffer) != 0){
        perror("FAILED pthread create\n");
        return 1;
    }

    pthread_join(prod, NULL);
    pthread_join(con, NULL);

    return 0;
}