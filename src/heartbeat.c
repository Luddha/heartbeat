// main file for heartbeat


#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>


#include <common.h>
//#include "hb_server.h"

void usage(){
	printf("Usage: heartbeat  -i ip_address -p port\n\
		-i	ip address to listen on\n \
		-p	port number\n");
	exit(0);
}

// test 

int main(int argc, char **argv){

	int opt;
	char *optstring = "i:p:h";
	char ip[15];
	int port;

	while ((opt = getopt(argc, argv, optstring) != -1)){
		switch (opt){
			case 'i':
				strncpy(ip, opt, 15);
				break;
			case 'p':
				port = atoi(opt);
				break;
			case 'h':
				usage();
				break;
			default:
				usage();

		}
	}

// start of server	
	int sockfd;
	int client_fd;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char buffer[65535];
	int buf_size;

	strncpy(buffer, "Connection Successful!", 22);


	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_aton(ip, &server.sin_addr);

	if ((bind(sockfd, (struct sockaddr*)&server, sizeof(server))) < 0){
		error_msg("bind failed");
	}

	listen(sockfd, 5);

	while (1){
		client_fd = accept(sockfd, &client, sizeof(client));
		if (client_fd < 0){
			error_msg("failed to accept connection");
		}
		buf_size = send(client_fd, "Connection Successful!", 22, 0);
		if (buf_size < 0){
			error_msg("failed to send msg");
		}
		printf("msg sent to %s", inet_ntoa(client.sin_addr));

		buf_size = recv(client_fd, buffer, 65535, 0);
		if (buf_size < 0){
			error_msg("failed to recv msg");
		}
		printf("msg from %s:\n %s\n", inet_ntoa(client.sin_addr), buffer);

		close(client_fd);


	}


}
