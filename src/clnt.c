#include "../include/clnt.h"

int get_request(char *url, char *port){
	int sockfd, bindfd;
	char *ptr, *host;
	char getrequest[1024];
	struct sockaddr_in addr;

	if(isValidIP(url)){
		sprintf(getrequest, "GET / HTTP1.1\nHOST: %s\n\n", url);
	} else {
		if((ptr == strstr(url, "/")) == NULL){
		sprintf(getrequest, "GET / HTTP1.1\nHOST: %s\n\n", url);
		} else {
		strcpy(path, ptr);
		host =strtok(url, "/");
		sprintf(getrequest, "GET / HTTP1.1\nHOST: %s\n\n", url);
		}
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("Error creating the socket...\n");
		exit(1);
	}
	printf("Socket created...\n");

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(url);
	addr.sin_port = htons(atoi(port));
	
	if(connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		printf("Connection Error!\n");
		exit(1);
	}
	printf("Connection succesful...\n\n\n");
	ptr = strtok(path, "/");
	strcpy(path, ptr);
	
	write(sockfd, getrequest, strlen(getrequest));
	return sockfd;
}

int isValidIP(char *ip){
	struct sockaddr_in addr;
	int valid = inet_pton(AF_INET, ip, &(addr.sin_addr));
	return valid != 0;
}

int parseHeader(char *header){
	char *line, *key, *value;
	char temp[100];
	int i = 0;
	line = strtok(header, "\n");
	while(line != NULL){
		printf("%s\n", line);
		strcpy(temp, line);
		value = splitKeyValue(line, i);
	if(i == 3){
		strcpy(contentFileType, value);
	}
		line = strtok(NULL, "\n");
		i++;
	}
	for(i=0; i < 4; i++){
		if(status[i] == 0) return 1;
	}
	return 0;
}

char *splitKeyValue(char *line, int index){
	char *temp;
	if((temp = strstr(line, keys[index])) != NULL){
		temp = temp + strlen(keys[index]);
		status[index] = 1;
	}
	return temp;
}

void openFile(){
	char *temp;
	char command[100];
	char fileName[1000];
	strcpy(fileName, path);
	if((temp == strstr(contentFileType, "text/html")) != NULL){
		if((temp == strstr(fileName, ".txt")) != NULL){
			sprintf(command, "vim %s\n", fileName);
		} else {
			sprintf(command, "/Applications/Opera.app/Contents/MacOS/opera", fileName);
		}
		system(command);
	} else if((temp == strstr(contentFileType, "appication/pdf")) != NULL){
		printf("The filetype %s is not supported.\n", contentType);
	}
}
