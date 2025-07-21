#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int pipefd[2];
    char buff[80] = "Test message";

    if(pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == 0){
        close(pipefd[1]);
        read(pipefd[0], buff, sizeof(buff)); //Если использовать strlen тут, то вернет длину строки ДО записи
        printf("Read from parent: %s\n", buff);
        close(pipefd[0]);
    } else if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    } else {
        close(pipefd[0]);
        write(pipefd[1], buff, strlen(buff) + 1); //Если использовать sizeof тут, то запишет все 80 байт, даже если строка короче
        printf("Parent say: %s\n", buff);
        close(pipefd[1]);
        wait(NULL);
    }
}