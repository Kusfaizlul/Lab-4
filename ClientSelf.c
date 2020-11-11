#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
        int soc;
        struct sockaddr_in server;
        char serply[2000],msg[2000],temp[10] = "Client 1" ,k[] = "STOP";

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
        puts("   Enter 'stop' to stop chating  " );

        send(soc,temp,sizeof(temp),0);

        int i = 0;
        while(1){
                if ( i == 0){
                        printf(" Say Hi : ");}
                else
                        printf("\n Reply  : ");

                fgets(msg,sizeof(msg),stdin);

                if ( send(soc ,msg,2000,0) < 0 ){
                        perror("\n Send failed\n");
                        close(soc);
                        exit(EXIT_FAILURE);
                }

                if (strcmp(msg,"stop\n") == 0){ // If user input stop the program will exit
                        printf("\n --- BYE BYE --- \n");
                        break;
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
}
