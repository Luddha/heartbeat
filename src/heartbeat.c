// main file for heartbeat


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <common.h>
#include <hb_server.h>

void usage(){
	printf("Usage: heartbeat  -i ip_address -p port\n\
		-i	ip address to listen on\n \
		-p	port number\n");
	exit(0);
}


int main(int argc, char **argv){

	int opt;
	char *optstring = "i:p:h";
	char ip[15];
	int port;

	while ((opt = getopt(argc, argv, optstring)) != -1){
		switch (opt){
			case 'i':
				strncpy(ip, optarg, 15);
				break;
			case 'p':
				port = atoi(optarg);
				break;
			case 'h':
				usage();
				break;
			default:
				usage();

		}
	}

	start_server(ip, port);

}
