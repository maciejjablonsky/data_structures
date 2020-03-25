//
// Created by maciek on 03.07.19.
//

#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../../singly_linked_list.c"


typedef struct
{
    int a;
    int b;
} TWO_INTS;

sl_list_t list = {NULL, NULL, 0, sizeof(TWO_INTS), COPY_ITEM, NULL};
TWO_INTS _zero_item = {1, 2};
TWO_INTS _first_item = {3, 4};
TWO_INTS _second_item = {5, 6};

static void zero_item(void **state)
{
    (void)state;
    TWO_INTS *item = SL_LIST_item_at(&list, 0);
    assert_memory_equal(&_zero_item, item, list.item_size);
}

static void first_item(void **state)
{
    (void)state;
    void *item = SL_LIST_item_at(&list, 1);
    assert_memory_equal(&_first_item, item, list.item_size);
}

static void second_item(void **state)
{
    (void)state;
    void *item = SL_LIST_item_at(&list, 2);
    TWO_INTS item_from_list = *(TWO_INTS *) item;
    assert_memory_equal(&_second_item, &item_from_list, list.item_size);
}

static void out_of_range_item(void**state)
{
    (void)state;
    void *item = SL_LIST_item_at(&list, 3);
    assert_null(item);
    item = SL_LIST_item_at(&list, 4 );
    assert_null(item);
}
int main(void)
{
    SL_LIST_add_item(&list, &_zero_item);
    SL_LIST_add_item(&list, &_first_item);
    SL_LIST_add_item(&list, &_second_item);
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(zero_item),
        cmocka_unit_test(first_item),
        cmocka_unit_test(second_item),
        cmocka_unit_test(out_of_range_item),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}