#pragma once

typedef char String[255];

enum algo {FCFS, SJF, SRTF, RR};
enum status {NEW, RUNNING, WAITING, READY, TERMINATED};
enum schedType {NONPREEMPTIVE, PREEMPTIVE};

typedef struct TimeNode {
    int startTime;
    int endTime;
    struct TimeNode *next;
} TimeNode;

typedef struct TimeList {
    TimeNode *head;
    TimeNode *tail;
    int size;
} TimeList;

typedef struct Process {
    int pid;
    int order;
    int arrivalTime;
    int burstTime;

    TimeList *timeList;
    int waitingTime;
    int progress;

    enum status status;
} Process;

typedef struct DataInput {
    enum algo schedAlgo;
    int numProcesses;
    int timeSlice;

    struct Process *processes;
} DataInput;

typedef struct ProcessNode {
    Process *process;
    struct ProcessNode *next;
} ProcessNode;

typedef struct PriorityQueue {
    ProcessNode *head;
    int (*comparator)(const void*, const void*);
} PriorityQueue;

typedef struct SchedulingOptions {
    enum schedType schedType;
    int timeSlice;
    int (*comparator)(const void*, const void*);
} SchedulingOptions;