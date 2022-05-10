/**
 * @file list.c
 * @author SY, Jacob Adrianne L. ; UY, Lorene C.
 * @brief Linked List implementation
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "types.h"

/**
 * @brief Create a TimeList object
 * 
 * @return TimeList* the address of the TimeList object 
 */
TimeList*
createTimeList()
{
    TimeList *list = (TimeList*)malloc(sizeof(TimeList));
    list->head = NULL;
    list->tail = list->head;
    list->size = 0;
    return list;
}

/**
 * @brief Appends a TimeNode to the TimeList
 * 
 * @param list      the address of the list where a TimeNode will be appended to
 * @param startTime starting time of the process
 * @param endTime   ending time of process
 */
void
append(TimeList *list, int startTime, int endTime)
{
    TimeNode *newTime = (TimeNode*)malloc(sizeof(TimeNode));
    newTime->startTime = startTime;
    newTime->endTime = endTime;

    if(list->head == NULL) {
        list->head = newTime;
        list->head->next = NULL;
        
        list->tail = list->head;
    }
    else 
    {
        TimeNode *currTail = list->tail;
        currTail->next = newTime;
        currTail->next->next = NULL;

        list->tail = currTail->next;
    }

    list->size++;
}

/**
 * @brief Returns a TimeNode at the specified index
 * 
 * @param list       the address of the TimeList object
 * @param index      index of the TimeNode
 * @return TimeNode* the address of the TimeNode at the specified index; NULL if index is less than 0
 */
TimeNode*
get(TimeList *list, int index)
{
    if(index < 0) return NULL;
    
    TimeNode *currNode = list->head;
    int currIndex = 0;

    while(currNode != NULL && currIndex < index) {
        currNode = currNode->next;
        currIndex++;
    }
    return currNode;
}