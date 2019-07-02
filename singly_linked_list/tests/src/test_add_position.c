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
    long a;
    unsigned long b;
} ITEM;

SL_LIST list = {NULL, NULL, 0};

static void add_first_item(void **state)
{
    (void) state;
    ITEM pattern_item = {12, 423};

    SL_LIST *plist = &list;
    bool ret = SL_LIST_add_position(plist, &pattern_item, sizeof(ITEM));
    assert_true(ret);
    assert_int_equal(plist->size, 1);
    assert_non_null(plist->head);
    assert_non_null(plist->head->item);
    assert_memory_equal(plist->head->item, &pattern_item, sizeof(ITEM));
    assert_null(plist->head->next);
    assert_memory_equal(plist->head, plist->tail, sizeof(NODE));
}

static void add_second_item(void**state)
{
    (void)state;
    ITEM pattern_item = {5, 49};
    bool ret = SL_LIST_add_position(&list, &pattern_item, sizeof(ITEM));
    assert_true(ret);
    assert_int_equal(list.size, 2);
    assert_ptr_not_equal(list.head, list.tail);
    assert_ptr_equal(list.head->next, list.tail);
    assert_memory_equal(list.head->next, list.tail, sizeof(NODE));
}

int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(add_first_item),
            cmocka_unit_test(add_second_item),
            };
    return cmocka_run_group_tests(tests, NULL, NULL);
}