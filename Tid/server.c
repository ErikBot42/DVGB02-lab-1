#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

// Server


int main(int argc, char ** argv)
{
    int port = 37;
    if (argc != 2) {
        printf("Port not defined\n", port);
    }	
    else
    {
	    port = atoi(argv[1]);
    }
    printf("Using port %d\n", port);
	
	struct sockaddr_in si_me, si_other;
    int buffersize = 0;
	char buffer[buffersize];
	socklen_t addr_size;
    	
    while(1)
    {
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

        memset(&si_me, '\0', sizeof(si_me));
        si_me.sin_family = AF_INET;
        si_me.sin_port = htons(port);
        si_me.sin_addr.s_addr = INADDR_ANY;


        bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));
        printf("Socket bound to server address\n");
        addr_size = sizeof(si_other);

        recvfrom(sockfd, buffer, buffersize, 0, (struct sockaddr*)&si_other, &addr_size); // receive EMPTY datagram
        printf("Data received: %s\n", buffer);

        time_t current_time = time(NULL);
        printf("Current time in HEX is %d(%X)\n", current_time, current_time);
        printf("Current server time is: %s\n", ctime(&current_time));
        printf("Sending time...\n", ctime(&current_time));

        sendto(sockfd, &current_time, 4, 0, (struct sockaddr*)&si_other, addr_size);

        printf("Done, closing socket..\n");

        close(sockfd);
    }

}
