#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    // /*
    //How to cut off the beginning and comparing strings
    int maxSize = 1000;
    char* s = "lol msg 4 hello";
    char* s2 = "world";
    int compare = strcmp("world", s2);
    printf("Comparison return value: %i\n", compare);
    // */
    
    
    
    //testing user input with scanf
    char str[100];
    printf("Enter your message: ");
    scanf("%s", str);
    
    printf("You just sent out this message: %s\n", str);
    
    
    
    /*
    char* parts = strtok(s, " ");
    int i = 0;
    for(; i < 4; i++)
    {
        printf("%s\n", parts[i]);
    }
    //printf("%d\n", val);
    */
}