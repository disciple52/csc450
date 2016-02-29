#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include "shmTictactoe.h"
#define SHMSZ 10 //this is how many bytes we can hold

 int main(int argc, char** argv)
 {
    char c;
    int shmid, i;
    key_t key;
    char *shm, *s; //effectively a character array in java
    time_t t;

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
    
    //initialize random number generator
    srand((unsigned) time(&t));
    
    shm[0] = 'p';
    //initailize all cells with ?
    for(i = 1; i < 10; i++)
    {
        shm[i] = '?';
    }
    
    int pid = fork();
    
    if(pid != 0)
    {
        while(1)
        {
            //parent
            if(shm[0] == 'p')
            {
                //critical section
               //parent goes
                int go = validMove(shm);
                shm[go] = 'x';
                
                int won = isWin('x', shm);
                if(won == 1) //winner
                {
                 printf("%c  %c  %c\n", shm[1], shm[2], shm[3]);
                 printf("%c  %c  %c\n", shm[4], shm[5], shm[6]);
                 printf("%c  %c  %c\n", shm[7], shm[8], shm[9]);
                 printf("Parent: winner\n");
                 shm[0] = 'w';
                 break;
                }
                else if(won == 2) //tie
                {
                 printf("%c  %c  %c\n", shm[1], shm[2], shm[3]);
                 printf("%c  %c  %c\n", shm[4], shm[5], shm[6]);
                 printf("%c  %c  %c\n", shm[7], shm[8], shm[9]);
                 printf("Parent: tie\n");
                 shm[0] = 'w';
                 break;
                }
                else
                {
                    shm[0] = 'c';
                }
            }
            else if(shm[0] == 'w')
            {
                exit(0); 
            }
            waitWhileEqual('c', shm);
        }
    }
    else
    {
        while(1)
        {
            //child
            if(shm[0] == 'c')
            {
                //critical section
               //child goes
                int go = validMove(shm);
                shm[go] = 'o';
                
                int won = isWin('o', shm);
                if(won == 1) //winner
                {
                 printf("%c  %c  %c\n", shm[1], shm[2], shm[3]);
                 printf("%c  %c  %c\n", shm[4], shm[5], shm[6]);
                 printf("%c  %c  %c\n", shm[7], shm[8], shm[9]);
                 printf("Child: winner\n");
                 shm[0] = 'w';
                 break;
                }
                else if(won == 2) //tie
                {
                 printf("%c  %c  %c\n", shm[1], shm[2], shm[3]);
                 printf("%c  %c  %c\n", shm[4], shm[5], shm[6]);
                 printf("%c  %c  %c\n", shm[7], shm[8], shm[9]);
                 printf("Child: tie\n");
                 shm[0] = 'w';
                 break;
                }
                else
                {
                    shm[0] = 'p';
                }
            }
            else if(shm[0] == 'w')
            {
                exit(0); 
            }
            waitWhileEqual('p', shm);
        }
    }
    
    //printf("The mem address is: %p\n", shm);
    return 0;
}

void waitWhileEqual(char val, char* shm)
{
    while(shm[0] == val)
    {
        //wait
        
    }
}

int isWin(char c, char* shm)
{
    if((((shm[1] == shm[2]) && (shm[1] == shm[3])) && (shm[1] == c)) || 
       (((shm[4] == shm[5]) && (shm[4] == shm[6])) && (shm[4] == c)) ||  
       (((shm[7] == shm[8]) && (shm[7] == shm[9])) && (shm[7] == c)) ||      
       (((shm[1] == shm[4]) && (shm[1] == shm[7])) && (shm[1] == c)) ||
       (((shm[2] == shm[5]) && (shm[2] == shm[8])) && (shm[2] == c)) ||
       (((shm[3] == shm[6]) && (shm[3] == shm[9])) && (shm[3] == c)) ||
       (((shm[1] == shm[5]) && (shm[1] == shm[9])) && (shm[1] == c)) ||
       (((shm[7] == shm[5]) && (shm[7] == shm[3])) && (shm[7] == c)))    
    {
        return 1; //winner
    }
    else if( shm[1] != '?' && 
             shm[2] != '?' && 
             shm[3] != '?' &&           
             shm[4] != '?' &&
             shm[5] != '?' &&
             shm[6] != '?' && 
             shm[7] != '?' && 
             shm[8] != '?' && 
             shm[9] != '?')
    {
        return 2; //tie
    }
    return 0; 
}

int validMove(char* shm)
{
    //get random move
    int go = 0;
    while(go == 0) 
    {
       go =  rand() % 10; 
    }
    if(shm[go] != '?')
    {
        go = validMove(shm); 
    }
    return go; 
}