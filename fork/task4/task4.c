#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NULL ((void *)0)

int main(){
    pid_t pid = fork();

    if (pid == 0){
        printf("CHILD process, PID = %d, PPID = %d\n", getpid(), getppid());
        sleep(2);
        printf("CHILD FINISHED, NEW PID = %d\n", getppid());
        exit(EXIT_SUCCESS);
    } else if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    } else {
        printf("PARENT process, PID = %d\n", getpid());
    }
}