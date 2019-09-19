//
// Created by maciek on 02.07.19.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/sl_list.c"

typedef struct
{
    int a;
    int b;
} TWO_INTS;

void * __real_malloc(size_t);
void * __wrap_malloc(size_t size)
{
    return mock_ptr_type(void*);
}

static void success(void ** state)
{
    (void)state;
    NODE new_node;

    TWO_INTS pattern_item = {11, 'j'};
    will_return(__wrap_malloc, &new_node); // memory for node
    will_return(__wrap_malloc, __real_malloc(sizeof(TWO_INTS))); // memory for item

    NODE *tested_node = sl_list_create_node(&pattern_item, sizeof(TWO_INTS));
    assert_non_null(tested_node);
    assert_memory_equal(tested_node->item, &pattern_item, sizeof(TWO_INTS));
    assert_ptr_not_equal(&pattern_item, new_node.item);
    assert_null(tested_node->next);
}

static void node_memory_failure(void **state)
{
    (void)state;
    will_return(__wrap_malloc, NULL); // memory for node
    TWO_INTS pattern_pos = {1, 'a'};
    NODE *tested_node = sl_list_create_node(&pattern_pos, sizeof(TWO_INTS));
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