//
// Created by maciek on 02.07.19.
//

#ifndef DATA_STRUCTURES_SL_LIST_H
#define DATA_STRUCTURES_SL_LIST_H

#include <stddef.h>

#ifndef bool

typedef enum {false, true} bool;

#endif


// ITEM DEFINITION
// you can edit this

typedef struct {
    int a;
    int b;
} ITEM;



typedef struct sl_list SL_LIST;

SL_LIST * SL_LIST_create_list(void);

size_t SL_LIST_size(const SL_LIST *list);

bool SL_LIST_add_position(SL_LIST * list, const ITEM *item);

ITEM * SL_LIST_item_at(const SL_LIST *list, size_t index);

bool SL_LIST_apply_foreach(SL_LIST * list, ITEM * (*function)(ITEM * item));

bool SL_LIST_delete_item_at(SL_LIST * list, size_t index);

SL_LIST * SL_LIST_delete_list(SL_LIST * list);


#endif //DATA_STRUCTURES_SL_LIST_H
