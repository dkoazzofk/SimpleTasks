#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(){
    int sockfd;
    char buffer[1024];
    struct sockaddr_in clientaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd < 0){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&clientaddr, 0, sizeof(clientaddr));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(8080);
    inet_aton("127.0.0.1", &clientaddr.sin_addr.s_addr);

    socklen_t len = sizeof(clientaddr);

    while(1){
        printf("Enter message: ");
        fgets(buffer, 1024, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if(sendto(sockfd, buffer, strlen(buffer) + 1, 0, (struct sockaddr *)&clientaddr, len) < 0){
            perror("sendto");
            exit(EXIT_FAILURE);
        }

        if(recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr *)&clientaddr, &len) < 0){
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }
        printf("Recieved message from server: %s", buffer);
    }

    close(sockfd);
    return 0;
}
