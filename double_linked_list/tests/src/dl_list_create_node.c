//
// Created by maciek on 01.10.19.
//

#include <setjmp.h>
#include <stddef.h>
#include <stdarg.h>
#include <cmocka.h>
#include "../../src/dl_list.c"

void *__real_malloc(size_t size);

void *__wrap_malloc(size_t size)
{
    return mock_ptr_type(void*);
}

void __real_exit(int status);

void __wrap_exit(int status)
{
    function_called();
}

static void dl_list_create_node__success(void **state)
{

    (void) state;
    int item = 2;
    will_return(__wrap_malloc, __real_malloc(sizeof(dl_node_t)));
    will_return(__wrap_malloc, __real_malloc(sizeof(item)));
    dl_node_t *empty_node = dl_list_create_node(&item, sizeof(int), DL_COPY_ITEM);
    assert_non_null(empty_node);
    assert_memory_equal(empty_node->item, &item, sizeof(item));
    assert_ptr_equal(empty_node->next, NULL);
    assert_ptr_equal(empty_node->prev, NULL);
}

static void dl_list_create_node__memory_failure(void **state)
{
    (void) state;
    int item = 2;
    will_return(__wrap_malloc, NULL);
    dl_node_t *new_node = dl_list_create_node(&item, sizeof(item), DL_COPY_ITEM);
    assert_null(new_node);

}

static void dl_list_create_node__item_memory_failure(void **state)
{
    (void) state;
    int item = 2;
    will_return(__wrap_malloc, __real_malloc(sizeof(dl_node_t)));
    will_return(__wrap_malloc, NULL);
    expect_function_call(__wrap_exit);
    dl_node_t *new_node = dl_list_create_node(&item, sizeof(item), DL_COPY_ITEM);
}

int main()
{
    struct CMUnitTest tests[] = {cmocka_unit_test(dl_list_create_node__success),
                                 cmocka_unit_test(dl_list_create_node__memory_failure),
                                 cmocka_unit_test(dl_list_create_node__item_memory_failure)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}