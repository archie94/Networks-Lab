#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

main()
{
	int sockfd;
	struct sockaddr_in serv_addr;
	
	int i, sent;
	char buf[100];
	char buff[100];
	
	/*
	Opening a socket 
	Check whether opening is successful or not
	*/
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Unable to create socket\n");
	}
	printf("Socket created\n");
	
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(6000);
	
	/*
	Establish a connection with the server process
	*/
	if((connect(sockfd, (struct socketaddr *)&serv_addr, sizeof(serv_addr)))<0){
		printf("Unable to connect to server\n");
		exit(0);
	}
	
	printf("Client connected\n");
	
	while(1){
	
		for(i=0; i<100; i++){
			buf[i] = '\0';
			buff[i] = '\0';
		}
		fflush(stdin);
		printf("Enter an expression : ");
		gets(buf);
		int k = 0;
		/*
		Remove extra spaces from input expression
		*/
		for(i=0;i<strlen(buf);i++,k++){
			while(buf[i] == 32){
				i++;
			}
			buff[k] = buf[i];
		}
		/*
		If input expression is "-1" we will terminate the client
		*/
		if(!strcmp(buff,"-1")){
			break;
		}
		
		sent = send(sockfd, buff, strlen(buff) + 1, 0);
		printf("-------------Sent %d bytes to server--------------\n", sent);
		recv(sockfd, buf, 100, 0);
		printf("Received result from server = %s\n",buf);
	}
	printf("----------------Closing client------------------ \n");
	close(sockfd);
}
