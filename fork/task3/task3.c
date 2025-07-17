#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NULL ((void *)0)

int main(){
    pid_t pid = fork();
    int n = 10;
    int sumNeChet = 0;
    int sumChet = 0;

    if (pid == 0){
        for (int j = 2; j <= 10; j+=2){
            sumChet += j;
        }
        printf("CHILD process Chet = %d\n", sumChet);
    } else if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    } else {
        for (int i = 1; i <= 10; i+= 2){
            sumNeChet += i;
        }
        printf("PARENT process Ne chet = %d\n", sumNeChet);
    }
    wait(NULL);

    return 0;
}