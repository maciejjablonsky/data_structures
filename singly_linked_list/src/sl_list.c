//
// Created by maciek on 02.07.19.
//

#include "sl_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node NODE;

struct node
{
    ITEM item;
    NODE *next;
};


struct sl_list
{
    NODE *head;
    NODE *tail;
    size_t size; // number of items on the list
};

NODE *sl_list_create_node(const ITEM *item);

NODE *sl_list_get_node(const SL_LIST *list, size_t index);

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


NODE *sl_list_create_node(const ITEM *item)
{
    NODE *new_node = malloc(sizeof(NODE));
    if (new_node == NULL)
    {
        return new_node;
    }
    memcpy(&new_node->item, item, sizeof(ITEM));
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

bool SL_LIST_add_position(SL_LIST *list, const ITEM *const item)
{
    NODE *new_node = sl_list_create_node(item);
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

ITEM *SL_LIST_item_at(const SL_LIST *const list, const size_t index)
{
    if (index >= list->size) { return NULL; }

    return &sl_list_get_node(list, index)->item;
}

NODE *sl_list_get_node(const SL_LIST *const list, const size_t index)
{
    NODE *node = list->head;
    for (size_t i = 0; i < index; ++i)
    {
        node = node->next;
    }
    return node;
}

bool SL_LIST_apply_foreach(SL_LIST *list, ITEM *(*func)(ITEM *item))
{
    if (list == NULL || list->head == NULL || func == NULL) { return false; }

    NODE *node = list->head;
    while (node != NULL)
    {
        node->item = *func(&node->item);
        node = node->next;
    }
    return true;
}


bool SL_LIST_delete_item_at(SL_LIST *list, size_t index)
{
    if (index >= list->size) { return false; }

    if (index > 0)
    {
        NODE * prev_node = sl_list_get_node(list, index - 1);
        NODE * node_to_delete = prev_node->next;
        prev_node->next = prev_node->next->next;
        free(node_to_delete);
    }
    else
    {
        NODE * node_to_delete = list->head;
        list->head = list->head->next;
        free(node_to_delete);
    }
    list->size--;
    return true;
}

SL_LIST * SL_LIST_delete_list(SL_LIST * list)
{
    if (list != NULL)
    {
        while(list->size != 0)
        {
            if(!SL_LIST_delete_item_at(list, 0))
            {
                return list;
            }
        }
        free(list);
    }
    return NULL;
}