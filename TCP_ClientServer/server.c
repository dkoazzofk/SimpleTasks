#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(){
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    //опция, чтобы порт освобождался сразу после выключения сервера
    int opt = 1;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        perror("setsockopt");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    //привязка к ip
    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    //заставляем слушать подключения
    if(listen(sockfd, 5) < 0){
        perror("listen");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server started.\nWaiting connection...\n");

    socklen_t addr_len = sizeof(cliaddr);
    int client_socket = accept(sockfd, (struct sockaddr *)&cliaddr, &addr_len);
    if(client_socket < 0){
        perror("accept");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while(1){
        int valread = read(client_socket, buffer, 1024);
        printf("Messager from client: %s\n", buffer);

        send(client_socket, buffer, strlen(buffer), 0);
        printf("Message was sended\n"); 
    }
    
    close(sockfd);
    close(client_socket);
    return 0;
}
