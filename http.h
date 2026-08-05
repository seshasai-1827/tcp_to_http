#ifndef HTTP_H
#define HTTP_H

#define max_length 1000

typedef struct response{
    char method[10];
    int code;
    char* status;
    char *contenttype;
    int length;
    char connection[10];
    char *content;
}response;

void generateBody(response *, char *);
void makeResponseString(response *, char *);
void convert(char *,char *,char *);
#endif


