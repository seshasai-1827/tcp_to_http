#include "http.h"
#include <string.h>
#include <stdio.h>

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
                strcpy(path,temp);
                break;
            }
        }
        temp[i++] = clientrequest[it++];
    }
}

void generateBody(response *clientresp,char* path){
    //define the various controllers here
    clientresp->content = "page not found";
    clientresp->contenttype = "text";
    clientresp->code = 404;
    clientresp->status = path?"OK":"NO";
    if (strcmp(path, "/wow") == 0){
        clientresp->contenttype = "text";
        clientresp->code = 200;
        clientresp->content = "wow";//can be a function
    }
    if (strcmp(path, "/favicon.ico") == 0){
        clientresp->contenttype = "jpeg";
        clientresp->code = 200;
        clientresp->content = "./static/meme.jpeg";
    }
    clientresp->length = strlen(clientresp->content);       
}


void makeResponseString(response *clientresp,char *response_str){
// // HTTP/1.1 200 OK\r\n
// // Date: Mon, 13 Jul 2026 22:15:30 GMT\r\n
// // Server: Apache/2.4.41 (Ubuntu)\r\n
// // Content-Type: application/json; charset=UTF-8\r\n
// // Content-Length: 41\r\n
// // \r\n
// // {"status":"success","message":"Data found"}

    snprintf(response_str,400,
        "HTTP/1.1 %d %s\r\n"
        "Content-Type:%s\r\nContent-Length:%d\r\n\r\n%s"
        ,clientresp->code,clientresp->status,clientresp->contenttype,clientresp->length,clientresp->content);    
}