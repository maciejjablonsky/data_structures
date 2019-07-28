//
// Created by maciek on 02.07.19.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/sl_list.c"

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
    NODE new_node;

    ITEM pattern_item = {11, 'j'};
    will_return(__wrap_malloc, &new_node);

    NODE * tested_node = sl_list_create_node(&pattern_item);
    assert_non_null(tested_node);
    assert_memory_equal(&tested_node->item, &pattern_item, sizeof(ITEM));
    assert_null(tested_node->next);
}

static void node_memory_failure(void **state)
{
    (void)state;
    will_return(__wrap_malloc, NULL);
    ITEM pattern_pos = {1, 'a'};
    NODE * tested_node = sl_list_create_node(&pattern_pos);
    assert_null(tested_node);
}


int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(success),
            cmocka_unit_test(node_memory_failure),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}