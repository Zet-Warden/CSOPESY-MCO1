#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"

int
main()
{
    String filename;
    DataInput *data;

    printf("Filename: ");
    scanf("%s", filename);

    data = getDataFromFile(filename);
    switch (data->schedAlgo)
    {
        case FCFS:
            fcfs(data->processes, data->numProcesses);
            break;
        case SJF:
            sjf(data->processes, data->numProcesses);
            break;
        case SRTF:
            srtf(data->processes, data->numProcesses);
            break;
        case RR:
            rr(data->processes, data->numProcesses, data->timeSlice);
        default:
            break;
    }
    printResult(data->processes, data->numProcesses);    
    return 0;
}