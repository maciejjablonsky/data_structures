//
// Created by maciek on 13.10.19.
//

#include "check_execution_time.h"
#include <stdio.h>

void reset_timer(check_time_t *timer)
{
    timer->start = 0;
    timer->end = 0;
}

void start_timer(check_time_t *timer)
{
    timer->start = clock();
}

void stop_timer(check_time_t *timer)
{
    timer->end = clock();
}

void print_timer_results(check_time_t *timer)
{
    printf("Test lasted %lf miliseconds\n", (timer->end - timer->start) * (double) 1000 / CLOCKS_PER_SEC);
}