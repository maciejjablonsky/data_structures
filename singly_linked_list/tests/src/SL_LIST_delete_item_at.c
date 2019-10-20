//
// Created by maciek on 28.07.19.
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

static void delete_second_item(void **state)
{
    sl_list_t *list = SL_LIST_create(sizeof(TWO_INTS), COPY_ITEM, NULL);
    assert_non_null(list);

    TWO_INTS items[] = {{0, 0},
                        {1, 1},
                        {2, 2},
                        {3, 3}};
    size_t size = 4;
    for (size_t i = 0; i < size; ++i)
    {
        SL_LIST_add_item(list, items + i);
    }

    bool ret = SL_LIST_delete_item_at(list, 1);
    assert_true(ret);

    TWO_INTS *second_item = SL_LIST_item_at(list, 1);
    assert_int_equal(second_item->a, 2);
    assert_int_equal(second_item->b, 2);
    assert_int_equal(size-1, list->size);
}

static void delete_last_item(void **state)
{
    sl_list_t *list = SL_LIST_create(sizeof(TWO_INTS), COPY_ITEM, NULL);
    assert_non_null(list);

    TWO_INTS items[] = {{0, 0},
                        {1, 1},
                        {2, 2},
                        {3, 3}};
    size_t size = 4;
    for (size_t i = 0; i < size; ++i)
    {
        SL_LIST_add_item(list, items + i);
    }

    SL_LIST_delete_item_at(list, list->size - 1);
    assert_int_equal(size - 1, list->size);
    TWO_INTS *last_item = SL_LIST_item_at(list, list->size - 1);

    assert_int_equal(last_item->a, 2);
    assert_int_equal(last_item->b, 2);

}

static void delete_first_item(void ** state)
{
    sl_list_t *list = SL_LIST_create(sizeof(TWO_INTS), COPY_ITEM, NULL);
    assert_non_null(list);

    TWO_INTS items[] = {{0, 0},
                        {1, 1},
                        {2, 2},
                        {3, 3}};
    size_t size = 4;
    for (size_t i = 0; i < size; ++i)
    {
        SL_LIST_add_item(list, items + i);
    }

    SL_LIST_delete_item_at(list, 0);
    assert_int_equal(size - 1, list->size);
    TWO_INTS *first_item = SL_LIST_item_at(list, 0);
    assert_int_equal(first_item->a, 1);
    assert_int_equal(first_item->b, 1);


}

static void delete_only_item(void ** state)
{
    sl_list_t *list = SL_LIST_create(sizeof(TWO_INTS), COPY_ITEM, NULL);
    assert_non_null(list);

    TWO_INTS items[] = {{0, 0}};
    size_t size = 1;
    for (size_t i = 0; i < size; ++i)
    {
        SL_LIST_add_item(list, items + i);
    }

    SL_LIST_delete_item_at(list, 0);
    assert_int_equal(size - 1, list->size);
    TWO_INTS *first_item = SL_LIST_item_at(list, 0);
    assert_null(first_item);
}


static void delete_last_item_and_add_one(void **state)
{
    sl_list_t *list = SL_LIST_create(sizeof(size_t), COPY_ITEM, NULL);
    assert_non_null(list);


    for (size_t i = 0; i < 3; ++i)
    {
        SL_LIST_add_item(list, &i);
    }
    SL_LIST_delete_item_at(list, 2);
    size_t item = 4;
    SL_LIST_add_item(list, &item);
    size_t *return_item = SL_LIST_item_at(list, 2);
    assert_int_equal(item, *return_item);


}

int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(delete_second_item),
            cmocka_unit_test(delete_last_item),
            cmocka_unit_test(delete_first_item),
            cmocka_unit_test(delete_only_item), cmocka_unit_test(delete_last_item_and_add_one)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}