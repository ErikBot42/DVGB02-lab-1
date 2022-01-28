#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
// Server

int main(int argc, char **argv)
{
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(struct sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(2009);

    int request_sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(request_sd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in));

    listen(request_sd, SOMAXCONN);

    int clientaddrlen = sizeof(struct sockaddr_in);
    
    struct sockaddr_in clientAddr;
    int sd = accept(request_sd, (struct sockaddr*)&clientAddr, &clientaddrlen);
    
    const int bufferSize = 13;
    char buf[bufferSize];
    read(sd, buf, bufferSize-1);
    buf[bufferSize-1] = 0;
    printf("buffer: %s\n", buf);
    


}
