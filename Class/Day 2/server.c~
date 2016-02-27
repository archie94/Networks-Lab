/*
		GROUP NO : 17
	@authors:	Anubhav Patnaik 13/CS/26
			Arka Prava Basu 13/CS/32
	A UDP server
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

main()
{
	int sockfd, newsockfd;
	int clientLen;
	struct sockaddr_in cli_addr, serv_addr;
	
	int i;
	int bufLen;
	char buf[100];
	char msg[100];
	
	// Check if socket has been connected or not 
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		printf("cant create socket\n");
	exit(0);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr =INADDR_ANY;
	serv_addr.sin_port = htons(6000);

	// Check if binding fails 
	if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("Unable to bind local address\n");
	}

		
	while(1)
	{
		printf("Server running ... Waiting for client\n");
		

		bufLen = 1;
		while(bufLen){
		
		
			for(i=0;i<100;i++) buf[i] = '\0';
			int size = sizeof(serv_addr);
			bufLen = recvfrom( sockfd, buf, 100, 0, (struct sockaddr *)&serv_addr, &size);
			printf("Received message : \" %s \" \n", buf);
		 
		 	for(i=0;i<strlen(buf);i++){
				if(buf[i] >= 97 && buf[i] <= 122)
					buf[i] -= 32;
			}
			sendto( sockfd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
			
		}	
		printf("------------Disconnecting CLient-------------------------\n");
		close(newsockfd);
	}
}

