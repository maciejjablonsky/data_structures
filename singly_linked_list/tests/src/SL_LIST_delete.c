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

static void delete_three_items_list(void **state)
{
    sl_list_t *list = SL_LIST_create(sizeof(TWO_INTS), NULL);
    assert_non_null(list);

    TWO_INTS items[] = {{0, 0},
                        {1, 1},
                        {2, 2},};
    size_t size = 3;
    for (size_t i = 0; i < size; ++i)
    {
        SL_LIST_add_item(list, items + i);
    }

    list = SL_LIST_delete_list(list);
    assert_null(list);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(delete_three_items_list),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}