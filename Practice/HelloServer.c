/*
*	Creates a simple TCP server which outputs a message 
*	client connects to it. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

main()
{
	int sockfd;
	int clientfd;
	int len;
	struct sockaddr_in server, client;
	char msg[] = "Hello to the new world";
	int sent;
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket: ");
		exit(-1);
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(10000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);

	len = sizeof(struct sockaddr_in);
	
	if((bind(sockfd, (struct sockaddr *)&server, len)) == -1)
	{
		perror("bind");
		exit(-1);
	}

	if((listen(sockfd, 5)) == -1)
	{
		perror("listen");
		exit(-1);
	}

	while(1)
	{
		if((clientfd = accept(sockfd, (struct sockaddr *)&client, &len)) == -1)
		{
			perror("accept");
			exit(-1);
		}
		sent = send(clientfd, msg, strlen(msg), 0);
		printf("sent %d bytes to client %s\n", sent, inet_ntoa(client.sin_addr));
		close(clientfd);
	}
}
