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

static int teardown(void **state)
{
    DL_LIST_delete(list);
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

static void DL_LIST_delete_item_at__doesnt_brake_forward_movement(void **state)
{
    int *item = DL_LIST_item_at(list, 4);
    assert_int_equal(*item, 4);
    DL_LIST_delete_item_at(list, 4);
    item = DL_LIST_item_at(list, 4);
    assert_int_equal(*item, 5);
    item = DL_LIST_item_at(list, 5);
    assert_int_equal(*item, 6);
}

static void DL_LIST_delete_item_at__doesnt_brake_backward_movement(void **state)
{
    int *item = DL_LIST_item_at(list, 4);
    assert_non_null(item);
    assert_int_equal(*item, 4);
    DL_LIST_delete_item_at(list, 4);
    item = DL_LIST_item_at(list, 3);
    assert_non_null(item);
    assert_int_equal(*item, 3);

    item = DL_LIST_item_at(list, 2);
    assert_non_null(item);
    assert_int_equal(*item, 2);
}

static void DL_LIST_delete_item_at__deletion_of_first_item_doesnt_brake_movement(void **state)
{
    DL_LIST_item_at(list, 0);
    DL_LIST_delete_item_at(list, 0);
    int *item = DL_LIST_item_at(list, 0);
    assert_non_null(item);
    assert_int_equal(*item, 1);
}

static void DL_LIST_delete_item_at__deletion_of_last_item_doesnt_brake_movement(void **state)
{
    DL_LIST_item_at(list, ITEMS_COUNT - 1);
    DL_LIST_delete_item_at(list, ITEMS_COUNT - 1);
    int *item = DL_LIST_item_at(list, ITEMS_COUNT - 2);
    assert_non_null(item);
    assert_int_equal(*item, ITEMS_COUNT - 2);
}

static void DL_LIST_delete_item_at__delete_only_item_moves_to_null(void **state)
{
    dl_list_t *p_list = DL_LIST_create(sizeof(int), DL_COPY_ITEM, NULL);
    int item = 2;
    DL_LIST_add_item(p_list, &item);
    int *p_item = DL_LIST_item_at(p_list, 0);
    assert_non_null(p_item);
    assert_int_equal(*p_item, 2);
    DL_LIST_delete_item_at(p_list, 0);
    p_item = DL_LIST_item_at(p_list, 0);
    assert_null(p_item);
    DL_LIST_delete(p_list);
}


int main(void)
{
    struct CMUnitTest tests[] = {
            cmocka_unit_test_setup_teardown(DL_LIST_delete_item_at__delete_first_item, setup, teardown),
            cmocka_unit_test_setup_teardown(DL_LIST_delete_item_at__delete_last_item, setup, teardown),
            cmocka_unit_test_setup_teardown(DL_LIST_delete_item_at__delete_middle_item, setup, teardown),
            cmocka_unit_test(DL_LIST_delete_item_at__delete_only_item),
            cmocka_unit_test_setup_teardown(DL_LIST_delete_item_at__doesnt_brake_forward_movement, setup, teardown),
            cmocka_unit_test_setup_teardown(DL_LIST_delete_item_at__doesnt_brake_backward_movement, setup, teardown),
            cmocka_unit_test_setup_teardown(DL_LIST_delete_item_at__deletion_of_first_item_doesnt_brake_movement, setup,
                                            teardown),
            cmocka_unit_test_setup_teardown(DL_LIST_delete_item_at__deletion_of_last_item_doesnt_brake_movement, setup,
                                            teardown),
            cmocka_unit_test(DL_LIST_delete_item_at__delete_only_item_moves_to_null),};
    return cmocka_run_group_tests(tests, NULL, NULL);
}
