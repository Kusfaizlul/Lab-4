#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
	int soc,i=0;
	struct sockaddr_in server;
	char serply[2000],msg[2000],temp[50] = "Client 1 Left The Chat\n" ,k[] = "STOP";

	//Creating socket
	soc = socket(AF_INET,SOCK_STREAM,0);

	if (soc == -1 ){
		perror("\n Creating Socket Error ");
		exit(EXIT_FAILURE);
	}

	server.sin_addr.s_addr = inet_addr("192.168.14.10");
	server.sin_family = AF_INET;
	server.sin_port = htons(8190);

	//Connect to remote server
	if (connect(soc ,(struct sockaddr *)&server ,sizeof(server)) < 0) {
		perror("\n Connection error ");
		close(soc);
		exit(EXIT_FAILURE);
	}

	puts("\n---- Congrats!Your socket is connected ----");
	puts("   Enter 'STOP' to stop chating  " );

	char im[]="Client 1 join the chat.";
	send(soc,im,sizeof(im),0);

	while(i != -1){
		if ( i == 0){
			printf(" Say Hi : ");}
		else
			printf("\n Reply : ");

		fgets(msg,sizeof(msg),stdin);

		if (strcmp(msg,k) == 10){
			strcpy(msg,temp);

			if ( send(soc ,msg,2000,0) < 0 ){
	       	                perror("\n Send failed\n");
               		        close(soc);
                        	exit(EXIT_FAILURE);
			}
			close(soc);
			exit(EXIT_SUCCESS);
		}

		if ( send(soc ,msg,2000,0) < 0 ){
			perror("\n Send failed\n");
			close(soc);
			exit(EXIT_FAILURE);
		}

		//Receive a reply from the server
		if ( recv(soc, serply , 2000 , 0 ) < 0 ){
			perror("\n Receving Failed\n");
			close(soc);
			exit(EXIT_FAILURE);
		}
		printf("\n Server : %s ",serply);

		i = 1;
	}

	close(soc);
	exit(EXIT_SUCCESS);
}
