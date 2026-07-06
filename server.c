#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include<stdlib.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include<string.h>

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
    while(1){
        
        int max_length = 1000;
        char buff[max_length];
        
        rec_len = recv(clientfd,(void*)buff,max_length,0);
        printf("length of message : %d",rec_len);
        if(rec_len<0){
            
            perror("recv");
        }
        buff[rec_len] = '\0';
        puts(buff);
        sleep(1);
    }
}