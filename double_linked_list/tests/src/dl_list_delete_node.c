//
// Created by maciek on 20.10.19.
//

#include <setjmp.h>
#include <stddef.h>
#include <stdarg.h>
#include <cmocka.h>
#include "../../src/dl_list.c"

dl_list_t *list = NULL;
#define ITEMS_COUNT 10

static int setup(void **state)
{
    (void) state;
    list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    assert_non_null(list);
    for (int i = 0; i < ITEMS_COUNT; ++i)
    {
        DL_LIST_add_item(list, &i);
    }
    return 0;
}

static int teardown(void **state)
{
    // free list
    return 0;
}

static void dl_list_delete_node__delete_1st_node(void **state)
{
    dl_node_t *node_to_delete = dl_list_get_node(list, 0);
    assert_non_null(node_to_delete);
    dl_node_t *node_after_deleted = node_to_delete->next;
    dl_node_t *node_before_deleted = NULL;
    dl_list_delete_node(list, node_to_delete);
    assert_ptr_equal(list->head, node_after_deleted);
    assert_null(node_after_deleted->prev);
}

static void dl_list_delete_node__delete_middle_node(void **state)
{
    assert_true(list->size > 4);
    dl_node_t *node_to_delete = dl_list_get_node(list, 4);
    dl_node_t *node_before_deleted = node_to_delete->prev;
    dl_node_t *node_after_deleted = node_to_delete->next;
    dl_list_delete_node(list, node_to_delete);
    assert_ptr_equal(node_before_deleted->next, node_after_deleted);
    assert_ptr_equal(node_after_deleted->prev, node_before_deleted);
}

static void dl_list_delete_node__delete_last_node(void **state)
{
    dl_node_t *node_to_delete = dl_list_get_node(list, ITEMS_COUNT - 1);
    dl_node_t *node_before_deleted = node_to_delete->prev;
    dl_list_delete_node(list, node_to_delete);
    assert_ptr_equal(list->tail, node_before_deleted);
    assert_ptr_equal(node_before_deleted->next, NULL);
}

static void dl_list_delete_node__delete_only_item(void **state)
{
    dl_list_t *private_list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    int item = 2;
    DL_LIST_add_item(private_list, &item);
    dl_node_t *node_to_delete = dl_list_get_node(private_list, 0);
    dl_list_delete_node(private_list, node_to_delete);
    assert_null(private_list->head);
    assert_null(private_list->tail);
    assert_int_equal(private_list->size, 0);
}

int main(void)
{
    struct CMUnitTest tests[] = {cmocka_unit_test_setup_teardown(dl_list_delete_node__delete_1st_node, setup, teardown),
                                 cmocka_unit_test_setup_teardown(dl_list_delete_node__delete_middle_node, setup,
                                                                 teardown),
                                 cmocka_unit_test_setup_teardown(dl_list_delete_node__delete_last_node, setup,
                                                                 teardown),
                                 cmocka_unit_test(dl_list_delete_node__delete_only_item)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}