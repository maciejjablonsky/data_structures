//
// Created by maciek on 04.07.19.
//

#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/sl_list.c"


ITEM * increment(ITEM * item)
{
    item->a++;
    item->b++;
    return item;
}

ITEM * swap(ITEM *item)
{
    int temp = item->a;
    item->a = item->b;
    item->b = temp;
    return item;
}


static void test_increment(void **state)
{
    ITEM items[] = {
            {1,1},
            {2,2},
            {3,3}
    };
    (void)state;
    SL_LIST * list = SL_LIST_create_list();
    assert_non_null(list);
    for (size_t i = 0; i < 3; ++i)
    {
        SL_LIST_add_position(list, items + i);
    }
    SL_LIST_apply_foreach(list, increment);
    NODE * node = list->head;
    for (size_t i = 0; i < 3; ++i)
    {
        assert_int_equal(((ITEM)items[i]).a + 1, node->item.a);
        assert_int_equal(((ITEM)items[i]).b + 1, node->item.b);
        node = node->next;
    }
}

int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(test_increment)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}