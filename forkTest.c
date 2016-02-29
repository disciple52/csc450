#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main(int argc, char** argv)
{
    /*
    srand(time(NULL));
    int num;
    int i;
    int nums[10];
    for(i = 0; i < 10; i++)
    {
        nums[i] = rand()%2;
        //printf("%d\n", num);
    }
    
    for(i = 0; i < 10; i++)
    {
        printf("woot: %d\n", nums[i]);
    }
    */
    
    printf("About to Fork...\n");
    int mem2Share = 5;
    int sharedMemID = shmdt(&mem2Share);
    
    printf("Shared Mem ID: %d", sharedMemID);
    
    pid_t pid = fork();
    if(pid == 0)
    {
        //I am the child
        int sharedValue;
        shmat(sharedMemID, &sharedValue, 0);
        printf("I got the value (Child): %d", sharedValue);
        return 0;
    }
    else
    {
        //I am the parent
        int status;
        int sharedValue;
        shmat(sharedMemID, &sharedValue, 0);
        printf("I got the value (Child): %d", sharedValue);
        waitpid(pid, &status, 0);
        printf("The child is done: %d\n", status);
    }
}