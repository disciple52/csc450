#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    uint16_t port = 3000; //EXAMPLE: a port is like an extension of a phone number 0 - 1023 are reserved for the operating system
    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_port = htons (port);
    name.sin_addr.s_addr = htonl (INADDR_ANY);
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //we created our socket
    int bindfd = bind(sockfd, (struct sockaddr *) &name, sizeof(name)); //we do our bind to local stuff (IP address etc.)
    int listenfd = listen(sockfd, 100); // now we need to listen (blocks until incoming client accepts)
    char buffer[5];
    buffer = "hello\0";
    printf("listening...\n");
    int clientfd = accept(sockfd, (struct sockaddr *) &name, sizeof(name));//accept incoming connection 
    printf("client connected...\n");
    printf("%s\n",buffer);
}

