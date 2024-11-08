/**
 * FCFS scheduling
 */
 
#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

//Your code and design here
void waitingTime(Task myTask[],int n)
    {
        int waitingTi[n]; 

        for(int i = 1; i < n; i ++)
        {
            waitingTi[i]= myTask[i - 1].burst + waitingTi [i-1];
            myTask[i].tid = i;
        }

        for(int i = 1; i < n; i++)
        {
            printf("Task %d: Waiting Time = %d \n", myTask[i].tid, waitingTi[i]); 
        }
    }

void averagewaitingTime(Task myTask[], int n)
    {
        int averageTime; 
        int totalWait = 0; 
        int waitingTime =0; 

        for(int i = 1; i < n; i ++)
        {

            waitingTime += myTask[i-1].burst;
            totalWait += waitingTime;
        }

        averageTime = totalWait/n;
        printf("Average waiting time: ", averageTime); 
        
    }
