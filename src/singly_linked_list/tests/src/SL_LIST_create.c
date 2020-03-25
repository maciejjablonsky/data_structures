//
// Created by maciek on 02.07.19.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../../singly_linked_list.c"
#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    int a;
    int b;
} TWO_INTS;

typedef int ONE_INT;

void *my_super_pretty_destructor(void *item)
{
    return NULL;
}

void *__real_malloc(size_t);

void *__wrap_malloc(size_t size)
{
    return mock_ptr_type(void*);
}

static void test_create_list__failure(void **state)
{
    (void) state;
    will_return(__wrap_malloc, NULL);
    sl_list_t *list = SL_LIST_create(sizeof(TWO_INTS), COPY_ITEM, my_super_pretty_destructor);
    assert_null(list);
}

static void test_create_list__success(void **state)
{
    (void)state;
    sl_list_t pattern_list = {NULL, NULL, 0, sizeof(TWO_INTS), COPY_ITEM, my_super_pretty_destructor};
    will_return(__wrap_malloc, __real_malloc(sizeof(sl_list_t)));
    sl_list_t *ptr = SL_LIST_create(sizeof(TWO_INTS), COPY_ITEM, my_super_pretty_destructor);
    assert_non_null(ptr);
    assert_ptr_equal(pattern_list.head, ptr->head);
    assert_ptr_equal(pattern_list.tail, ptr->tail);
    assert_int_equal(pattern_list.size, ptr->size);
    assert_int_equal(pattern_list.copy_info, ptr->copy_info);
    assert_int_equal(sizeof(TWO_INTS), ptr->item_size);
    assert_ptr_equal(my_super_pretty_destructor, ptr->item_destructor);
}


int main(void)
{
    const struct CMUnitTest tests[] = {cmocka_unit_test(test_create_list__failure),
            cmocka_unit_test(test_create_list__success)};

    return cmocka_run_group_tests(tests, NULL, NULL);
}