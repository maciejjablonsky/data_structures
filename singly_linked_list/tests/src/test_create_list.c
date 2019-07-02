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


void *__real_malloc(size_t);

void *__wrap_malloc(size_t size)
{
    return mock_ptr_type(void*);
}

static void test_create_list__failure(void **state)
{
    (void) state;
    will_return(__wrap_malloc, NULL);
    SL_LIST *list = SL_LIST_create_list();
    assert_null(list);
}

static void test_create_list__success(void **state)
{
    (void)state;
    SL_LIST pattern_list = {NULL, NULL, 0};
    SL_LIST tested_list = {NULL, NULL, 0};
    will_return(__wrap_malloc, &tested_list);
    SL_LIST * ptr = SL_LIST_create_list();
    assert_non_null(ptr);
    assert_memory_equal(&pattern_list, &tested_list, sizeof(SL_LIST));
}


int main(void)
{
    const struct CMUnitTest tests[] = {cmocka_unit_test(test_create_list__failure),
            cmocka_unit_test(test_create_list__success)};

    return cmocka_run_group_tests(tests, NULL, NULL);
}