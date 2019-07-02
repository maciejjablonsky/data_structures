//
// Created by maciek on 02.07.19.
//

#ifndef DATA_STRUCTURES_SL_LIST_H
#define DATA_STRUCTURES_SL_LIST_H

#include <stddef.h>

#ifndef bool

typedef enum {false, true} bool;

#endif

typedef struct sl_list SL_LIST;

SL_LIST * SL_LIST_create_list(void);

SL_LIST * SL_LIST_delete_list(SL_LIST *list, void *(*delete_position)(void *position, size_t pos_size));

size_t SL_LIST_size(const SL_LIST *list);

bool SL_LIST_add_position(SL_LIST * list, const void *pos, size_t size);


#endif //DATA_STRUCTURES_SL_LIST_H
