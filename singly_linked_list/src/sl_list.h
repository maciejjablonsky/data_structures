//
// Created by maciek on 02.07.19.
//

#ifndef DATA_STRUCTURES_SL_LIST_H
#define DATA_STRUCTURES_SL_LIST_H

#include <stddef.h>

#ifndef bool

typedef enum
{
    false, true
} bool;

#endif


/*
 * Best approach to use this list is to provide your own ITEM definition every time you use this sl list.
 * Every node on list stores void pointer to the item.
 * Every item is copied when putting on the list so you need to provide your own item_destructor function.
 * With such approach list may be used few times in the program, while
 * every instance stores different data type.
 */


typedef struct sl_list SL_LIST;


// returns pointer to initialized list structure or null in case of error
// item_destructor should be a pointer to your own function that cares about proper deletion of your item
// or it can be NULL if list stores just plain e.g. ints or doubles or anything without allocated memory
SL_LIST *SL_LIST_create(size_t item_size, void *(*item_destructor)(void *item_to_delete));

// returns number of items on the list
size_t SL_LIST_size(const SL_LIST *list);

// adds item on the list
// returns true if everything went fine or false when wrong (doesn't add item then)
bool SL_LIST_add_item(SL_LIST *list, void *item);

// returns pointer to item stored on the list or null in case of non existing index
void *SL_LIST_item_at(const SL_LIST *list, size_t index);

/*
 * returns true if error didn't occur
 * function should take address of item and return also address of item
 * function can do everything with item, it's possible to free item's memory and replace
 * it with a new memory
 * in such case be careful about good free <-> assign mechanism
 */
bool SL_LIST_apply_foreach(SL_LIST *list, void *(*function)(void *item));

// returns true if item was deleted or false when index is out-of-range
bool SL_LIST_delete_item_at(SL_LIST *list, size_t index);

// deletes every node from list and returns null
// should be used like this
// SL_LIST * list = SL_LIST_create(size, destructor);
// list = SL_LIST_delete_list(list);
SL_LIST *SL_LIST_delete_list(SL_LIST *list);


#endif //DATA_STRUCTURES_SL_LIST_H
