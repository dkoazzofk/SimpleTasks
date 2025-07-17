#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define NULL ((void *)0)

int main(){
    for(int i = 1; i <= 3; i++){
        pid_t pid = fork();

        if (pid == 0){
            printf("CHILD process %d, PID = %d, PPID = %d\n", i, getpid(), getppid());
            return 0;
        } else if (pid < 0){
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }
    while(wait(NULL) > 0);

    printf("PARENT process, PID = %d\n", getpid());
    return 0;
}