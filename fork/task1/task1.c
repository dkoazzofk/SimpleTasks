#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NULL ((void *)0)

int main(){
    pid_t pid1;

    pid1 = fork();

    if (pid1 == 0){
        printf("CHILD process, PID = %d, PPID = %d\n", getpid(), getppid());
        exit(EXIT_SUCCESS);
    } else if (pid1 > 0) {
        printf("PARENT process, PID = %d, CHILD process = %d\n", getpid(), pid1);
        wait(NULL);
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}