#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
	
	srand(time(NULL));
    int num;
    int i;
    
    int numberOfElements = 10;
    
    int begin = 0;
    int end = numberOfElements - 1;

    int nums[numberOfElements];
    for(i = 0; i < numberOfElements; i++)
    {
        nums[i] = rand()%2;
    }
	
	//int nums[] = {6,2,3,1,9,10,15,13,12,17};
	for(i = 0;i < numberOfElements;i++) 
	{
		printf("%d\n",nums[i]);
	}
	printf("************\n");
	mergeSortIntake(nums, numberOfElements);

	for(i = 0;i < numberOfElements;i++) 
	{
		printf("%d\n",nums[i]);
	}
}

void mergeSortIntake(int ar[], int numsLength)
{
    mergeSort(ar, 0, numsLength-1);
}
	
void mergeSort(int ar[], int begin, int end)
	{
		if(begin != end)
		{
			int leftBegin = begin;
			int rightBegin = ((end-begin)/2 + begin) + 1;
			int leftEnd = ((end-begin)/2 + begin);
			int rightEnd = end;
			
			mergeSort(ar, leftBegin, leftEnd);
			mergeSort(ar, rightBegin, rightEnd);
			
			int temp[rightEnd - leftBegin + 1];
			int currLeft = leftBegin;
			int currRight = rightBegin;
			int tempPos = 0;
			
			for(; tempPos < (rightEnd - leftBegin + 1); tempPos++)
			{
				if(currLeft > leftEnd)
				{
					temp[tempPos] = ar[currRight];
					currRight++;
				}
				else if(currRight > rightEnd)
				{
					temp[tempPos] = ar[currLeft];
					currLeft++;
				}
				else
				{
					if(ar[currLeft] < ar[currRight])
					{
						temp[tempPos] = ar[currLeft];
						currLeft++;
					}
					else
					{
						temp[tempPos] = ar[currRight];
						currRight++;
					}
				}
			}
			//temp is filled with the values from our 2 sublists in order
			int otherTempPos = 0;
			int j = leftBegin;
			for(; j <= rightEnd; j++)
			{
				ar[j] = temp[otherTempPos];
				otherTempPos++;
			}
		}
	}
