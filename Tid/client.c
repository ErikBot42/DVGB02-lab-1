#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
// Client 

#define IP_ADDR "127.0.0.1"

void main(int argc, char **argv)
{
    int port = 37;
	if (argc != 2)
	{
        printf("Port not defined\n", port);
	}
    else
    {
	    port = atoi(argv[1]);
    }
    printf("Using port %d\n", port);

    int sockfd;
	struct sockaddr_in serverAddr;

    int buffersize = 0;
	char buffer[buffersize];
	socklen_t addr_size;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    
    sendto(sockfd, buffer, buffersize, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Sending empty datagram\n");

    time_t current_time;
	
	addr_size = sizeof(serverAddr);
	recvfrom(sockfd, &current_time, 4, 0, (struct sockaddr*)&serverAddr, &addr_size);
	printf("[+]Data received: %d (%X)\n", current_time, current_time);
	printf("Current server time is: %s\n", ctime(&current_time));

    printf("closing socket");
    close(sockfd);
    
}
