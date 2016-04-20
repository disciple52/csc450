#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int filedes[1];
    pipe(filedes);
    
    
    char* buf = "hello";
    write(filedes[1], buf, 5);
    char* buf2 = malloc(5 * sizeof(char));

    pid_t pid = fork();
    printf("PID %d\n", pid);
    if(pid == 0)
    {
        printf("Child");
        read(filedes[0], buf2, 5);
        //write(filedes[1], "woot", 4);
    }
    else
    {
        read(filedes[0], buf2, 5);
        printf("Parent: %s\n", buf2);
        /*
        int numRead = 0;
        while(numRead == 0)
        {
            numRead = read(filedes[0], buf2, 5);
        }
        printf("%s\n", buf2);
        */
        
    }
    return 0;
}