//
// Created by maciek on 20.10.19.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/dl_list.c"

dl_list_t *list;

#define ITEMS_COUNT 10

static int setup(void **state)
{
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
    DL_LIST_delete(list);
    return 0;
}

static void dl_list_get_node__get_1st_item(void **state)
{
    dl_node_t *node = dl_list_get_node(list, 0);
    assert_non_null(node);
    assert_int_equal(*(int *) node->item, 0);
}

static void dl_list_get_node__get_5th_item(void **state)
{
    assert(ITEMS_COUNT >= 4);
    dl_node_t *node = dl_list_get_node(list, 4);
    assert_non_null(node);
    assert_int_equal(*(int *) node->item, 4);
}

static void dl_list_get_node__get_last_item(void **state)
{
    dl_node_t *node = dl_list_get_node(list, ITEMS_COUNT - 1);
    assert_non_null(node);
    assert_int_equal(*(int *) node->item, ITEMS_COUNT - 1);

}

static void dl_list_get_node__jumping_through_list(void **state)
{
    // going to first node
    dl_node_t *node = dl_list_get_node(list, 0);
    assert_non_null(node);
    assert_int_equal(*(int *) node->item, 0);

    // going to last node
    node = dl_list_get_node(list, ITEMS_COUNT - 1);
    assert_non_null(node);
    assert_int_equal(*(int *) node->item, ITEMS_COUNT - 1);

    // going left but from lower indexes
    node = dl_list_get_node(list, 3);
    assert_non_null(node);
    assert_int_equal(*(int *) node->item, 3);

    // going left but from higher indexes
    node = dl_list_get_node(list, 2);
    assert_non_null(node);
    assert_int_equal(*(int *) node->item, 2);

    // going right from lowe indexes
    node = dl_list_get_node(list, 5);
    assert_non_null(node);
    assert_int_equal(*(int *) node->item, 5);

    // going right but from higher indexes
    node = dl_list_get_node(list, 8);
    assert_non_null(node);
    assert_int_equal(*(int *) node->item, 8);

    // going to the same index as previous
    node = dl_list_get_node(list, 8);
    assert_non_null(node);
    assert_int_equal(*(int *) node->item, 8);
}

// I'm not testing improper indexes because dl_list_get_node is meant to be unguarded
/*
static void dl_list_get_node__too_big_index(void**state)
{
    dl_node_t * node = dl_list_get_node(list, ITEMS_COUNT);
    assert_null(node);
}

static void dl_list_get_node__negative_index(void ** state)
{
    dl_node_t * node = dl_list_get_node(list, -1);
    assert_null(node);
}*/

int main(void)
{
    struct CMUnitTest tests[] = {cmocka_unit_test(dl_list_get_node__get_1st_item),
                                 cmocka_unit_test(dl_list_get_node__get_5th_item),
                                 cmocka_unit_test(dl_list_get_node__get_last_item),
                                 cmocka_unit_test(dl_list_get_node__jumping_through_list),
            /*cmocka_unit_test(dl_list_get_node__too_big_index),
            cmocka_unit_test(dl_list_get_node__negative_index),*/
    };
    return cmocka_run_group_tests(tests, setup, NULL);
}