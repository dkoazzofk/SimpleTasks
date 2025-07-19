#include <stdio.h>
#include <pthread.h>

#define NULL ((void *)0)

#define NUM_THREADS 5

void* print_func(void* arg){
    int thread_num = *(int*)arg;
    printf("Thread %d: TID = %lu\n", thread_num, pthread_self());
    return NULL;
}

int main(){
    pthread_t tids[NUM_THREADS];
    int thread_num[NUM_THREADS];

    for(int i = 0; i < NUM_THREADS; i++){
        thread_num[i] = 1 + i;
        if (pthread_create(&tids[i], NULL, print_func, &thread_num[i]) != 0){
            perror("FAILED pthread_create\n");
            return 1;
        }
    }

    for(int i = 0; i < NUM_THREADS; i++){
        pthread_join(tids[i], NULL);
    }
 
    return 0;
}