//
// Created by maciek on 02.07.19.
//

#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../../src/sl_list.c"

static void empty_list(void **state)
{
    SL_LIST * list = SL_LIST_create_list();
    assert_non_null(list);
    assert_int_equal(SL_LIST_size(list), 0);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(empty_list),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}