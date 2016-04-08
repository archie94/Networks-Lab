#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main() {
	int sockfd, newsockfd;
	int clilen;
	int fdmax = 0, i, bytes, k, j;
	struct sockaddr_in serv_addr, cli_addr;
	char buff[100];
	
	fd_set master;
	fd_set read_fd;
	
	FD_ZERO(&master);
	FD_ZERO(&read_fd);
	
	if( (sockfd = socket( AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket creation failed\n");
		exit(0);
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(6000);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	if( bind( sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("Failed to bind to port 6000\n");
		exit(0);
	}
	
	listen( sockfd, 5);
	printf("listening for 5 \n");
	
	FD_SET( sockfd, &master);
	fdmax = sockfd;
	
	while(1) {
		read_fd = master;
		printf("waiting for select\n");
		if( select( fdmax + 1, &read_fd, NULL, NULL, NULL) == -1) {
			printf(" Server select error\n");
			exit(0);
		}
		printf("Server select is OK \n");
		
		for( i=0; i <= fdmax; i++) {
			
			if( FD_ISSET( i, &read_fd)) {
				// one client found
				if( i == sockfd) { // handle new connection
					clilen = sizeof(cli_addr);
					if( ( newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen)) < 0) {
						printf(" Server accept error\n");
						exit(0);
					}
					
					printf(" Server accept OK\n");
					FD_SET( newsockfd, &master); // add to master set
					
					if( newsockfd > fdmax) { // keep track of maximum
						fdmax = newsockfd;
					}
					printf("------- new connection--------\n");
				}else { // handle data from a client
					for(k=0;k<100;k++) {
						buff[k] = '0';
					}
					if(( bytes = recv( i, buff, 100, 0)) <= 0){ // got error or connection closed by client
						if( bytes == 0) {
							printf("-----------Connection closed by client-------------\n");
						}else {
							printf("recv() error\n");
						}
						
						close(i);
						FD_CLR( i, &master); // remove from master set
					}else { // we got message from a client
						for( j=0; j<=fdmax; j++) { // send to everyone
							if( FD_ISSET( j, &master)) {
								if( j != sockfd) { // do not send to server
									printf( " sending %s \n", buff);
									send( j, buff, bytes, 0);
								}
							}
						} // end of for j
					} // end of else ----- message handled and sent to everyone 
				} // client handled 
			} // end of if
		}// end of for i
	} // end of while
	return 0;
}
