#ifndef HTTP_H
#define HTTP_H

#define max_length 100000

typedef struct response{
    char method[10];
    int code;
    char* status;
    char *contenttype;
    int length;
    char connection[10];
    unsigned char *content;
}response;

void sendText(response *,char *);
void sendBytes(response *,char *);
void generateBody(response *, char *);
void makeResponseString(response *, char *,int *);
void convert(char *,char *,char *);
#endif


