//
// Created by maciek on 02.07.19.
//

#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/sl_list.c"

typedef int INT_ITEM;

static void empty_list(void **state)
{
    sl_list_t *list = SL_LIST_create(sizeof(INT_ITEM), NULL);
    assert_non_null(list);
    assert_int_equal(SL_LIST_size(list), 0);
}

static void after_adding_few_items(void**state)
{
    (void) state;
    sl_list_t * list = SL_LIST_create(sizeof(int), NULL);
    assert_non_null(list);
    int n = 3;

    for(int i = 0; i < n; ++i)
    {
        SL_LIST_add_item(list, &i, COPY_ITEM);
    }
    assert_int_equal(SL_LIST_size(list), n);
}

static void after_adding_and_deleting(void **state)
{
    (void)state;
    sl_list_t * list = SL_LIST_create(sizeof(int), NULL);
    assert_non_null(list);
    int n = 5;
    int d = 2;
    assert_true(n>=d);
    for (int i = 0; i < n; ++i)
    {
        SL_LIST_add_item(list, &i, COPY_ITEM);
    }
    for (int i = 0; i < d; ++i)
    {
        SL_LIST_delete_item_at(list, 0);
    }
    assert_int_equal(n-d, SL_LIST_size(list));
}


int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(empty_list),
        cmocka_unit_test(after_adding_few_items),
        cmocka_unit_test(after_adding_and_deleting)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}