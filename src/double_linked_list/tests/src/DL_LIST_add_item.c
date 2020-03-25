//
// Created by maciek on 01.10.19.
//

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
#include "../../src/dl_list.h"

void *__real_malloc(size_t size);

void *__wrap_malloc(size_t size)
{
    return mock_ptr_type(void*);
}

static void DL_LIST_add_item__copy_success(void **state)
{
    (void) state;

    int item = 2;
    will_return(__wrap_malloc, __real_malloc(sizeof(dl_list_t)));
    will_return(__wrap_malloc, __real_malloc(sizeof(dl_node_t)));
    will_return(__wrap_malloc, __real_malloc(sizeof item));
    dl_list_t *list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);


    bool ret = DL_LIST_add_item(list, &item);
    assert_true(ret);
    assert_ptr_equal(list->head, list->tail);
    assert_ptr_equal(list->head->item, list->tail->item);
    assert_ptr_not_equal(&item, list->head->item);
    assert_memory_equal(&item, list->head->item, sizeof(int));
}

static void DL_LIST_add_item__copy_pointer_success(void **state)
{
    (void) state;

    int item = 3;
    will_return(__wrap_malloc, __real_malloc(sizeof(dl_list_t)));
    will_return(__wrap_malloc, __real_malloc(sizeof(dl_node_t)));
    dl_list_t *list = DL_LIST_create(sizeof(int), DL_COPY_POINTER, NULL);

    bool ret = DL_LIST_add_item(list, &item);
    assert_true(ret);
    assert_ptr_equal(list->head, list->tail);
    assert_ptr_equal(list->head->item, list->tail->item);
    assert_ptr_equal(list->head->item, &item);
    assert_memory_equal(&item, list->head->item, sizeof(int));
}

static void DL_LIST_add_item__node_memory_failure(void **state)
{
    (void) state;
    int item = 2;
    will_return(__wrap_malloc, __real_malloc(sizeof(dl_list_t)));
    will_return(__wrap_malloc, NULL); // failure of allocation memory for node

    dl_list_t *list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);

    bool ret = DL_LIST_add_item(list, &item);
    assert_false(ret);

}

int main()
{
    struct CMUnitTest tests[] = {cmocka_unit_test(DL_LIST_add_item__copy_success),
                                 cmocka_unit_test(DL_LIST_add_item__copy_pointer_success),
                                 cmocka_unit_test(DL_LIST_add_item__node_memory_failure)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}