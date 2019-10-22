#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
#include "../../src/dl_list.h"

#define ITEMS_COUNT 10
dl_list_t *list = NULL;

static int setup(void **state)
{
    list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    for (int i = 0; i < ITEMS_COUNT; ++i)
    {
        DL_LIST_add_item(list, &i);
    }
    return 0;
}

static int teardown(void **state)
{
    DL_LIST_delete(list);
    return 0;
}

static void dl_list_foreach__goes_through_whole_list(void **state)
{
    int i = 0;
    int *item = NULL;
    dl_list_foreach(list, item)
    {
        assert_non_null(item);
        assert_int_equal(*item, i);
        i++;
    }
    assert_int_equal(i, ITEMS_COUNT);
}

static void dl_list_foreach__doesnt_go_through_empty_list(void **state)
{
    dl_list_t *priv_list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    int *item = NULL;
    bool loop_run = false;
    dl_list_foreach(priv_list, item)
    {
        loop_run = true;
    }
    assert_false(loop_run);
    DL_LIST_delete(priv_list);
}

int main(void)
{
    struct CMUnitTest tests[] = {
            cmocka_unit_test_setup_teardown(dl_list_foreach__goes_through_whole_list, setup, teardown),
            cmocka_unit_test(dl_list_foreach__doesnt_go_through_empty_list)};
    return cmocka_run_group_tests(tests, NULL, NULL);
}