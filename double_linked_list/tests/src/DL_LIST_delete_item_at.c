#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <assert.h>
#include <cmocka.h>
#include "../../src/dl_list.c"

dl_list_t *list = NULL;
#define ITEMS_COUNT 10

static int setup(void **state)
{
    list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    assert_non_null(list);
    for (int i = 0; i < ITEMS_COUNT; ++i)
    {
        DL_LIST_add_item(list, &i);
    }
    return 0;
}

static void DL_LIST_delete_item_at__delete_first_item(void **state)
{
    dl_node_t *node_to_delete = dl_list_get_node(list, 0);
    dl_node_t *node_after = node_to_delete->next;
    DL_LIST_delete_item_at(list, 0);
    assert_ptr_equal(list->head, node_after);
    assert_null(node_after->prev);
    assert_int_equal(list->size, ITEMS_COUNT - 1);
    assert_int_equal(*(int *) list->head->item, 1);

    DL_LIST_delete_item_at(list, 0);

}

static void DL_LIST_delete_item_at__delete_last_item(void **state)
{
    dl_node_t *node_to_delete = dl_list_get_node(list, ITEMS_COUNT - 1);
    dl_node_t *node_before = node_to_delete->prev;
    DL_LIST_delete_item_at(list, ITEMS_COUNT - 1);
    assert_int_equal(list->size, ITEMS_COUNT - 1);
    assert_ptr_equal(list->tail, node_before);
    assert_int_equal(*(int *) list->tail->item, ITEMS_COUNT - 2);
    assert_null(node_before->next);

}

static void DL_LIST_delete_item_at__delete_middle_item(void **state)
{
    static_assert(ITEMS_COUNT > 4, "ITEMS_COUNT <= 4");
    dl_node_t *node_to_delete = dl_list_get_node(list, 3);
    dl_node_t *node_before = node_to_delete->prev;
    dl_node_t *node_after = node_to_delete->next;
    DL_LIST_delete_item_at(list, 3);
    assert_int_equal(list->size, ITEMS_COUNT - 1);
    assert_ptr_equal(node_before->next, node_after);
    assert_ptr_equal(node_before, node_after->prev);
}

static void DL_LIST_delete_item_at__delete_only_item(void **state)
{
    dl_list_t *only_one_item_list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    int item = 2;
    DL_LIST_add_item(only_one_item_list, &item);
    DL_LIST_delete_item_at(only_one_item_list, 0);
    assert_null(only_one_item_list->head);
    assert_null(only_one_item_list->tail);
    assert_int_equal(only_one_item_list->size, 0);
}

int main(void)
{
    struct CMUnitTest tests[] = {cmocka_unit_test_setup(DL_LIST_delete_item_at__delete_first_item, setup),
                                 cmocka_unit_test_setup(DL_LIST_delete_item_at__delete_last_item, setup),
                                 cmocka_unit_test_setup(DL_LIST_delete_item_at__delete_middle_item, setup),
                                 cmocka_unit_test_setup(DL_LIST_delete_item_at__delete_only_item, setup),};
    return cmocka_run_group_tests(tests, NULL, NULL);
}
