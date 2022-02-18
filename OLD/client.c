#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
// Client 

#define IP_ADDR "192.168.86.103"

int main(int argc, char **argv)
{
    struct sockaddr_in serverAddr;
    int sd;
    int server_port = 2009;
    
    printf("creating sockets (port: %d)...\n", server_port);

    // create socket
    sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

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
    printf("recived: %s\n", buf);

    printf("closing socket");
    close(sd);
    return 0;
}
