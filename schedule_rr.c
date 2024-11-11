/**
 * Round-robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "string.h"



/*
 * Your code and design here:
 */

struct node *head = NULL; 

void add(char *name, int priority, int burst)
{
    Task *newTask = (Task *)malloc(sizeof(Task));
    if (newTask == NULL) 
    {
        fprintf(stderr, "Error: Could not allocate memory for new task\n");
        return;
    }
    newTask->name = strdup(name);
    newTask->priority = priority; 
    newTask->burst = burst; 

    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) 
    {
        fprintf(stderr, "Error: Could not allocate memory for new node\n");
        free(newTask);
        return;
    }

    newNode->task = newTask; 
    newNode->next = NULL;

    if(head == NULL)
    {
        head = newNode; 
    }
    else{
        struct node *temp = head; 
        while(temp->next != NULL)
        {
            temp = temp->next; 
        }
        temp->next = newNode; 
    }
}



void schedule() {
    int quantum = 10;                
    int totalElapsed = 0;            
    int totalTurnaroundTime = 0;     
    int taskCount = 0;              
    struct node *current = head;

    while (current != NULL) {
        taskCount++;
        current = current->next;
    }
    int tasksRemaining = 1;

    while (tasksRemaining > 0) {
        tasksRemaining = 0; 
        current = head;
        while (current != NULL) {
            if (current->task->burst > 0) { 
                tasksRemaining++;

                int timeSlice;
                if (current->task->burst <= quantum) {
                    timeSlice = current->task->burst;
                } else {
                    timeSlice = quantum;
                }
                run(current->task, timeSlice);
                current->task->burst -= timeSlice;
                totalElapsed += timeSlice;

                if (current->task->burst <= 0) {
                    totalTurnaroundTime += totalElapsed;
                } 
            }
            current = current->next; 
        }
    }
    if (taskCount > 0) {
        float averageTurnaroundTime = (float)totalTurnaroundTime / taskCount;
        printf("Average Turnaround Time: %.2f ms\n", averageTurnaroundTime);
    }
}
