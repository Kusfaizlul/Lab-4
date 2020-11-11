#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

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
        server.sin_addr.s_addr = inet_addr("192.168.14.10");
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

        c = sizeof(struct sockaddr_in);

        while(1){
                new_soc = accept(soc,(struct sockaddr *)&client,(socklen_t*)&c); //Accept New Con
                if ( new_soc < 0){
                        perror(" No Connecction");
                        puts("\n\n Waiting For New Connection ...");
                        exit(EXIT_FAILURE);
                }
                int pid = fork();

                if (pid < 0){
                        perror("\n Fork Error");
                        exit(EXIT_FAILURE);
                }

                else if ( pid == 0){ // Child process
                        close(soc);

                        char im[2000], name[10]; // Temporary hold from client

                        recv(new_soc,name,2000,0);


                        printf("\n %s Join The Chat\n", name);
                        int i = 0;
                        while(1){//Send and recv department
                                recv(new_soc,text,2000,0);

                                if(strcmp(text,"stop\n")== 0){
                                        printf("\n %s Left The Chat", name);
                                        break;
                                        }

                                else{
                                        printf("\n %s : %s",name,text);
                                        printf(" \n Reply    : ");
                                        fgets(reply,sizeof(reply),stdin);
                                        send(new_soc,reply,2000,0);
                                }
                        }
                }

                else
                        close(new_soc);
        }
        close(soc);

        exit(EXIT_SUCCESS);
}
