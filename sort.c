/**
 * @file sort.c
 * @author SY, Jacob Adrianne L. ; UY, Lorene C.
 * @brief Contains custom comparator functions
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
 * @brief Compares two processes based on their arrival time
 * 
 * @param a     1st process
 * @param b     2nd process
 * @return int  positive if 2nd process arrives after 1st process, else negative; 
 *              if both arrive at the same time, positive if 2nd process appears after 1st process in the text file, else negative  
 */
int
arrivalTimeComparator(const void *a, const void *b)
{
    Process l = *((Process *)a);
    Process r = *((Process *)b);

    if(l.arrivalTime == r.arrivalTime) return l.order - r.order;
    return l.arrivalTime - r.arrivalTime;
}

/**
 * @brief Compares two processes based on their burst time
 * 
 * @param a     1st process
 * @param b     2nd process
 * @return int  positive if 2nd process finishes faster after 1st process, else negative; 
 *              if both finish at the same rate, positive if 2nd process appears after 1st process in the text file, else negative
 */
int
burstTimeComparator(const void *a, const void *b)
{
    Process l = *((Process *)a);
    Process r = *((Process *)b);

    if(l.burstTime == r.burstTime) {
        if(l.arrivalTime == r.arrivalTime) return l.order - r.order;
        return l.arrivalTime - r.arrivalTime;
    }
    return l.burstTime - r.burstTime;
}