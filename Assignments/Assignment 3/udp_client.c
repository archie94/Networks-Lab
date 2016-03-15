/*
Anubhav Patnaik 13/CS/26
Arka Prava Basu 13/CS/32
*/

#include <stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>

int main()
{
	int sockfd ;
	struct sockaddr_in serv_addr;
        socklen_t addrlen=sizeof(serv_addr);
	int i;
	char buf[100];
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) 
	{
		printf("Unable to create socket\n");
		exit(0);
	}

	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr= inet_addr("127.0.0.1");
	serv_addr.sin_port= htons(6000);

	printf("Enter the string\n");
        scanf("%s",buf);
        sendto(sockfd, buf, strlen(buf)+1, 0,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
	printf("Message from server\n");
        for(i=0; i < 100; i++) buf[i] = '\0';
        recvfrom(sockfd,buf,100,0,(struct sockaddr *)&serv_addr,&addrlen);  
        printf("%s\n",buf);
	close(sockfd);
	return 0;
}
 
