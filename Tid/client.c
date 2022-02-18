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
    char * ipAddrString = "127.0.0.1";
    if (argc <= 1)
    {
        printf("IP address not defined\n");
        printf("(Usage: %s <IP address> [port (default 37)]");
        exit(0);
    }
    else
    {
        char * ipAddrString = argv[1];
    }
	if (argc <= 2)
	{
        printf("Port not defined, using %d\n", port);
	}
    else
    {
	    port = atoi(argv[2]);
    }

    int sockfd;
	struct sockaddr_in serverAddr;

    int buffersize = 0;
	char buffer[buffersize];
	socklen_t addr_size;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, ipAddrString, &serverAddr.sin_addr);
    
    sendto(sockfd, buffer, buffersize, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("Sending empty datagram to %s:%d\n", ipAddrString, port);

    uint32_t data;
	addr_size = sizeof(serverAddr);
	recvfrom(sockfd, &data, 4, 0, (struct sockaddr*)&serverAddr, &addr_size);

    data = ntohl(data); // to little endian
	printf("Data received: dec: %d hex: %X\n", data, data);
    data -= 2208988800L; // since 1970
    time_t current_time = data;

	printf("Current server time is: %s\n", ctime(&current_time));

    printf("closing socket");
    close(sockfd);
    
}
