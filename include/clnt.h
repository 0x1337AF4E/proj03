#ifndef CL_H
#define CL_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int get_request(char *url, char *port);
int isValidIP(char *ip);
int parseHeader(char *header);
char *splitKeyValue(char *line, int index);
void openFile();

FILE *fileptr;
char *ptr, *host;
char keys[][25] = {"Date: ", "Hostname: ", "Location: ", "Content-Type: "};
char contentFileType[100];
char path[1000];
char *fileName;	
char http_not_found[] = "HTTP/1.1 404 Not Found";
char location[] = "Location: ";
char contentType[] = "Content Type: ";
char *line, *key, *value;
char *host;
#endif
