#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h> // for sockaddr struct
#include <arpa/inet.h> // for htons() and inet_*
#include <netdb.h> // for hostname functions
#include <string.h>

#define PORT 4242
#define HOSTNAME "morrigansub"
#define GROWTH 5

/*
    Basic Server Setup
    -create socket
    -bind address to socket
    -listen for connections, just setting up a willingness to connect
    -accept a new connection
    -send/recv depending
    -shutdown connetion
    -close socket

*/




int main(){

    int sockfd;
    struct hostent* hostp;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    struct in_addr* ip_addr;
    char buffer[1024];
    char send_message[] = "message recevied";
    int clilen = sizeof(client_addr);

    hostp = gethostbyname(HOSTNAME);
    ip_addr = (struct in_addr*)hostp->h_addr_list[0];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = ip_addr->s_addr;
    memset(&server_addr.sin_zero, '\0', 8);


    
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));


    listen(sockfd, GROWTH);

    
    while (1){
        
        accept(sockfd, (struct sockaddr*)&client_addr, &clilen);
        printf("[*] Connection established: %s", inet_ntoa(client_addr.sin_addr));

        recv(sockfd, &buffer, 1024, 0);
        printf("[*] Recv: %s", buffer);
        send(sockfd, send_message, sizeof(send_message), 0);
        

    }
    
    



}
