//
// Created by maciek on 20.10.19.
//

#include <setjmp.h>
#include <stddef.h>
#include <stdarg.h>
#include <cmocka.h>
#include "../../src/dl_list.h"
#include <assert.h>

dl_list_t *list = NULL;
#define ITEMS_COUNT 5

static int setup(void **state)
{
    list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
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

static void DL_LIST_item_at__get_1st_item(void **state)
{
    (void) state;

    int *item = DL_LIST_item_at(list, 0);
    assert_non_null(item);
    assert_int_equal(*item, 0);
}

static void DL_LIST_item_at__get_3rd_item(void **state)
{
    (void) state;
    static_assert(ITEMS_COUNT >= 2, "");
    int *item = DL_LIST_item_at(list, 2);
    assert_non_null(item);
    assert_int_equal(*item, 2);
}

static void DL_LIST_item_at__get_last_item(void **state)
{
    (void) state;
    int *item = DL_LIST_item_at(list, ITEMS_COUNT - 1);
    assert_non_null(item);
    assert_int_equal(*item, ITEMS_COUNT - 1);
}

static void DL_LIST_item_at__negative_index(void **state)
{
    (void) state;
    int *item = DL_LIST_item_at(list, -2);
    assert_null(item);
}

static void DL_LIST_item_at__too_big_index(void **state)
{
    (void) state;
    int *item = DL_LIST_item_at(list, ITEMS_COUNT);
    assert_null(item);
}


int main(void)
{
    struct CMUnitTest tests[] = {cmocka_unit_test_setup_teardown(DL_LIST_item_at__get_1st_item, setup, teardown),
                                 cmocka_unit_test_setup_teardown(DL_LIST_item_at__get_3rd_item, setup, teardown),
                                 cmocka_unit_test_setup_teardown(DL_LIST_item_at__get_last_item, setup, teardown),
                                 cmocka_unit_test_setup_teardown(DL_LIST_item_at__negative_index, setup, teardown),
                                 cmocka_unit_test_setup_teardown(DL_LIST_item_at__too_big_index, setup, teardown),

    };
    return cmocka_run_group_tests(tests, setup, NULL);
}