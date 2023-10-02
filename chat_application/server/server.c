//
// Created by kunal on 2/10/23.
//
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include <unistd.h>

#define port 8000
int main()
{
    int size =0;
    int fd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server_addr , c_addr;
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server_addr.sin_zero , 0 , sizeof(server_addr.sin_zero));

    if(bind(fd , (struct sockaddr *)&server_addr , sizeof(server_addr))<0)perror("binding failed");
    listen(fd ,10);

    int client_fd=accept(fd , (struct sockaddr *)&c_addr , &size);
    if(client_fd<0)perror("connection failed");
    printf("client connected");
    char buffer[100];
    while(1){
        memset(buffer,0 ,sizeof(buffer));
        ssize_t bytes=recv(client_fd, buffer , sizeof(buffer),0);
        if(bytes<0)perror("client disconnected");
        printf("Client : %s \n" , buffer);
        printf("server :");
        fgets(buffer , sizeof(buffer),stdin );
        send(client_fd , buffer , strlen(buffer),0);

    }
    close(fd);
    close(fd);
}
