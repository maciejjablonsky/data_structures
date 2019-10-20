//
// Created by maciek on 13.10.19.
//

#ifndef DATA_STRUCTURES_CHECK_EXECUTION_TIME_H
#define DATA_STRUCTURES_CHECK_EXECUTION_TIME_H

#include <time.h>

typedef struct
{
    clock_t start;
    clock_t end;
} check_time_t;

void reset_timer(check_time_t *timer);

void start_timer(check_time_t *timer);

void stop_timer(check_time_t *timer);

void print_timer_results(check_time_t *timer);

#endif //DATA_STRUCTURES_CHECK_EXECUTION_TIME_H
