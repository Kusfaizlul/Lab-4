#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc, char *argv[]){
	int socket_desc;
	struct sockaddr_in server;

	//Creating socket
	socket_desc = socket(AF_INET,SOCK_STREAM,0);

	if (socket_desc == -1 )
		printf(" Could not create socket\n");

	server.sin_addr.s_addr = inet_addr("192.168.14.10");
	server.sin_family = AF_INET;
	server.sin_port = htons(22);

	//Connect to remote server
	if (connect(socket_desc ,(struct sockaddr*)&server ,sizeof(server)) < 0) {
		puts("connection error");
		return 1;
	}

	puts(" Your socket is connected successfully\n");
	return 0;
}
