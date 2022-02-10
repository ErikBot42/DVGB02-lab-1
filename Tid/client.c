#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>


#include <unistd.h>
#include <arpa/inet.h>
// Client 

#define IP_ADDR "192.168.86.103"


	if (argc != 2)
	{
		print("Usage: %s <port>", argv[0]);
		exit(0);
	}
	
	int port = atoi([argv[1]);
	struct sockaddr_in si_me, si_other;
	char buffer[1024];
	socklen_t addr_size;
	
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr);
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
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
