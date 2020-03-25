//
// Created by maciek on 30.09.19.
//

#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../../singly_linked_list.c"

static void success_when_proper_parameters(void **state)
{
    (void) state;

    sl_list_t *list = SL_LIST_create(sizeof(size_t), COPY_ITEM, NULL);
    assert_non_null(list);
    for (size_t i = 0; i < 10; ++i)
    {
        SL_LIST_add_item(list, &i);
    }

    size_t *item;
    size_t i = 0;

    sl_list_foreach(list, item)
    {
        assert_int_equal(i, *item);
        i++;
    }
}

static void does_it_finish_at_last_item(void **state)
{
    (void) state;
    sl_list_t *list = SL_LIST_create(sizeof(size_t), COPY_ITEM, NULL);
    size_t k = 2;
    SL_LIST_add_item(list, &k);
    k = 13;
    SL_LIST_add_item(list, &k);
    k = 27;
    SL_LIST_add_item(list, &k);

    size_t * item;
    sl_list_foreach(list, item)
    {
        if (*item == k)
        {
            break;
        }
        SL_LIST_delete_item_at(list, 0);
    }
    assert_true(SL_LIST_size(list) == 1);
}

static void doesnt_run_when_empty(void **state)
{
    (void) state;
    sl_list_t *list = SL_LIST_create(sizeof(size_t), COPY_ITEM, NULL);
    assert_non_null(list);
    bool loop_run = false;

    size_t *item;
    sl_list_foreach(list, item)
    {
        loop_run = true;
    }
    assert_false(loop_run);
}

int main()
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(success_when_proper_parameters),
            cmocka_unit_test(does_it_finish_at_last_item),
            cmocka_unit_test(doesnt_run_when_empty)
            };
    return cmocka_run_group_tests(tests, NULL, NULL);
}