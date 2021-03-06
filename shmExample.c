#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "shmExample.h"
#define SHMSZ 27 //this is how many bytes we can hold

 int main(int argc, char** argv)
 {
    char c;
    int shmid;
    key_t key;
    char *shm, *s; //effectively a character array in java

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.reserve some shared memory for us of our defined size
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) 
    {
        perror("shmget");
        return -1;
    }
    
    /*
     * Now we attach the segment to our data space. gives us access to it
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) 
    {
        perror("shmat");
        return -1;
    }
    
    shm[0] = 'a';
    shm[26] = 'P';
    
    int pid = fork();
    
    if(pid != 0)
    {
        while(1 == 1)
        {
            //parent
            if(shm[26] == 'P')
            {
                //critical section
                printf("%c ", shm[0]);
                shm[0] = shm[0]++;
                shm[26] = 'C';
            }
            waitWhileEqual('C', shm);
        }
    }
    else
    {
        while(1==1)
        {
            //child
            if(shm[26] == 'C')
            {
                //critical section
                printf("%c", shm[0]);
                shm[0] = shm[0]++;
                shm[26] = 'P';
            }
            waitWhileEqual('P', shm);
        }
    }
    
    printf("The mem address is = %p\n", shm);
    return 0;
 }
 
 void waitWhileEqual(char val, char* shm)
 {
     while(shm[26] == val)
        {
            //wait
        }
 }