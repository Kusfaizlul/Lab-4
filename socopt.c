#include<stdio.h>
#include<string.h> //strlen 
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h> //write
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	int soc_des,new_soc,c;
	struct sockaddr_in server,client;
	char *msg;
	int optval;

	socklen_t optlen = sizeof(optval);

	//Creating socket
	soc_des = socket(AF_INET,SOCK_STREAM,0);
	if(soc_des == -1){
		printf("\n Could not creating socket :(");
		return 1;
	}

	//Check the status for the keepalive option
	if(getsockopt(soc_des,SOL_SOCKET,SO_KEEPALIVE, &optval , &optlen ) < 0 ){
		perror("getsockopt()");
		close(soc_des);
		exit(EXIT_FAILURE);
	}
	printf("\n SO_KEEPALIVE is %s ",(optval ?"ON" : "OFF"));

	/* Set the option active*/
	optval = 1;
	optlen = sizeof(optval);

	if(setsockopt(soc_des,SOL_SOCKET,SO_KEEPALIVE, &optval , optlen ) < 0){
		perror("setsockopt()");
		close(soc_des);
		exit(EXIT_FAILURE); 
	}
	printf("\n SO_KEEPALIVE is %s \n ",(optval ?"ON" : "OFF"));
	return 0;
}
