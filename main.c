#include "clnt.h"

int main(int argc, char **argv){
	
	int sockfd, ret;
	char *url, *temp;
	int portNumber;
	char status_ok[] = "OK";
	char buffer[BUFF_SIZE];
	char http_ok[] ="HTTP/1.1 200 OK";

	if(argc < 3){
		printf("usage: [URL] [PORT]\n");
		exit(1);
	}

	url = argv[1];
	portNumber = atoi(argv[2]);

	if((temp = strstr(url, "http://")) != NULL){
		url = url + 7;
	} else if((temp = strstr(url, "https://")) != NULL){
		url = url + 8;
	}

	if(portNumber > 65536 || portNumber < 0){
		printf("Invalid Port Number!");
		exit(1);
	}

	sockfd = get_request(url, argv[2]);

	memset(&buffer, 0, sizeof(buffer));
	ret = recv(sockfd, buffer, BUFF_SIZE, 0);
	if(ret < 0){
		printf("Error receiving HTTP status!\n");
	} else {
		printf("%s\n", buffer);
		if((temp = strstr(buffer, http_ok)) != NULL){
			send(sockfd, status_ok, strlen(status_ok), 0);
		} else {
			close(sockfd);
			return 0;
		}
	}
	fileptr = fopen(path, "w");
	if(fileptr == NULL){
		printf("Error opening the file!\n");
		close(sockfd);
		return 0;
	}

	memset(&buffer, 0, sizeof(buffer));
	while(recv(sockfd, buffer, BUFF_SIZE, 0) > 0){
		if((strstr(contentFileType, "text/html")) != NULL){
			fprintf(fileptr, "%s", buffer);
		} else {
			fwrite(&buffer, sizeof(buffer), 1, fileptr);
		}
		memset(&buffer, 0, sizeof(buffer));
	}

	fclose(fileptr);
	close(sockfd);

	openFile();

	return 0;
}
