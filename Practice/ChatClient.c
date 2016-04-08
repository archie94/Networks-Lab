#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

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
		
		fd_set rfd, wfd;
		struct timeval tv;
		
		/*int flags = fcntl( 0, F_GETFL, 0);
		flags |= O_NONBLOCK;
		fcntl( 0, F_SETFL, flags);*/
		
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		FD_ZERO( &rfd);
		FD_ZERO( &wfd);
		
		FD_SET( sockfd, &rfd);
		//FD_SET( sockfd, &wfd);
		FD_SET( STDIN_FILENO, &rfd);
		
		if( (select( sockfd + 1, &rfd, NULL, NULL, &tv) < 0)) {
			printf(" Select error \n");
			exit(0);
		}
		
		if( FD_ISSET( sockfd, &rfd)) { // we got data ... need to read it
			recv(sockfd, buff, 100, 0);
			printf("Received result from server = %s\n",buff);
		}
		
		if( FD_ISSET( STDIN_FILENO, &rfd)) {
			fflush(stdin);
			printf(">");
			gets(buf);
			sent = send(sockfd, buf, strlen(buf) + 1, 0);
			printf("-------------Sent %d bytes to server--------------\n", sent);
		}
	}
	printf("----------------Closing client------------------ \n");
	close(sockfd);
}
