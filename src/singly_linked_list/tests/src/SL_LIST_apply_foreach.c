//
// Created by maciek on 04.07.19.
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


void *increment(void *item)
{
    TWO_INTS *ti_item = (TWO_INTS *) item;
    ((TWO_INTS *) item)->a++;
    ((TWO_INTS *) item)->b++;

    return ti_item;
}

/*
void *swap(void *item)
{
    int temp = ((TWO_INTS *) item)->a;
    ((TWO_INTS *) item)->a = ((TWO_INTS *) item)->b;
    ((TWO_INTS *) item)->b = temp;
    return item;
}
*/


static void test_increment(void **state)
{
    (void) state;
    sl_list_t *list = SL_LIST_create(sizeof(TWO_INTS), COPY_ITEM, NULL);
    assert_non_null(list);

    TWO_INTS items[] = {{1, 1},
                        {2, 2},
                        {3, 3}};
    for (size_t i = 0; i < 3; ++i)
    {
        SL_LIST_add_item(list, items + i);
    }

    SL_LIST_apply_foreach(list, increment);
    sl_node_t *node = list->head;
    for (size_t i = 0; i < 3; ++i)
    {
        assert_int_equal(((TWO_INTS) items[i]).a + 1, ((TWO_INTS *) node->item)->a);
        assert_int_equal(((TWO_INTS) items[i]).b + 1, ((TWO_INTS *) node->item)->b);
        node = node->next;
    }
}

void *increment_int(void *item)
{
    int *int_item = item;
    *int_item += 1;
    return item;
}

static void test_increment_int(void **state)
{
    (void) state;
    sl_list_t *list = SL_LIST_create(sizeof(int), COPY_ITEM, NULL);
    assert_non_null(list);

    int ints[] = {1, 2, 3, 4};
    for (size_t i = 0; i < 4; ++i)
    {
        SL_LIST_add_item(list, ints + i);
    }
    SL_LIST_apply_foreach(list, increment_int);
    sl_node_t *node = list->head;
    for (size_t i = 0; i < 3; ++i)
    {
        assert_int_equal(ints[i] + 1, *(int *) node->item);
        node = node->next;
    }
}

int main(void)
{
    const struct CMUnitTest tests[] = {cmocka_unit_test(test_increment), cmocka_unit_test(test_increment_int)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}