#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

int main(int argc, char *argv[]){
	int socket_desc;
	struct sockaddr_in server;
	char* message;
	char server_reply[2000];

	//Creating socket
	socket_desc = socket(AF_INET,SOCK_STREAM,0);

	if (socket_desc == -1 )
		printf(" Could not create socket\n");

	server.sin_addr.s_addr = inet_addr("192.168.14.10");
	server.sin_family = AF_INET;
	server.sin_port = htons(22);

	//Connect to remote server
	if (connect(socket_desc ,(struct sockaddr*)&server ,sizeof(server)) < 0) {
		puts("\n connection error\n");
		return 1;
	}

	puts("\n Your socket is connected successfully\n");
	
	if ( send(socket_desc ,message, strlen(message),0) < 0 ){
		puts("\n Send failed\n");
		return 1;
	}
	puts("\n Data Send\n");

	//Receive a reply from the server
	if ( recv(socket_desc, server_reply, 2000 ,0) < 0 ){
		puts("\n receving fails\n");
		return 1;
	}
	puts("\n Receiving Successfully");
	//puts(server_reply);

//	close(socket_desc);
	return 0;
}
