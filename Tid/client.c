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
	if (argc != 2)
	{
		printf("Usage: %s <port>", argv[0]);
		exit(0);
	}
	int port = atoi(argv[1]);
    int sockfd;
	struct sockaddr_in serverAddr;
    int server_port = 37;

    int buffersize = 0;
	char buffer[buffersize];
	socklen_t addr_size;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    
    //strcpy(buffer, "Hello world!\n");
    sendto(sockfd, buffer, buffersize, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    printf("[+]Data send: %s", buffer);

    time_t current_time;
	
	addr_size = sizeof(serverAddr);
	recvfrom(sockfd, &current_time, 4, 0, (struct sockaddr*)&serverAddr, &addr_size);
	printf("[+]Data received: %d (%X)\n", current_time, current_time);
	printf("Current server time is: %s\n", ctime(&current_time));
	//long int time = buffer[0];
	//char * printTime = ctime(&time);
   	//printTime[strlen(printTime)-1] = '\0';
	/*
    struct sockaddr_in serverAddr;
    int server_port = 37;
    
    printf("creating sockets (port: %d)...\n", server_port);

    // create socket
    

    // fill addr struct
    memset(&serverAddr, 0, sizeof(struct sockaddr_in));
    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, IP_ADDR, &serverAddr.sin_addr);
    serverAddr.sin_port = htons(server_port);

    printf("connecting...\n");
    
    connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr_in));

    const int bufferSize = 13;
    char buf[bufferSize];
    printf("writing data...\n");
    write(sockfd, "Hello world!", bufferSize-1);
    printf("reading data...\n");
    read(sockfd, buf, bufferSize-1);
    buf[bufferSize-1] = 0;
    printf("recived: %s\n", buf);*/

    printf("closing socket");
    close(sockfd);
    
}
