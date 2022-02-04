#include <sys/types.h> 
#include <sys/socket.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include <sys/fcntl.h> 
#include <netinet/in.h> 
#include <netdb.h>
#define SERVER_PORT 8080 /* arbitrary, but client & server must agree */ 
#define BUF_SIZE 4096                   /* block transfer size */
#define QUEUE_SIZE 10

bool prefix(const char *pre, const char *str)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

void pln(char * string)
{
    printf("%s\n", string);
}

int fatal(char *string);

int main(int argc, char *argv[]) 
{

    /* Build address structure to bind to socket. */
    struct sockaddr_in channel; // IP addr
    memset(&channel, 0, sizeof(channel));  /* zero channel */
    channel.sin_family = AF_INET;
    channel.sin_addr.s_addr = htonl(INADDR_ANY);
    channel.sin_port = htons(SERVER_PORT);

    /* Passive open. Wait for connection. */
    int s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); /* create socket */ 
    if (s < 0) fatal("socket failed");
    int on = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on));
    int b = bind(s, (struct sockaddr *) &channel, sizeof(channel)); 
    if (b < 0) fatal("bind failed");
    int I = listen(s, QUEUE_SIZE);             /* specify queue size */
    if (I < 0) fatal("listen failed");

    /* Socket is now set up and bound. Wait for connection and process it. */ 
    while (1) {
        char buf[BUF_SIZE]; // Store client request
        pln("waiting for connection request...");
        int sa = accept(s, 0, 0);               // block for connection request 
        if (sa < 0) {pln("accept failed"); continue;}
        read(sa, buf, BUF_SIZE);            // read request from socket 
        pln("Recived request:\n");
        pln(buf);


        char * requestMethod = strtok(buf, " ");
        if (requestMethod == NULL) {pln("requestMethod invalid"); continue;}
        printf("Request method: %s\n", requestMethod);

        char * requestedFile = strtok(NULL, " ");
        if (requestedFile == NULL) {pln("requestedFile invalid"); continue;}
        printf("Request file: %s\n", requestedFile);

        char * httpVersion = strtok(NULL, " ");
        if (httpVersion == NULL) {pln("httpVersion invalid"); continue;}
        printf("HTTP version: %s\n", httpVersion);



        exit(1);

        
        /* Get and return the file. */
        int fd = open(buf, O_RDONLY);           /* open the file to be sent back */
        if (fd < 0) fatal("open failed");
        while (1) {
            int bytes = read(fd, buf, BUF_SIZE); /* read from file */
            if (bytes <= 0) break;          /* check for end of file */
            write(sa, buf, bytes);          /* write bytes to socket */
        }
        close(fd);                          /* close file */
        close(sa);                          /* close connection */
    }
}

int fatal(char *string)
{
    printf("%s\n", string);
    exit(1);
}
