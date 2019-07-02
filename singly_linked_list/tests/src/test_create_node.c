//
// Created by maciek on 02.07.19.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/sl_list.c"
typedef struct {
    int a;
    char ch;
} ITEM;

void * __real_malloc(size_t);
void * __wrap_malloc(size_t size)
{
    return mock_ptr_type(void*);
}

void __real_free(void * ptr);
void __wrap_free(void * ptr)
{
    function_called();
}

static void success(void ** state)
{
    (void)state;
    NODE * new_node = __real_malloc(sizeof(NODE));
    assert_non_null(new_node);

    ITEM pattern_position = {11, 'j'};
    ITEM * for_test_position = __real_malloc(sizeof(ITEM));
    assert_non_null(for_test_position);
    will_return(__wrap_malloc, new_node);
    will_return(__wrap_malloc, for_test_position);

    NODE * tested_node = SL_LIST_create_node(&pattern_position, sizeof(ITEM));
    assert_non_null(tested_node);
    assert_ptr_not_equal(&pattern_position, tested_node->item);
    assert_int_not_equal(tested_node->size, 0);
    assert_memory_equal(tested_node->item, &pattern_position, sizeof(ITEM));
    assert_null(tested_node->next);
}

static void node_memory_failure(void **state)
{
    (void)state;
    will_return(__wrap_malloc, NULL);
    ITEM pattern_pos = {1, 'a'};
    NODE * tested_node = SL_LIST_create_node(&pattern_pos, sizeof(ITEM));
    assert_null(tested_node);
}

static void position_memory_failure(void **state)
{
    (void)state;
    ITEM pattern_pos = {1, 'a'};
    NODE * tested_node = __real_malloc(sizeof(NODE));
    assert_non_null(tested_node);

    will_return(__wrap_malloc, tested_node);
    will_return(__wrap_malloc, NULL);
    expect_function_call(__wrap_free);
    NODE * expected_node = SL_LIST_create_node(&pattern_pos, sizeof(ITEM));
    assert_null(expected_node);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(success),
            cmocka_unit_test(node_memory_failure),
            cmocka_unit_test(position_memory_failure),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}