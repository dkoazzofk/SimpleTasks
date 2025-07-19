#include <stdio.h>
#include <pthread.h>

#define NULL ((void *)0)

#define N 10
#define M 2

int sum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* arg){
    int* array = (int*)arg;
    int localsum = 0;

    for(int i = 0; i < N/M; i++){
        localsum += array[i];
    }

    pthread_mutex_lock(&mutex);
    sum += localsum;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    int array[N] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int func_array1[N/M];
    int func_array2[N/M];

    for(int i = 0; i < N/M; i++){
        func_array1[i] = array[i];
    }

    for(int i = 0; i < N/M; i++){
        func_array2[i] = array[i + N/M];
    }

    pthread_t tid, tid2;

    if (pthread_create(&tid, NULL, thread_func, func_array1) != 0){
        perror("FAILED pthread_create\n");
        return 1;
    }

    if (pthread_create(&tid2, NULL, thread_func, func_array2) != 0){
        perror("FAILED pthread_create\n");
        return 1;
    }

    pthread_join(tid, NULL);
    pthread_join(tid2, NULL);

    printf("SUM = %d\n", sum);
    return 0;
}