#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NULL ((void *)0)

int main(){
    pid_t pid1 = fork();
    pid_t pid2, pid3;

    if (pid1 == 0){

        printf("Level 1 CHILD PID = %d, PPID = %d\n", getpid(), getppid());

        pid2 = fork();
        if (pid2 == 0){

            printf("Level 2 CHILD PID = %d, PPID = %d\n", getpid(), getppid());

            pid3 = fork();
            if (pid3 == 0){

                printf("Level 3 CHILD PID = %d, PPID = %d\n", getpid(), getppid());

            } else if (pid3 > 0){
                printf("Level 3 PARENT PID = %d\n", getpid());
                wait(NULL);
            }

        } else if (pid2 > 0){
            printf("Level 2 PARENT PID = %d\n", getpid());
            wait(NULL);
        }

    } else if (pid1 > 0){
        printf("Level 1 PARENT PID = %d\n", getpid());
        wait(NULL);
    }

    return 0;
}