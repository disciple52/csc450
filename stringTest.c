#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

void processChat();

int main(int argc, char** argv)
{
    puts("Please enter something:");
    processChat();
}

void processChat()
{
    char* command;
    char* who;
    char* msg;

    scanf("%ms", &command);
    if(strcmp("tell", command) == 0)
    {
        scanf("%ms %m[^\n]", &who, &msg);
        printf("Sending private message (%s) to: %s\n", msg, who);
    }
    else
    {
        scanf("%m[^\n]", &msg);
        char* destination = malloc(sizeof(command) + sizeof(msg));
        strcpy(destination, command);
        strcat(destination, msg);
        printf("Broadcasting: %s\n", destination);
    }
    //puts(command);
    //puts(msg);
}