//
// Created by maciek on 02.07.19.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/sl_list.c"
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
    SL_LIST *list = SL_LIST_create(sizeof(TWO_INTS), my_super_pretty_destructor);
    assert_null(list);
}

static void test_create_list__success(void **state)
{
    (void)state;
    SL_LIST pattern_list = {NULL, NULL, 0, sizeof(TWO_INTS), my_super_pretty_destructor};
    SL_LIST tested_list = {NULL, NULL, 0, 0};
    will_return(__wrap_malloc, &tested_list);
    SL_LIST *ptr = SL_LIST_create(sizeof(TWO_INTS), my_super_pretty_destructor);
    assert_non_null(ptr);
    assert_memory_equal(&pattern_list, &tested_list, sizeof(SL_LIST));
    assert_int_equal(sizeof(TWO_INTS), tested_list.item_size);
    assert_ptr_equal(my_super_pretty_destructor, tested_list.item_destructor);
}


int main(void)
{
    const struct CMUnitTest tests[] = {cmocka_unit_test(test_create_list__failure),
            cmocka_unit_test(test_create_list__success)};

    return cmocka_run_group_tests(tests, NULL, NULL);
}