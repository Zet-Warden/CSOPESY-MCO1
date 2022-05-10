#include <stdlib.h>
#include "types.h"
#include "utils.h"

int
arrivalTimeComparator(const void *a, const void *b)
{
    Process l = *((Process *)a);
    Process r = *((Process *)b);

    if(l.arrivalTime == r.arrivalTime) return l.order - r.order;
    return l.arrivalTime - r.arrivalTime;
}

int
burstTimeComparator(const void *a, const void *b)
{
    Process l = *((Process *)a);
    Process r = *((Process *)b);

    if(l.burstTime == r.burstTime) return l.order - r.order;
    return l.burstTime - r.burstTime;
}

void
sortByArrivalTime(Process processes[], int size)
{
    qsort(processes, size, sizeof(Process), arrivalTimeComparator);
}

