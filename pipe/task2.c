#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int pipefd[2]; // 0 - read 1 - write
    int pipefd2[2];
    char buffer[80] = "First message from Parent";
    char buffer2[80] = "Second message from Child";

    if (pipe(pipefd) == -1 || pipe(pipefd2) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == 0){
        close(pipefd[1]);
        close(pipefd2[0]);
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child process accepted: %s\n", buffer);

        write(pipefd2[1], buffer2, strlen(buffer2) + 1);
        printf("Child process say: %s\n", buffer2);
    } else if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[0]);
        close(pipefd2[1]);
        write(pipefd[1], buffer, strlen(buffer) + 1);
        printf("Parent process say: %s\n", buffer);

        read(pipefd2[0], buffer2, sizeof(buffer2));
        printf("Parent process accepted: %s\n", buffer2);
        wait(NULL);
    }
}