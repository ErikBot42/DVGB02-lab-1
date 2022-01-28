#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

// Client 


int main(int argc, char **argv)
{
    if (argc != 2) {printf("specify port\n"); exit(0);}
    int port = atoi(argv[1]);
    const int bufferSize = 1024;
    char buffer[bufferSize];

    int sockfd = socket(PF_INET, SOCK_DGRAM, 0);


    struct sockaddr_in serverAddr; // ip4 addr
    memset(&serverAddr, '\0', sizeof(serverAddr)); // ???
    serverAddr.sin_family=AF_INET;
    serverAddr.sin_port=htons(port);
    inet_pton(AF_INET, "192.168.86.103", &serverAddr.sin_addr);

    strcpy(buffer, "He110 w0r1d\n");
    sendto(sockfd, buffer, bufferSize, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    printf("Send: %s", buffer);
    
    socklen_t addr_size = sizeof(serverAddr);
    recvfrom(sockfd, buffer, bufferSize, 0, (struct sockaddr*)&serverAddr, &addr_size);

    printf("Recv: %s", buffer); 

    

    return 0;
}
