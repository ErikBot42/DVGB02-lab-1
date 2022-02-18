#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>

// Server

int main(int argc, char **argv)
{
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    int clientaddrlen;
    int request_sd, sd;

    int server_port = 2009;
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
    
    printf("closing sockets...\n");
    close(sd);
    close(request_sd);
    


}
