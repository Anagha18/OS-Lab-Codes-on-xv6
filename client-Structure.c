#include <arpa/inet.h>	//inet_addr
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define LIST "list"
#define GET "get"

int main(int argc, char **argv) 
{
	int sockfd = 0;					// sockfd - socket file descriptor
	int bytesReceived = 0;				// Bytes received from server
	char recvBuff[256];				// Buffer to receive bytes from server

	memset(recvBuff, '0', sizeof(recvBuff));	// memset() is used to fill a block of memory with a particular value.

	struct sockaddr_in serv_addr;			// A sockaddr_in is a structure containing an internet address. 
	int fr;						// This structure is defined in <netinet/in.h>.

		  /* Create a socket first */

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 		// Create socket
	{
		printf("\n Error : Could not create socket \n");
	        return 1;
  	}


	  /* Initialize sockaddr_in data structure */

	serv_addr.sin_family = AF_INET;				// A sockaddr_in is a structure containing an internet address. 
								// This structure is defined in <netinet/in.h>.
	serv_addr.sin_port = htons(5050);  			// port
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	// local host IP address: 127.0.0.1


	  /* Attempt a connection */

	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) // connect - initiate a connection on a socket.
	{
		printf("\n Error : Connect Failed \n");
		return 1;
	}	
		
	write(sockfd, argv[1], sizeof(argv[1]));
        sleep(3);
        int val = write(sockfd, (const char*) argv[2], strlen(argv[2])+1);
	    printf("val: %d\n", val);	
        int newfd = open("temp.txt",O_WRONLY|O_CREAT,0777);		
        int bytesWritten = 0;
        int bytesRead = 256;
        while(bytesRead >= 256){
            bytesRead = read(sockfd, recvBuff, sizeof(recvBuff));
            printf("bytesRead :%d\n", bytesRead);
            bytesWritten += write(newfd, recvBuff, bytesRead);
        }
        close(newfd);
        printf("bytesWritten: %d\n", bytesWritten);
    
  
	return 0;
}
