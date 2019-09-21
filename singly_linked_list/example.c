//
// Created by maciek on 02.07.19.
//

#include <stdio.h>
#include "src/sl_list.h"

void *print_int(void *item)
{
    printf("%i\n", *(int *) item);
    return item;
}

void *print_double(void *item)
{
    printf("%lf\n", *(double *) item);
    return item;
}

int main()
{
    sl_list_t *int_list = SL_LIST_create(sizeof(int), NULL);
    sl_list_t *double_list = SL_LIST_create(sizeof(double), NULL);
    for (size_t i = 0; i < 10; ++i)
    {
        double k = (double) i / 3;
        SL_LIST_add_item(int_list, &i);
        SL_LIST_add_item(double_list, &k);
    }
    printf("List of ints:\n");
    SL_LIST_apply_foreach(int_list, print_int);
    putchar('\n');

    printf("List of doubles:\n");
    SL_LIST_apply_foreach(double_list, print_double);

    SL_LIST_delete_list(double_list);
    SL_LIST_delete_list(int_list);
    return 0;
}