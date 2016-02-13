#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
/* Allow "cc -D" to override definition */
 
void main(int argc, char *argv[])
{
    int cnt;
    char ch, ch1;
    FILE *fp1, *fp2;
 
    if (fp1 = fopen(argv[1], "r"))    
    {
        fp2 = fopen(argv[2], "w");
        cnt = count_characters(fp1); 
        fseek(fp1, -1L, 2);
 
        while (cnt)
        {
            ch = fgetc(fp1);
            fputc(ch, fp2);
            fseek(fp1, -2L, 1);
            cnt--;
        }
    }
}

int count_characters(FILE *f) 
{
    fseek(f, -1L, 2);
    int last_pos = ftell(f);
    last_pos++;
    return last_pos;
}