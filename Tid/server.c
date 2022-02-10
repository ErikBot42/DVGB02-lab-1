#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

// Server


int main()
{
	
	
	int port = 37;
	struct sockaddr_in si_me, si_other;
	char buffer[1024];
	socklen_t addr_size;
	
	int sd = socket(AF_INET, SOCK_DGRAM, 0);
	
	time_t mytime = time(NULL);
    	/*char * time_str = ctime(&mytime);
   	time_str[strlen(time_str)-1] = '\0';*/
    	
    	/*
	time_t currentTime;
	struct tm * timeInfo;
	char sentTime[50];
	time(&currentTime);
	timeInfo = localtime(&rawtime);
	sentTime[0] = asctime(timeInfo); */
	
	memset(&si_me, '\0', sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(port);
	si_me.sin_addr.s_addr = INADDR_ANY;
	
	
	
	bind(sd, (struct sockaddr*)&si_me, sizeof(si_me));
	printf("[+]Socket bound to server address");
	addr_size = sizeof(si_other);
	recvfrom(sd, buffer, 1024, 0, (struct sockaddr*)&si_other, &addr_size);
	printf("[+]Data received");
	sendto(sd, mytime, 1024, 0, (struct sockaddr*)&si_other, &addr_size);
	/*sendto(sd, buffer, 1024, 0, (struct sockaddr*)&si_other, &addr_size);*/
	printf("[+]Data send: %s", mytime /*buffer*/);
	
	/*
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    int clientaddrlen;
    int request_sd, sd;

    int server_port = 37;
    printf("creating sockets (port: %d)...\n", server_port);

    // create socket
    request_sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    // fill addr struct
    memset(&serverAddr, 0, sizeof(struct sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(server_port);
    
    // bind addr to socket
    bind(request_sd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));
    
    // activate connect request queue
    listen(request_sd, SOMAXCONN);
    
    clientaddrlen = sizeof(struct sockaddr_in);
    printf("waiting for client...\n");
    
    // recive connection
    sd = accept(request_sd, (struct sockaddr*)&clientAddr, &clientaddrlen);
    
    printf("reading data to buffer...\n");

    // read data to buffer
    const int bufferSize = 13;
    char buf[bufferSize];
    read(sd, buf, bufferSize-1);
    buf[bufferSize-1] = 0;
    printf("buffer: %s\n", buf);
    
    printf("send buffer back...\n");

    write(sd, buf, bufferSize-1);
    
    printf("closing sockets...\n"); */
    close(sd);
    close(request_sd);
    
	return 0;

}
