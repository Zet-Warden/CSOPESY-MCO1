/**
 * @file io.c
 * @author SY, Jacob Adrianne L. ; UY, Lorene C.
 * @brief Contains functions that reads data from text files and outputs the result to the console
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
 * @brief Get the Data From File object
 * 
 * @param filename      the name of the text file
 * @return DataInput*   address of the resulting DataInput object that stores information about 
 *                      the type of algorithm, number of processes, time slice, and processes
 */
DataInput*
getDataFromFile(String filename)
{
    FILE *fp;
    DataInput *data = (DataInput*)malloc(sizeof(DataInput));

    fp = fopen(filename, "r");
    if(fp == NULL) {
        fprintf(stderr, "<%s> not found.", filename);
        exit(1);
    }

    fscanf(fp, "%u %d %d", &data->schedAlgo, &data->numProcesses, &data->timeSlice);
    data->processes = (Process*) malloc(sizeof(Process) * data->numProcesses);

    for(int i = 0; i < data->numProcesses; i++) {
            int pid, arrivalTime, burstTime;
            fscanf(fp, "%d %d %d", &pid, &arrivalTime, &burstTime);
            
            data->processes[i].pid = pid;
            data->processes[i].order = i;
            data->processes[i].arrivalTime = arrivalTime;
            data->processes[i].burstTime = burstTime;

            data->processes[i].timeList = createTimeList();
            append(data->processes[i].timeList, -1, -1);
            data->processes[i].waitingTime = 0;

            data->processes[i].progress = 0;
            data->processes[i].status = NEW;
    }
    fclose(fp);
    return data;
}


/**
 * @brief Prints the processes
 * 
 * @param processes the processes to be printed out to the console
 * @param NUM_PROCESSES the number of processes
 */
void
printResult(Process processes[], int NUM_PROCESSES)
{
    float totalWaitingTime = 0.0;

    for(int i = 0; i < NUM_PROCESSES; i++) {
        printf("P[%d] ", processes[i].pid);

        for(int j = 0; j < processes[i].timeList->size; j++) {
            TimeNode *prevTime = get(processes[i].timeList, j - 1);
            TimeNode *currTime = get(processes[i].timeList, j);
            TimeNode *nextTime = get(processes[i].timeList, j + 1);
   
            // consecutive executions of sliced processes will be outputted as
            // one pair of start and end time for brevity
            if(prevTime == NULL || currTime->startTime != prevTime->endTime)
            {
                printf("Start Time: %d ", currTime->startTime);
            }

            if(nextTime == NULL || currTime->endTime != nextTime->startTime) {
                printf("End Time: %d | ", currTime->endTime);
            }
        }

        printf("Waiting time: %d\n", processes[i].waitingTime);
        totalWaitingTime += processes[i].waitingTime;
    }

    float avgWaitingTime = totalWaitingTime / NUM_PROCESSES;
    printf("Average waiting time: %.3f", avgWaitingTime);
}