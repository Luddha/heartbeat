#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include <common.h>


void start_server(char *ip, int port){
// start of server	
	int sockfd;
	int client_fd;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char buffer[65535];
	int buf_size;
	int socket_len = sizeof(client);


	strncpy(buffer, "Connection Successful!", 22);


	sockfd = socket(PF_INET, SOCK_STREAM, 0);

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_aton(ip, &server.sin_addr);
	memset(&server.sin_zero, 0, 8);

	if ((bind(sockfd, (struct sockaddr*)&server, sizeof(server))) < 0){
		error_msg("bind failed");
	}

	listen(sockfd, 5);
	printf("[*] Listening on port: %d\n", port);

	while (1){
		client_fd = accept(sockfd, (struct sockaddr*)&client, &socket_len);
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
