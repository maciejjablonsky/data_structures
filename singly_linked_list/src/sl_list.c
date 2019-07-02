//
// Created by maciek on 02.07.19.
//

#include "sl_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct
{
    void *item;
    void *next;
    size_t size;
} NODE;

struct sl_list
{
    NODE *head;
    NODE *tail;
    size_t size; // number of items on the list
};

NODE *SL_LIST_create_node(const void *item, size_t size);

SL_LIST *SL_LIST_create_list(void)
{
    SL_LIST *new_list = malloc(sizeof(SL_LIST));
    if (new_list == NULL)
    {
        return new_list;
    }
    new_list->head = new_list->tail = NULL;
    new_list->size = 0;
    return new_list;
}

SL_LIST *SL_LIST_delete_list(SL_LIST *list, void *(*delete_position)(void *position, size_t pos_size))
{

}


NODE *SL_LIST_create_node(const void *const item, size_t size)
{
    NODE *new_node = malloc(sizeof(NODE));
    if (new_node == NULL)
    {
        return new_node;
    }
    new_node->item = malloc(size);
    if (new_node->item == NULL)
    {
        free(new_node);
        return NULL;
    }
    memcpy(new_node->item, item, size);
    new_node->size = size;
    new_node->next = NULL;
    return new_node;
}

size_t SL_LIST_size(const SL_LIST *const list)
{
    if (list != NULL)
    {
        return list->size;
    }
    else
    {
        return 0;
    }
}

bool SL_LIST_add_position(SL_LIST *list, const void *const pos, const size_t size)
{
    NODE *new_node = SL_LIST_create_node(pos, size);
    if (new_node == NULL) { return false; }

    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    list->size++;
    return true;
}

void * SL_LIST_item_at(const SL_LIST * const list, const size_t index)
{
    if (index >= list->size) {return NULL;}
    NODE * node = list->head;
    for (size_t i = 0; i < index; ++i)
    {
        node = node->next;
    }
    return node->item;
}
