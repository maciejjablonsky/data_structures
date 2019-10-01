//
// Created by maciek on 01.10.19.
//

#include <stddef.h>
#include <setjmp.h>
#include <stdarg.h>
#include <cmocka.h>
#include "../../src/dl_list.c"

static int setup(void **state)
{

}

static int teardown(void **state)
{

}

void *__real_malloc(size_t size);

void *__wrap_malloc(size_t size)
{
    return mock_ptr_type(void*);
}

typedef void *destructor_t(void *);

static void create_success(void **state)
{
    will_return(__wrap_malloc, __real_malloc(sizeof(dl_list_t)));
    dl_list_t *list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, (destructor_t *) 0x02);
    assert_non_null(list);
    assert_null(list->head);
    assert_null(list->tail);
    assert_int_equal(list->item_size, sizeof(int));
    assert_int_equal(list->size, 0);
    assert_ptr_equal(list->item_destructor, (destructor_t *) 0x02);
    assert_ptr_equal(list->storage_info, DL_COPY_ITEM);
}

static void create_memory_failure(void **state)
{
    will_return(__wrap_malloc, NULL);
    dl_list_t *list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    assert_null(list);
}

int main()
{
    struct CMUnitTest tests[] = {cmocka_unit_test(create_success), cmocka_unit_test(create_memory_failure)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}