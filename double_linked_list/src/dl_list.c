//
// Created by maciek on 01.10.19.
//

#include "dl_list.h"
#include <stdlib.h>
#include <memory.h>

dl_node_t *dl_list_create_node(void *item, size_t item_size, dl_storage_type info);

dl_list_t *DL_LIST_create(size_t item_size, dl_storage_type info, void *(*destructor)(void *))
{
    dl_list_t *new_list = malloc(sizeof(dl_list_t));
    if (new_list == NULL)
    {
        return new_list;
    }
    new_list->head = new_list->tail = NULL;
    new_list->item_size = item_size;
    new_list->storage_info = info;
    new_list->item_destructor = destructor;
    return new_list;
}

bool DL_LIST_add_item(dl_list_t *list, void *item)
{
    dl_node_t *new_node = dl_list_create_node(item, list->item_size, list->storage_info);
    if (new_node == NULL) { return false; }

    if (list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        new_node->prev = list->tail;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
    return true;
}

dl_node_t *dl_list_create_node(void *item, size_t item_size, dl_storage_type info)
{
    dl_node_t *new_node = malloc(sizeof(dl_node_t));
    if (new_node == NULL)
    {
        return new_node;
    }
    switch (info)
    {
        case DL_COPY_POINTER:new_node->item = item;
            break;
        case DL_COPY_ITEM:
        default:new_node->item = malloc(item_size);
            if (new_node->item != NULL)
            {
                memcpy(new_node->item, item, item_size);
            }
            else
            {
                exit(1);
            }
    }
    new_node->next = new_node->prev = NULL;
    return new_node;
}