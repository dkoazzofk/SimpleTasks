#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 80

int main(){
    int pipefd[2];
    char msg_for_1[BUF_SIZE] = "hello";
    char msg_for_2[BUF_SIZE];
    char msg_for_3[BUF_SIZE];
    char msg_for_4[BUF_SIZE];

    if (pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    pid_t pid2, pid3;

    if (pid == 0){
        read(pipefd[0], msg_for_2, sizeof(msg_for_2));
        printf("Child process 1 accept: %s\n", msg_for_2);

        pid2 = fork();
        if (pid2 == 0){
            read(pipefd[0], msg_for_3, sizeof(msg_for_3));
            printf("Child process 2 accept: %s\n", msg_for_3);
            
            pid3 = fork();
            if (pid3 == 0){
                read(pipefd[0], msg_for_4, sizeof(msg_for_4));
                printf("Child process 3 say: %s\n", msg_for_4);
            } else if (pid3 > 0){
                strcpy(msg_for_3, "BYE");
                write(pipefd[1], msg_for_3, strlen(msg_for_3) + 1);
                printf("Parent process 3 do: %s\n", msg_for_3);
            }

        } else if (pid2 > 0){
            strcpy(msg_for_2, "HELLO");
            printf("Parent process 2 do: %s\n", msg_for_2);
            write(pipefd[1], msg_for_2, strlen(msg_for_2) + 1);
        }

    } else if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[0]);
        write(pipefd[1], msg_for_1, strlen(msg_for_1) + 1);
        close(pipefd[1]);
        printf("Parent process 1 say: %s\n", msg_for_1);
    }
}