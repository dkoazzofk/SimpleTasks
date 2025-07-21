#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NULL ((void *)0)
#define ARRAY_SIZE 100
#define NUM_THREADS 4

pthread_barrier_t barrier;
int array[ARRAY_SIZE];

void* fill_array(void* arg){
    int threadID = *(int*)arg;
    int start = threadID * (ARRAY_SIZE / NUM_THREADS);
    int end = start + (ARRAY_SIZE / NUM_THREADS);

    printf("Thread %d Fill array [%d..%d]\n", threadID, start, end - 1);

    for(start; start < end; start++){
        int random = rand() % 100;
        array[start] = random;
    }
    pthread_barrier_wait(&barrier); //Поток останавливается здесь, пока все 
                                    //остальные потоки (и main) не достигнут барьера.
    return NULL;
}

int main(){
    pthread_t tid[NUM_THREADS];
    int threadsID[NUM_THREADS];

    pthread_barrier_init(&barrier, NULL, NUM_THREADS + 1);
    for (int i = 0; i < NUM_THREADS; i++){
        threadsID[i] = i;
        if (pthread_create(&tid[i], NULL, fill_array, &threadsID[i]) != 0){
            perror("FAILED pthread create\n");
            return 1;
        }
    }

    pthread_barrier_wait(&barrier); //Дождаться, пока все рабочие потоки закончат заполнение массива.
    sleep(2);
    printf("All threads complete work\n");

    for (int i = 0; i < NUM_THREADS; i++){
        pthread_join(tid[i], NULL);
    }

    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++){
        sum += array[i];
    }
    printf("SUM = %d\n", sum);
}