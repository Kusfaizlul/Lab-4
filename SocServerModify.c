#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc, char *argv[]){
        int soc, new_soc ,c,optval = 1;
        struct sockaddr_in server, client;
        char text[2000], reply[2000];

        socklen_t optlen = sizeof(optval);

        //Creating socket
        soc = socket(AF_INET,SOCK_STREAM,0);

        if (soc == -1 )
                printf("\n Could not create socket ");

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(8190);

        //Socket Option
        if(setsockopt(soc,SOL_SOCKET,SO_KEEPALIVE,&optval,optlen) < 0 ){
                perror("\n Invalid Opt");
                close(soc);
                exit(EXIT_FAILURE);
        }
        printf("\n KeepAlive is %s ",(optval ?"ON" : "OFF"));

        //Bind
        if( bind(soc,(struct sockaddr *)&server,sizeof(server)) < 0 ){
                perror("\n bind failed");
                close(soc);
                exit(EXIT_FAILURE);
        }

        //Listen
        if( listen(soc , 10) < 0 ){
                perror("\n Listen failed");
                close(soc);
                exit(EXIT_FAILURE);
        }

        puts("\n Waiting for incoming connections.. ");

        //Accept
        c = sizeof(struct sockaddr_in);
        char buf[] = "Client x Left The Chat";
        int loop = 0;

        while(loop != -1)
        {
                new_soc = accept(soc,(struct sockaddr *)&client,(socklen_t*)&c);
                if ( new_soc > 0){
                        char im[2000];
                        recv(new_soc,im,2000,0);
                        printf("\n %s",im);
                        //Send and Receive
                        int i = 99;
                        while(i != 0 ){
                                recv(new_soc,text,2000,0);
                                int a = strncmp(text,buf,6);

                                if( a == 0){
                                        printf("\n Client : %s",text);
                                        printf("\n Waiting for new connection..");
                                        break;
                                }

                                else{
                                        printf("\n Client : %s",text);
                                        printf(" \n Reply : ");
                                        fgets(reply,sizeof(reply),stdin);
                                        send(new_soc,reply,2000,0);
                                }
                        }

                }
                else
                        printf("\n Waiting for new connection..");
        }
        close(soc);
        exit(EXIT_SUCCESS);
}

