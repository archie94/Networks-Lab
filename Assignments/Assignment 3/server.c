/*
Anubhav Patnaik 13/CS/26
Arka Prava Basu 13/CS/32
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<sys/select.h>
void checkpalindrome(char buf[])
{
   int len,i,j,k;
          len=strlen(buf);
          for(i=0,j=len-1;i<len/2;i++,j--)
          {
            if(buf[i]!=buf[j])
              break;
          }
          for(k=0; k < 100; k++) buf[k] = '\0';
	  if(i==len/2)
            strcpy(buf,"palindrome");
          else
            strcpy(buf,"not a palindrome");
}
int main()
{
	int sockfd1,sockfd2,newsockfd; 
	int clilen;
	struct sockaddr_in cli_addr, serv_addr;
        socklen_t addrlen=sizeof(cli_addr);
	int i,j,len,k,n,rv;
	char buf[100];
        struct timeval tv;
        fd_set readfds,writefds;
        //For Tcp
	if((sockfd1=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Cannot create socket\n");
                exit(0);
	}
        //For Udp
        if((sockfd2=socket(AF_INET,SOCK_DGRAM,0))<0) {  
      		printf("Cannot create socket\n");
      		exit(0);
   	}
	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr= INADDR_ANY;
	serv_addr.sin_port= htons(6000);
	if (bind(sockfd1, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		printf("Unable to bind local address\n");
		exit(0);
	}
        if (bind(sockfd2, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
		printf("Unable to bind local address\n");
		exit(0);
	} 
	
        listen(sockfd1, 5); 
	
        while (1) 
        {
         
          FD_ZERO(&readfds);
          FD_ZERO(&writefds);
          
          FD_SET(sockfd1, &readfds);
	  FD_SET(sockfd2, &readfds);
          n = sockfd2 + 1;
          tv.tv_sec = 10;
          tv.tv_usec = 500000;
          rv = select(n, &readfds, NULL, NULL,&tv);
	  
          for(i=0; i < 100; i++) buf[i] = '\0';
          
          if (rv == -1) 
          {
    		perror("select"); // error occurred in select()
	  } 
	  else if (rv == 0) 
          {
    		printf("Timeout occurred!  No data after 10.5 seconds.\n");
          } 
	  else 
          {     
    		// one or both of the descriptors have data
    		if (FD_ISSET(sockfd1, &readfds)) 
                {   
                    // TCP Socket
                    clilen = sizeof(cli_addr);
	            newsockfd = accept(sockfd1, (struct sockaddr *) &cli_addr,&clilen) ;
	            if (newsockfd < 0) {
 		      printf("Accept error\n");
		      exit(0);
                    }   
        	    recv(newsockfd,buf,100,0);
                    printf("The string is: %s\n",buf);
                    checkpalindrome(buf); 
                    send(newsockfd,buf,strlen(buf)+1,0);
    	        }
    		else if (FD_ISSET(sockfd2, &readfds)) 
                { 
                    // UDP Socket  
        	    recvfrom(sockfd2,buf,100,0,(struct sockaddr *)&cli_addr,&addrlen);//For Udp
                    printf("The string is: %s\n",buf);
                    checkpalindrome(buf);  
                    sendto(sockfd2,buf,strlen(buf)+1,0,(struct sockaddr *)&cli_addr,addrlen);//For Udp 
                }
           }          
        	  
          close(newsockfd);
        }
}
