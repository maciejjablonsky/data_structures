//
// Created by maciek on 06.10.19.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/dl_list.h"

static void DL_LIST_size__empty_list_size(void **state)
{
    (void) state;

    dl_list_t *list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    assert_non_null(list);
    assert_int_equal(0, DL_LIST_size(list));
}

static void DL_LIST_size__after_adding_three_items(void **state)
{
    (void) state;

    dl_list_t *list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    assert_non_null(list);
    int item = 2;
    DL_LIST_add_item(list, &item);
    DL_LIST_add_item(list, &item);
    DL_LIST_add_item(list, &item);
    assert_int_equal(3, DL_LIST_size(list));
}

static void DL_LIST_size_after_few_deletions(void **state)
{
    (void) state;
    dl_list_t *list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    assert_non_null(list);
    int item = 2;
    DL_LIST_add_item(list, &item);
    DL_LIST_add_item(list, &item);
    DL_LIST_add_item(list, &item);
    DL_LIST_add_item(list, &item);
    assert_int_equal(4, DL_LIST_size(list));
    DL_LIST_delete_item_at(list, 2);
    DL_LIST_delete_item_at(list, 0);
    assert_int_equal(2, DL_LIST_size(list));
}

int main(void)
{
    struct CMUnitTest tests[] = {cmocka_unit_test(DL_LIST_size__empty_list_size),
                                 cmocka_unit_test(DL_LIST_size__after_adding_three_items),
                                 cmocka_unit_test(DL_LIST_size_after_few_deletions),};
    return cmocka_run_group_tests(tests, NULL, NULL);
}