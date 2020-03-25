//
// Created by maciek on 02.07.19.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../../singly_linked_list.c"

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

static void item_copy_success(void **state)
{
    (void)state;
    sl_node_t new_node;

    TWO_INTS pattern_item = {11, 'j'};
    will_return(__wrap_malloc, &new_node); // memory for sl_node
    will_return(__wrap_malloc, __real_malloc(sizeof(TWO_INTS))); // memory for item

    sl_node_t *tested_node = sl_list_create_node(&pattern_item, sizeof(TWO_INTS), COPY_ITEM);
    assert_non_null(tested_node);
    assert_memory_equal(tested_node->item, &pattern_item, sizeof(TWO_INTS));
    assert_ptr_not_equal(&pattern_item, new_node.item);
    assert_null(tested_node->next);
}

static void pointer_copy_success(void**state)
{
    (void)state;
    sl_node_t new_node;

    TWO_INTS * test_item = __real_malloc(sizeof(TWO_INTS));
    assert_non_null(test_item);
    test_item->a = 11;
    test_item->b = 'j';
    will_return(__wrap_malloc, &new_node);
    sl_node_t * tested_node = sl_list_create_node(test_item, sizeof(TWO_INTS), COPY_POINTER);
    assert_non_null(tested_node);
    assert_ptr_equal(test_item, tested_node->item);
    assert_null(tested_node->next);
}

static void node_memory_failure(void **state)
{
    (void)state;
    will_return(__wrap_malloc, NULL); // memory for sl_node
    TWO_INTS pattern_pos = {1, 'a'};
    sl_node_t *tested_node = sl_list_create_node(&pattern_pos, sizeof(TWO_INTS), COPY_ITEM);
    assert_null(tested_node);
}


int main(void)
{
    const struct CMUnitTest tests[] = {
            cmocka_unit_test(item_copy_success),
            cmocka_unit_test(node_memory_failure),
            cmocka_unit_test(pointer_copy_success)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}