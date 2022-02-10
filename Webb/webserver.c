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


const char* getFileExtension(const char *file) {
    const char *dot = strrchr(file, '.');
    if(!dot || dot == file) return "";
    return dot + 1;
}

void writeAndPrint(int fd, const char *buf, size_t count, bool print)
{
    if (print) printf("%.*s",(int)count,buf);
    write(fd, (const void*)buf, count);
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
        pln("---------------------------------");
        pln("waiting for connection request...");
        pln("");
        pln("");

        int sa = accept(s, 0, 0);               // block for connection request 
        if (sa < 0) {pln("accept failed"); continue;}
        read(sa, buf, BUF_SIZE);            // read request from socket 
        pln("Recived request:\n");
        pln(buf);
        
        // required responses:
        // 200 - OK, send file
        // 404 - not found
        
        // TODO: check 404
        char * requestMethod = strtok(buf, " \n\r");
        if (requestMethod == NULL) {pln("requestMethod invalid"); continue;}
        printf("Request method: %s\n", requestMethod);

        char * requestedFile = strtok(NULL, " \n\r");
        if (requestedFile == NULL) {pln("requestedFile invalid"); continue;}
        requestedFile+=1;// +1 to remove /
        printf("Request file: %s\n", requestedFile);

        char * httpVersion = strtok(NULL, " \n\r");
        if (httpVersion == NULL) {pln("httpVersion invalid"); continue;}
        printf("HTTP version: %s\n", httpVersion);


        // assume http version is ok.
        pln("response:"); 
        fflush(stdout);
        writeAndPrint(sa, httpVersion, strlen(httpVersion), true); fflush(stdout);
        FILE *fp = fopen(requestedFile, "r"); 
        char * sResponse  = (char*)malloc(1048576);//1M
        if (fp == NULL)
        {
            sprintf(sResponse, " 404 Not Found\r\n");
            writeAndPrint(sa, sResponse, strlen(sResponse), true);
            pln("end");
            pln("cannot open requested file -> sent 404");
        }
        else
        {



            fseek(fp, 0, SEEK_END);
            long fileLength = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            char * buffer = (char *)malloc(fileLength);
            fread(buffer, 1, fileLength, fp);

            //    " 200 OK\n";
            //write(sa, sResponse, strlen(sResponse)-1);
            //sResponse = "Server: A web server\n";
            //write(sa, sResponse, strlen(sResponse)-1);
            //sResponse = "Content-Length: ";
            //write(sa, sResponse, strlen(sResponse)-1);
            //
            
            char * fileExtension = getFileExtension(requestedFile);

            char * contentType="text";
            bool printContent = true;

            printf("File extension: %s", fileExtension);
            if (strcmp(fileExtension, "html")==0) 
            {
                contentType  = "text/html"
            }
            if (strcmp(fileExtension, "jpeg")==0) 
            {
                contentType  = "image/jpeg"
                printContent = false
            }

            sprintf(sResponse, " 200 OK\r\nServer: A Web Server\r\nContent-Length: %ld\r\nContent-Type: %s\r\n\r\n", fileLength, contentType);

            writeAndPrint(sa, sResponse, strlen(sResponse), true);
            writeAndPrint(sa, buffer, fileLength, printContent, true);
        
            free(buffer);
            fclose(fp);

        }
            free(sResponse);
        /* Get and return the file. */
#if 0
        if (fd < 0) fatal("open failed");
        while (1) {
            int bytes = read(fd, buf, BUF_SIZE); /* read from file */
            if (bytes <= 0) break;          /* check for end of file */
            write(sa, buf, bytes);          /* write bytes to socket */
        }
#endif
        close(sa);                          /* close connection */
    }
}

int fatal(char *string)
{
    printf("%s\n", string);
    exit(1);
}
