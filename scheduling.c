/**
 * @file scheduling.c
 * @author SY, Jacob Adrianne L. ; UY, Lorene C.
 * @brief Contains functions for different scheduling algorithms (First-Come First-Serve, Shortest-Job First, Shortest-Remaining-Time-First, Round-Robin)
 * @version 0.1
 * @date 2022-05-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include "types.h"
#include "utils.h"

/**
 * @brief   Simulates CPU scheduling process based on the scheduling options passed.
 * 
 * @param processes     the processes to be scheduled, will be mutated based on the scheduling process
 * @param NUM_PROCESSES the number of processes
 * @param options       the scheduling options to determine how the processes will be scheduled
 */
void
scheduleProcesses(Process processes[], int NUM_PROCESSES, SchedulingOptions *options)
{
    int finishedProcesses = 0;
    int time = 0;

    PriorityQueue *pendingProcesses = createPriorityQueue(options->comparator);
    Process *currProcess = NULL;
    Process *interruptedProcess = NULL;
     
    while(finishedProcesses < NUM_PROCESSES) {
        // process current job
        if(currProcess != NULL) {
            // update how long the process has been running
            // throughout its entire life cycle
            currProcess->progress++;
            // decrement remaining needed CPU burst time
            currProcess->burstTime--;

            // check if process is done
            if(!currProcess->burstTime) {
                currProcess->timeList->tail->endTime = time;
                currProcess->status = TERMINATED;
                finishedProcesses++;

                currProcess = NULL;
            }

            // check if the algo supports preemption and
            // if its time to interrupt/slice the current executing process
            else if(options->schedType == PREEMPTIVE && currProcess->progress % options->timeSlice == 0) {
                currProcess->timeList->tail->endTime = time;
                currProcess->status = READY;
                // create a record to keep track
                // of each start and end time in-between slices
                append(currProcess->timeList, -1, -1);

                interruptedProcess = currProcess;
                currProcess = NULL;
            }
        }

        // add all READY processes to the queue if not yet included
        for(int i = 0; i < NUM_PROCESSES; i++) {
            if(processes[i].status == NEW && processes[i].arrivalTime <= time) {
                processes[i].status = READY;
            }

            // READY processes that were not interupted take priority
            if(processes[i].status == READY &&
                (interruptedProcess == NULL || processes[i].pid != interruptedProcess->pid)) {
                push(pendingProcesses, &processes[i]);
            }
        }

        // push previously interrupted process (if any) back to the queue
        if(interruptedProcess != NULL) {
            push(pendingProcesses, interruptedProcess);
            interruptedProcess = NULL;
        }

        // get the process to be processed next if CPU is free
        if(currProcess == NULL) {
            currProcess = pop(pendingProcesses);
            if(currProcess != NULL) {
                currProcess->status = RUNNING;
                currProcess->timeList->tail->startTime = time;
            }
        } 

        // increment the waiting time of READY processes
        // as they are not currently running
        for(int i = 0; i < NUM_PROCESSES; i++) {
            if(processes[i].status == READY) {
                processes[i].waitingTime++;
            }
        }
       
        time++;
    }
}

/**
 * @brief   First-Come First-Serve(FCFS) scheduling algorithm
 * 
 * @param processes     the processed to be scheduled, will be mutated based on the results of the FCFS algorithm
 * @param NUM_PROCESSES the number of processes
 */
void 
fcfs(Process processes[], int NUM_PROCESSES)
{
    SchedulingOptions *options = (SchedulingOptions*)malloc(sizeof(SchedulingOptions));
    options->schedType = NONPREEMPTIVE;
    options->comparator = arrivalTimeComparator;
    options->timeSlice = 1;
    scheduleProcesses(processes, NUM_PROCESSES, options);
}

/**
 * @brief   Shortest-Job First scheduling algorithm
 * 
 * @param processes     the processed to be scheduled, will be mutated based on the results of the SJF algorithm
 * @param NUM_PROCESSES the number of processes
 */
void 
sjf(Process processes[], int NUM_PROCESSES)
{
    SchedulingOptions *options = (SchedulingOptions*)malloc(sizeof(SchedulingOptions));
    options->schedType = NONPREEMPTIVE;
    options->comparator = burstTimeComparator;
    options->timeSlice = 1;
    scheduleProcesses(processes, NUM_PROCESSES, options);
}

/**
 * @brief   Shortest-Remaining-Time-First scheduling algorithm
 * 
 * @param processes     the processed to be scheduled, will be mutated based on the results of the SRTF algorithm
 * @param NUM_PROCESSES the number of processes
 */
void 
srtf(Process processes[], int NUM_PROCESSES)
{
    SchedulingOptions *options = (SchedulingOptions*)malloc(sizeof(SchedulingOptions));
    options->schedType = PREEMPTIVE;
    options->comparator = burstTimeComparator;
    options->timeSlice = 1;
    scheduleProcesses(processes, NUM_PROCESSES, options);
}

/**
 * @brief   Round-Robin scheduling algorithm
 * 
 * @param processes     the processed to be scheduled, will be mutated based on the results of the RR algorithm
 * @param NUM_PROCESSES the number of processes
 * @param timeSlice     time slice/time quantum
 */
void 
rr(Process processes[], int NUM_PROCESSES, int timeSlice)
{
    SchedulingOptions *options = (SchedulingOptions*)malloc(sizeof(SchedulingOptions));
    options->schedType = PREEMPTIVE;
    options->comparator = NULL;
    options->timeSlice = timeSlice;
    scheduleProcesses(processes, NUM_PROCESSES, options);
}