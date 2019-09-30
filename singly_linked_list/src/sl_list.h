//
// Created by maciek on 02.07.19.
//

#ifndef DATA_STRUCTURES_SL_LIST_H
#define DATA_STRUCTURES_SL_LIST_H

#include <stddef.h>
#include <stdbool.h>

#ifndef bool

typedef enum
{
    false, true
} bool;

#endif

typedef struct sl_node sl_node_t;
struct sl_node
{
    void *item;
    sl_node_t *next;
};


/*
 * List stores user provided items.
 * User can choose between storing copy or pointer to item when adding.
 * If item contains dynamic allocated memory, user should provide destructor_function to prevent memory leaks.
 */
typedef struct sl_list sl_list_t;
struct sl_list
{
    sl_node_t *head;
    sl_node_t *tail;
    size_t size; // number of items on the list
    size_t item_size;

    void *(*item_destructor)(void *item_to_delete);
};




typedef enum
{
    COPY_ITEM, COPY_POINTER
} copy_type;


/*
 * creates initialized empty list
 *
 * return value: pointer to initialized list structure or null otherwise
 * parameters:
 *  - item_size: size of item in bytes
 *  - item_destructor: pointer to user provided function or NULL when there is no dynamically allocated memory
 */
sl_list_t *SL_LIST_create(size_t item_size, void *(*item_destructor)(void *item_to_delete));

/*
 * returns number of items on the list
 *
 * return value: length of list
 * parameters:
 *  - list: initialized list
 */
size_t SL_LIST_size(const sl_list_t *list);

/*
 * adds item at the end off the list
 *
 * return value: true if item added properly, false otherwise (doesn't add item then)
 * parameters:
 *  - list: initialized sl_list
 *  - item: address of item
 *  - copy: copy_type value describing whether copy whole item or just a address
 */
bool SL_LIST_add_item(sl_list_t *list, void *item, copy_type copy);

/*
 * gets access to i-th item
 *
 * return value: address of i-th item or NULL in case of non existing index
 * parameters:
 *  - list: initialized sl_list
 *  - index: number of item
 */
void *SL_LIST_item_at(const sl_list_t *list, size_t index);

/*
 * applies 'function' to every item on the list
 *
 * return value: true if everything went fine, false otherwise
 * parameters:
 *  - list: initialized sl_list
 *  - function: address of function that takes pointer to item and also returns pointer to item
 *              it doesn't have to be the same item, but you should be careful about freeing memory
 *
 */
bool SL_LIST_apply_foreach(sl_list_t *list, void *(*function)(void *item));

/*
 * deletes i-th item from the list
 *
 * return value: true if item was deleted, false when index is out-of-range
 * parameters:
 *  - list: initialized sl_list
 *  - index: unsigned index of item
 */
bool SL_LIST_delete_item_at(sl_list_t *list, size_t index);

/*
 * deletes every sl_node from list
 *
 * return value: NULL
 * parameters:
 *  - list: initialized list
 *
 *
 * make sure to assign returned NULL to list_ptr:
 * ```
 * list = SL_LIST_delete_list(list);
 * ```
 */
sl_list_t *SL_LIST_delete_list(sl_list_t *list);

/*
 * macro loop that iterates over every node
 * breaks when node or item are NULL
 *
 * parameters:
 *  - sl_list_ptr: sl_list_t * pointer to initialized list
 *  - item: user_provided_item_type_t * pointer that will get address of items on the list
 *
 * usage: // increments every value on the list
 * size_t * item;
 * sl_list_foreach(list, item)
 * {
 *     (*item)++;
 * }
 *
 */
#define sl_list_foreach(sl_list_ptr, item) \
    for (\
        sl_node_t *cursor_node_ptr = (sl_list_ptr)->head; \
        (cursor_node_ptr)\
        && ((item) = (cursor_node_ptr)->item);\
        cursor_node_ptr = cursor_node_ptr->next\
    )\



#endif //DATA_STRUCTURES_SL_LIST_H
