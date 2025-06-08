#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr, clientaddr;

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server started. Waiting connection...\n");

    socklen_t len = sizeof(clientaddr);
    int recv_len;
    char check[] = "SERVERCHECKING\n";
    while(1){
        if((recv_len = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&clientaddr, &len)) < 0){
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }

        printf("Recieved data from client: %s\n", buffer);
        char newbuffer[1024];
        snprintf(newbuffer, sizeof(newbuffer), "%s %s", buffer, check);

        if(sendto(sockfd, newbuffer, strlen(newbuffer) + 1, 0, (struct sockaddr *)&clientaddr, len) < 0){
            perror("sendto");
            exit(EXIT_FAILURE);
        }
    }
    close(sockfd);
    return 0;
}
