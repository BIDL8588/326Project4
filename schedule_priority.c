/*
 * Priority scheduling
 */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

/*
 * Your code and design here:
 */

#include <string.h>

struct node *head = NULL; 

void add(char *name, int priority, int burst) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    if (newTask == NULL) 
    {
        fprintf(stderr, "Error: Could not allocate memory for new task\n");
        return;
    }
    newTask->name = (char *)malloc(strlen(name) + 1);
    if (newTask->name == NULL) 
    {
        fprintf(stderr, "Error: Could not allocate memory for task name\n");
        free(newTask);
        return;
    }

    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = 0;

    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) 
    {
        fprintf(stderr, "Error: Could not allocate memory for new node\n");
        free(newTask->name);
        free(newTask);
        return;
    }
    newNode->task = newTask;
    newNode->next = NULL;

    if (head == NULL) 
    {
        head = newNode;
    } else {
        struct node *current = head;
        while (current->next != NULL) 
        {
            current = current->next;
        }
        current->next = newNode;
    }
}
void schedule()
{
    struct node *current = head; 
    int totalWait = 0; 
    int waitingTime =0; 
    int count = 0; 
    while(current != NULL)
    {   if(current->task == NULL)
    {
        fprintf(stderr, "Error: Task is NULL in the list\n"); 
    }
        printf("Task %s (Priority %d): Waiting Time = %d\n", current->task->name, current->task->priority, waitingTime);
        totalWait += waitingTime; 

        waitingTime += current->task->burst; 

        current = current->next; 
        count++; 
    }
    if (count > 0)
    {
        float averageWait = (float)totalWait/ count; 
        printf("Average Waiting Time: %.2f\n", averageWait);
    }  
}
