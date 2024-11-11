/*
 * Priority scheduling
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

void add(char *name, int priority, int burst) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    if (newTask == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for new task\n");
        return;
    }

    newTask->name = (char *)malloc(strlen(name) + 1);
    if (newTask->name == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for task name\n");
        free(newTask);
        return;
    }

    strcpy(newTask->name, name);
    newTask->priority = priority;
    newTask->burst = burst;
    newTask->tid = 0;

    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for new node\n");
        free(newTask->name);
        free(newTask);
        return;
    }
    newNode->task = newTask;
    newNode->next = head;
    head = newNode;
}

void schedule() {
    int totalWait = 0;
    int waitingTime = 0;
    int count = 0;

    while (head != NULL) {
        struct node *highestPriorityNode = head;
        struct node *current = head;
        struct node *prevHighest = NULL;

        while (current->next != NULL) {
            if (current->next->task->priority > highestPriorityNode->task->priority) {
                highestPriorityNode = current->next;
                prevHighest = current;
            }
            current = current->next;
        }

        if (highestPriorityNode != head) {
            prevHighest->next = highestPriorityNode->next;
        } else {
            head = head->next;
        }

        run(highestPriorityNode->task, highestPriorityNode->task->burst);

        // Calculate total waiting time
        totalWait += waitingTime;
        waitingTime += highestPriorityNode->task->burst;
        count++;

        free(highestPriorityNode->task->name);
        free(highestPriorityNode->task);
        free(highestPriorityNode);
    }

    if (count > 0) {
        float averageWait = (float)totalWait / count;
        printf("Average Waiting Time: %.2f\n", averageWait);
    }
}
