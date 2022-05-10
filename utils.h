#include "types.h"

DataInput* getDataFromFile(String filename);
void printResult(Process processes[], int NUM_PROCESSES);

int arrivalTimeComparator(const void *a, const void *b);
int burstTimeComparator(const void *a, const void *b);

PriorityQueue* createPriorityQueue(int (*comparator)(const void*, const void*));
void push(PriorityQueue *queue, Process *process);
Process* pop(PriorityQueue *queue);
Process* peek(PriorityQueue *queue);
int contains(PriorityQueue *queue, Process *process);
int isEmpty(PriorityQueue *queue);
void printQueue(PriorityQueue *queue);

TimeList* createTimeList();
void append(TimeList *list, int startTime, int endTime);
TimeNode* get(TimeList *list, int index);

void scheduleProcesses(Process processes[], int NUM_PROCESSES, SchedulingOptions *options);
void fcfs(Process processes[], int NUM_PROCESSES);
void sjf(Process processes[], int NUM_PROCESSES);
void srtf(Process processes[], int NUM_PROCESSES, int timeSlice);
void rr(Process processes[], int NUM_PROCESSES, int timeSlice);