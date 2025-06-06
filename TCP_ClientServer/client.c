#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8080);

    if(inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0){
        perror("address");
        close(sockfd);
    }

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while(1){
        printf("Put your message: ");
        fgets(buffer, sizeof(buffer), stdin);
        send(sockfd, buffer, strlen(buffer), 0);
        
        read(sockfd, buffer, 1024);
        printf("Message from server: %s", buffer);
    }

    close(sockfd);
    return 0;
}
