#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 80

int main(){
    int pipefd[2];
    char parent_msg[BUF_SIZE] = "Hello";
    char child_buffer[BUF_SIZE];

    if (pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == 0){
        close(pipefd[1]);
        read(pipefd[0], child_buffer, sizeof(child_buffer));
        printf("Cathced message lenght: %ld\n", strlen(child_buffer));
        read(pipefd[0], child_buffer, sizeof(child_buffer));
        printf("Cathed another one message, his lenght: %ld\n", strlen(child_buffer));
        close(pipefd[0]);
    } else if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[0]);
        write(pipefd[1], parent_msg, strlen(parent_msg) + 1);
        printf("Parent process say: %s\n", parent_msg);
        sleep(1);
        strcpy(parent_msg, "Hello another one");
        write(pipefd[1], parent_msg, strlen(parent_msg) + 1);
        printf("Parent say another one: %s\n", parent_msg);
        close(pipefd[1]);
        wait(NULL);
    }
}