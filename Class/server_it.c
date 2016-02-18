
/*
	A TCP iterative server which takes an arithmetic expression from client 
	and sends the result of the expression back to the client.
	Only simple arithmetic expressions consisting of +,-,* and / are considered.
	All the operators are considered left associative and have same precedence values.
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
	
	// Check if socket creation fails 
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("cant create socket\n");
	exit(0);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr =INADDR_ANY;
	serv_addr.sin_port = htons(6000);

	// Check if binding fails 
	if(bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("Unable to bind local addr\n");
	}

	listen(sockfd, 5);
	
	
	
	while(1)
	{
		printf("Server running ... waiting for client\n");
		clientLen = sizeof(cli_addr);
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clientLen);
		if(newsockfd < 0){
			printf("Accept error\n");
			exit(0);
		}

		bufLen = 1;
		while(bufLen){
		
		
			for(i=0;i<100;i++) buf[i] = '\0';
			bufLen = recv(newsockfd, buf, 100, 0);
			printf("Received message : %s\n", buf);
		
			// parse the msg here 
			int l,k,i;
			int num[2]={0};
			int op = -1;
			k = 0;
			for(i=0;i<strlen(buf);i++){
				if(buf[i]=='+' || buf[i]=='-' || buf[i] =='*' || buf[i]=='/'){
					
					
					if(k == 0){
						k++; 
					}else if(k == 1){
						if(op == 0)
							num[0] = num[0] + num[1];
						else if(op == 1)
							num[0] = num[0] - num[1];
						else if(op == 2)
							num[0] = num[0] * num[1];
						else if(op == 3)
							num[0] = num[0] / num[1];
						num[1] = 0;
					}
				
					
					if(buf[i] == '+'){
						op = 0;
					}else if(buf[i] == '-'){
						op = 1;
					}else if(buf[i] == '*'){
						op = 2;
					}else{
						op = 3;
					}
				}
				else
				num[k] = num[k]*10 + (buf[i]-'0');
			}
		
			if(op == 0)
				num[0] = num[0] + num[1];
			else if(op == 1)
				num[0] = num[0] - num[1];
			else if(op == 2)
				num[0] = num[0] * num[1];
			else if(op == 3)
				num[0] = num[0] / num[1];
			
			sprintf(msg, "%d",num[0]);
			send(newsockfd, msg, strlen(msg) + 1, 0);
			
		}	
		printf("------------Disconnecting CLient from Server-------------------------\n");
		close(newsockfd);
	}
}

