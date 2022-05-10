#include <stdio.h>
#include <stdlib.h>
#include "types.h"

TimeList*
createTimeList()
{
    TimeList *list = (TimeList*)malloc(sizeof(TimeList));
    list->head = NULL;
    list->tail = list->head;
    list->size = 0;
    return list;
}

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