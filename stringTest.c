#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    int maxSize = 1000;
    char* s = "lol msg 4 hello";
    char* s2 = "world";
    //puts(strstr(s, "4"));
    char* parts = strtok(s, " "); //splits into parts on the spaces
    int i = 0;
    for(; i < 4; i++)
    {
        printf("%s\n", parts[i]);
    }
    //printf("%d\n", val);
}