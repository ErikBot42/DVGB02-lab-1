#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h>
#define SERVER_PORT 12345                              /* arbitrary, but client & server must agree */
#define BUFSIZE 4096                                   /* block transfer size */

int main(int argc, char **argv) 
{
    int c, s, bytes;
    char buf[BUF_SIZE];                                   /* buffer for incoming file */ 
    struct hostent *h;                                    /* info about server */
    struct sockaddr_in channel;                           /* holds IP address */
    if (argc != 3) fatal("Usage: client server-name file-name");
    h = gethostbyname(argv[1]);                           /* look up host's IP address */
    if (!h) fatal("gethostbyname failed");
    s = socket(PF_INET, SOCK STREAM, IPPROTO_TCP); 
    if (s <0) fatal("socket");
    memset(&channel, 0, sizeof(channel));
    channel.sinfamily= AFINET;
    memcpy(&channel.sin_addr.s_addr, h->h_addr, h->h_length); 
    channel.sin_port= htons(SERVER_PORT);

    c = connect(s, (struct sockaddr *) &channel, sizeof(channel)); 
    if (c < 0) fatal("connect failed");
    /* Connection is now established. Send file name including 0 byte at end. */ 
    write(s, argv[2], strlen(argv[2])+1);
    /* Go get the file and write it to standard output. */ 
    while (1) {
        bytes = read(s, buf, BUF_SIZE);                   /* read from socket */
        if (bytes <= 0) exit(0);                          /* check for end of file */
        write(1, buf, bytes);                             /* write to standard output */
    } 
}


fatal(char *string)
{
    printf("%s\n", string);
    exit(1);
}
