#include "http.h"
#include <string.h>
#include <stdio.h>
#include<stdlib.h>


void convert(char *clientrequest,char *path,char *method){
    int it = 0,count = 0,i=0;
    char temp[max_length];
    while(clientrequest[it]!='\0'){
        if(clientrequest[it]==' '){
            count++;
            if(count==1){
                temp[i] = '\0';
                strcpy(method,temp);
                i = 0;
                it++;
            }
            if(count==2){
                temp[i] = '\0';
                strcpy(path,.temp);
                break;
            }
        }
        temp[i++] = clientrequest[it++];
    }
}

void generateBody(response *clientresp,char* path){
    //define the various controllers here

    if (strcmp(path, "/wow") == 0){
        clientresp->contenttype = "text/plain";
        clientresp->code = 200;
        sendText(clientresp,"wow");//can be a function
    }
    else if (strcmp(path, "/favicon.ico") == 0){
        clientresp->contenttype = "image/jpeg";
        clientresp->code = 200;
        sendBytes(clientresp,"./static/meme.jpeg");
    }
    else{
        clientresp->code = 404;
        clientresp->contenttype = "text/plain";
        clientresp->status = "not found";
        sendText(clientresp,"page not found");
    }   
}

void sendText(response* clientresp,char* respString){
    clientresp->status = "OK";
    clientresp->length = strlen(respString);
    int it = 0;
    unsigned char* buff = malloc(clientresp->length);
    while(it<clientresp->length){
        buff[it] = respString[it];
        it++;
    }
    clientresp->content = buff;
}

void sendBytes(response* clientresp,char* filePath){
    FILE* fptr = fopen(filePath,"rb");
    if(fptr==NULL){
        clientresp->code = 404;
        clientresp->contenttype = "text/plain";
        clientresp->status = "not found";
        sendText(clientresp,"page not found");
    }
    else{
        clientresp->code = 200;
        clientresp->status = "OK";
        long int len = 0,it = 0,ch;
        fseek(fptr,0,SEEK_END);
        len = ftell(fptr);//fetches size of file
        if(len<0){
            perror("file length error");
        }
        unsigned char* content = malloc(len);
        if(content==NULL){
            perror("unsuccessful malloc...");
        }
        fseek(fptr,0,SEEK_SET);//back to begining
        clientresp->length = fread(content,sizeof(char),len,fptr);
        clientresp->content = content;
        //free(content);
    }
    fclose(fptr);
}

void makeResponseString(response *clientresp,char *response_str,int* header_size){
// // HTTP/1.1 200 OK\r\n
// // Date: Mon, 13 Jul 2026 22:15:30 GMT\r\n
// // Server: Apache/2.4.41 (Ubuntu)\r\n
// // Content-Type: application/json; charset=UTF-8\r\n
// // Content-Length: 41\r\n
// // \r\n
// // {"status":"success","message":"Data found"}

    *header_size = snprintf(response_str,1024,
        "HTTP/1.1 %d %s\r\n"
        "Content-Type:%s\r\nContent-Length:%d\r\n\r\n"
        ,clientresp->code,clientresp->status,clientresp->contenttype,clientresp->length);    
}