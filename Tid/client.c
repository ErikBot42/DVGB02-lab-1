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

#define IP_ADDR "192.168.86.103"

int main()
{
	/*if (argc != 2)
	{
		print("Usage: %s <port>", argv[0]);
		exit(0);
	}*/
	struct sockaddr_in serverAddr;
    	int server_port = 37;
	int port = 37;
	struct sockaddr_in si_me, si_other;
	long int buffer[1024];
	socklen_t addr_size;
	
	memset(buffer, 0, 1024);
	
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	 
	sendto(sd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	printf("[+]Data send: %s", (char*)buffer);
	
	addr_size = sizeof(serverAddr);
	recvfrom(sd, buffer, 1024, 0, (struct sockaddr*)&serverAddr, &addr_size);
	long int time = buffer[0];
	char * printTime = ctime(&time);
   	printTime[strlen(printTime)-1] = '\0';
	printf("[+]Data received: Time is %s", printTime);
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
    
    connect(sd, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr_in));

    const int bufferSize = 13;
    char buf[bufferSize];
    printf("writing data...\n");
    write(sd, "Hello world!", bufferSize-1);
    printf("reading data...\n");
    read(sd, buf, bufferSize-1);
    buf[bufferSize-1] = 0;
    printf("recived: %s\n", buf);*/

    printf("closing socket");
    close(sd);
    return 0;
    
}
