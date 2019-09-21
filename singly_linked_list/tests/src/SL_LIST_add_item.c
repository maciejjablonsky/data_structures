//
// Created by maciek on 02.07.19.
//

#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/sl_list.c"


typedef struct
{
    int a;
    int b;
} TWO_INTS;

sl_list_t list = {NULL, NULL, 0, sizeof(TWO_INTS), NULL};

static void add_first_item(void **state)
{
    (void) state;
    TWO_INTS pattern_item = {12, 423};

    sl_list_t *plist = &list;
    bool ret = SL_LIST_add_item(plist, &pattern_item);
    assert_true(ret);
    assert_int_equal(list.size, 1);
    assert_non_null(list.head);
    assert_ptr_not_equal(&pattern_item, list.head->item);
    assert_memory_equal(list.head->item, &pattern_item, sizeof(TWO_INTS));
    assert_null(list.head->next);
    assert_memory_equal(list.head, list.tail, sizeof(node_t));
}

static void add_second_item(void**state)
{
    (void)state;
    TWO_INTS pattern_item = {5, 49};
    bool ret = SL_LIST_add_item(&list, &pattern_item);
    assert_true(ret);
    assert_int_equal(list.size, 2);
    assert_ptr_not_equal(list.head, list.tail);
    assert_ptr_equal(list.head->next, list.tail);
    assert_memory_equal(list.head->next, list.tail, sizeof(node_t));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(add_first_item),
            cmocka_unit_test(add_second_item),
            };
    return cmocka_run_group_tests(tests, NULL, NULL);
}