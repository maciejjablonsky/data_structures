//
// Created by maciek on 03.07.19.
//

#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/sl_list.c"

typedef struct
{
    long a;
    unsigned long b;
} ITEM;

SL_LIST list = {NULL, NULL, 0};
ITEM _zero_item = {1, 2};
ITEM _first_item = {3,4};
ITEM _second_item = {5, 6};

static void zero_item(void **state)
{
    (void)state;
    ITEM * item = SL_LIST_item_at(&list, 0);
    assert_memory_equal(&_zero_item, item, sizeof(item));
}

static void first_item(void **state)
{
    (void)state;
    ITEM * item = SL_LIST_item_at(&list, 1);
    assert_memory_equal(&_first_item, item, sizeof(item));
}

static void second_item(void **state)
{
    (void)state;
    ITEM * item = SL_LIST_item_at(&list, 2);
    assert_memory_equal(&_second_item, item, sizeof(item));
}

static void out_of_range_item(void**state)
{
    (void)state;
    ITEM * item = SL_LIST_item_at(&list, 3);
    assert_null(item);
    item = SL_LIST_item_at(&list, 4);
    assert_null(item);
}
int main(void)
{
    SL_LIST_add_position(&list, &_zero_item, sizeof(ITEM));
    SL_LIST_add_position(&list, &_first_item, sizeof(ITEM));
    SL_LIST_add_position(&list, &_second_item, sizeof(ITEM));
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(zero_item),
        cmocka_unit_test(first_item),
        cmocka_unit_test(second_item),
        cmocka_unit_test(out_of_range_item),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}