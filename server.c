#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>    
#include <sys/socket.h>
#include<stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include<string.h>
#include"http.h"
#define max_length  1000
//connect() is used by client?

int main(){
    int sockfd,sock,request,clientfd,rec_len,backlog = 10;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);//socket file descriptor
    if(sockfd<0){
        perror("socket");
    } 


    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8080);//network address of port:8080 (big endian)
    sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//assigning the network address of localhost
    
    sock = bind(sockfd,(struct sockaddr*)&sin,sizeof(sin));//socket binded
    if(sock<0){
        perror("failed bind");
    }

    while(1){
        
        char buff[max_length];
        char path[50];
        char rest[10];
        char response_buffer[400];
        char method[10];

        response *clientresp = malloc(sizeof(response));
        printf("listening...\n");
        request = listen(sockfd,backlog);//or poll?
        if(request<0){
            perror("listen");
        }

        struct sockaddr_in client_socket;
        socklen_t client_len = sizeof(client_socket);
        clientfd = accept(sockfd,(struct sockaddr*)&client_socket,&(client_len));
        if(clientfd<0){
            perror("accept");
        }
        printf("accepted client connection : %d\n",clientfd);

        rec_len = recv(clientfd,(void*)buff,max_length-1,0);
        buff[rec_len] = '\0';
        printf("message : %s\n",buff);
        if(rec_len<0){
            perror("recv");
        }

        
        convert(buff,path,method);
        generateBody(clientresp,path);
        makeResponseString(clientresp,response_buffer);
        printf("\nhttpreq : %s\n",path);
        send(clientfd,response_buffer,sizeof(response_buffer),0);
        close(clientfd);
        
    }
}
