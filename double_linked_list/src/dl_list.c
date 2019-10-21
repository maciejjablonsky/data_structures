//
// Created by maciek on 01.10.19.
//

#include "dl_list.h"
#include <stdlib.h>
#include <memory.h>
#include <assert.h>

dl_node_t *dl_list_create_node(void *item, size_t item_size, dl_storage_type info);

// unguarded
dl_node_t *dl_list_get_node(dl_list_t *list, size_t dest_index);

void dl_list_delete_node(dl_list_t *list, dl_node_t *node_to_delete);

dl_list_t *DL_LIST_create(const size_t item_size, const dl_storage_type info, void *(*destructor)(void *))
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

bool DL_LIST_add_item(dl_list_t *const list, void *const item)
{
    assert(list != NULL);

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

dl_node_t *dl_list_create_node(void *const item, const size_t item_size, const dl_storage_type info)
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


size_t DL_LIST_size(const dl_list_t *const list)
{
    assert(list != NULL);
    return list->size;
}

dl_node_t *dl_list_get_node(dl_list_t *const list, const size_t dest_index)
{
    dl_node_t *node = list->head;
    for (size_t i = 0; i < dest_index; ++i)
    {
        node = node->next;
    }
    return node;
}

void *DL_LIST_item_at(dl_list_t *list, const size_t index)
{
    if (index >= list->size)
    {
        return NULL;
    }
    return dl_list_get_node(list, index)->item;
}

// TODO add test
bool DL_LIST_delete_item_at(dl_list_t *const list, const size_t index)
{
    if (index >= list->size)
    {
        return false;
    }

    dl_node_t *node_to_delete = dl_list_get_node(list, index);
    if (list->item_destructor)
    {
        list->item_destructor(node_to_delete->item);
    }
    else
    {
        free(node_to_delete->item);
    }

    dl_list_delete_node(list, node_to_delete);
    return true;
}

void dl_list_delete_node(dl_list_t *list, dl_node_t *node_to_delete)
{
    if (list->head == node_to_delete)
    {
        list->head = node_to_delete->next;
    }
    if (list->tail == node_to_delete)
    {
        list->tail = node_to_delete->prev;
    }

    if (node_to_delete->prev)
    {
        node_to_delete->prev->next = node_to_delete->next;
    }
    if (node_to_delete->next)
    {
        node_to_delete->next->prev = node_to_delete->prev;
    }

    free(node_to_delete);
    list->size--;
}

dl_list_t *DL_LIST_delete(dl_list_t *const list)
{
    if (list)
    {
        while (list->size != 0)
        {
            if (!DL_LIST_delete_item_at(list, 0))
            {
                return list;
            }
        }
        free(list);
    }
    return NULL;
}