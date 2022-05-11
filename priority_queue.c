/**
 * @file priority_queue.c
 * @author SY, Jacob Adrianne L. ; UY, Lorence C.
 * @brief  Priority Queue implementation using linked list
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"

/**
 * @brief Create a Priority Queue object
 * 
 * @param comparator function that is used to compare two processes; negative value takes higher priority, 0 means equals priority
 * @return PriorityQueue* the address of the Priority Queue object 
 */
PriorityQueue*
createPriorityQueue(int (*comparator)(const void*, const void*))
{
    PriorityQueue *queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->head = NULL;
    queue->comparator = comparator;
    return queue;
}

/**
 * @brief Pushes a process into the queue; ensures that processes within the queue are only pushed once
 *  
 * @param queue     the address of the queue that takes in the process object 
 * @param process   the address of process object to be inserted into the queue
 */
void
push(PriorityQueue *queue, Process *process)
{
    if(contains(queue, process)) return;

    ProcessNode *currNode = queue->head;
    ProcessNode *prevNode = NULL;

    while(currNode != NULL && (queue->comparator == NULL || queue->comparator(currNode->process, process) < 0)) {
        prevNode = currNode;
        currNode  = currNode->next;
    }

    if(prevNode == NULL) {
        ProcessNode *temp = queue->head;
        queue->head = (ProcessNode*)malloc(sizeof(ProcessNode));
        queue->head->process = process;
        queue->head->next = temp;
    } else {
        ProcessNode *temp = prevNode->next;
        prevNode->next = (ProcessNode*)malloc(sizeof(ProcessNode));
        prevNode->next->process = process;
        prevNode->next->next = temp;
    }
}

/**
 * @brief Removes the process node from the queue; returns the corresponding process object of the node
 * 
 * @param queue     the address of the queue where an element will be popped
 * @return Process* the address of the process popped; NULL if there are no processes inside the queue
 */
Process*
pop(PriorityQueue *queue)
{
    ProcessNode *temp = queue->head;
    if(temp == NULL) return NULL;

    queue->head = queue->head->next;

    Process *process = temp->process;
    free(temp);
    return  process;
}

/**
 * @brief Returns the process at the head of the queue
 * 
 * @param queue     the address of the queue to be peeked at
 * @return Process* the address of the process object
 */
Process*
peek(PriorityQueue *queue)
{
    return queue->head->process;
}

/**
 * @brief   Checks whether the given process is already inside the queue
 *          checks the pid of the process to determine equality
 * @param queue     the address of the queue to be checked
 * @param process   the process to be checked
 * @return int      1 if the the queue contains the process; 0 otherwise
 */
int
contains(PriorityQueue *queue, Process *process)
{
    ProcessNode *currNode = queue->head;
    int found = 0;

    while(currNode != NULL && !found) {
        found = currNode->process->pid == process->pid;
        currNode = currNode->next;
    }

    return found;
}

/**
 * @brief Checks if the queue is empty
 * 
 * @param queue the address of the queue to be checked
 * @return int  1 for empty; 0 otherwise
 */
int
isEmpty(PriorityQueue *queue)
{
    return queue->head == NULL;
}

/**
 * @brief Prints the pid of the processes inside the queue
 * 
 * @param queue the queue to be printed
 */
void 
printQueue(PriorityQueue *queue)
{
    ProcessNode *currNode = queue->head;

    while(currNode != NULL) {
        printf("pid: %d\n", currNode->process->pid);
        currNode = currNode->next;
    }
}