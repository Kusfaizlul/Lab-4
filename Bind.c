#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc, char *argv[]){
	int socket_desc, new_soc ,c;
	struct sockaddr_in server, client;

	//Creating socket
	socket_desc = socket(AF_INET,SOCK_STREAM,0);

	if (socket_desc == -1 )
		printf(" Could not create socket\n");

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8888);

	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server,sizeof(server)) < 0 ){
		puts("\n bind failed");
	}
	
	//Listen
	if( listen(socket_desc , 3) < 0 ){
		puts("\n Listen failed");
	}

	puts("\n Waiting for incoming connections.. ");

	c = sizeof(struct sockaddr_in);

	new_soc = accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c);

	if (new_soc < 0 ){
		perror (" accept failed");}


	return 0;
}
