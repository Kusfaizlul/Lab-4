GNU nano 4.8                                                                                                        Soc.c
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
        int socket_desc, new_socket, c;
        struct sockaddr_in server,client;
        char messages[2000];

        //Create Socket
        socket_desc = socket(AF_INET,SOCK_STREAM,0);
        if(socket_desc == -1)
                printf("Could not create socket");

        //Prepare the sockaddr_in structure
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(8888);

        //Bind
        if(bind(socket_desc,(struct sockaddr*)&server,sizeof(server)) < 0 ){
                puts("bind failed");
                return 1;
        }

        //Listen
        listen(socket_desc,3);

        //Accept and incoming connection
        puts("Waiting dor incoming connections..");
        c = sizeof(struct sockaddr_in);
        while( (new_socket=accept(socket_desc, (struct sockaddr*)&client,(socklen_t *)&c))){
                if ( recv(new_socket,messages,2000,0) < 0 ){
                        puts("\n Recv fails");
                        return 1;
                }
                puts("\n diterima ..... ");
                puts("\n Ayat dia ");
                puts(messages);

                char msg[]="\n Nombor yang dail tiada dlm talian";

                send(new_socket,msg,sizeof(msg),0);
        }
}
