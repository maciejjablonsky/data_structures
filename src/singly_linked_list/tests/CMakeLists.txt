cmake_minimum_required(VERSION 3.13)

project(sl_list_test C)

set(CMAKE_C_STANDARD 11)

include_directories(/usr/local/include)

find_library(CMOCKA_LIB libcmocka.so.0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -lcmocka")

set(TESTED_SOURCE_DIR ../src)

# tests list DO NOT DELETE THIS LINE

# SL_LIST_create()
add_executable(test_SL_LIST_create src/SL_LIST_create.c)
target_link_libraries(test_SL_LIST_create ${CMOCKA_LIB} -Wl,--wrap=malloc)

# SL_LIST_create_node()
add_executable(test_SL_LIST_create_node src/SL_LIST_create_node)
target_link_libraries(test_SL_LIST_create_node ${CMOCKA_LIB} -Wl,--wrap=malloc)

# SL_LIST_size()
add_executable(test_SL_LIST_size src/SL_LIST_size.c)
target_link_libraries(test_SL_LIST_size ${CMOCKA_LIB})

# SL_LIST_add_item()
add_executable(test_SL_LIST_add_item src/SL_LIST_add_item.c)
target_link_libraries(test_SL_LIST_add_item ${CMOCKA_LIB} -Wl,--wrap=SL_LIST_create_node)

# SL_LIST_item_at()
add_executable(test_SL_LIST_item_at src/SL_LIST_item_at.c)
target_link_libraries(test_SL_LIST_item_at ${CMOCKA_LIB})

# SL_LIST_apply_foreach()
add_executable(test_SL_LIST_apply_foreach src/SL_LIST_apply_foreach.c)
target_link_libraries(test_SL_LIST_apply_foreach ${CMOCKA_LIB})

# SL_LIST_delete_item_at()
add_executable(test_SL_LIST_delete_item_at src/SL_LIST_delete_item_at.c)
target_link_libraries(test_SL_LIST_delete_item_at ${CMOCKA_LIB})

# SL_LIST_delete_list()
add_executable(test_SL_LIST_delete_list src/SL_LIST_delete.c)
target_link_libraries(test_SL_LIST_delete_list ${CMOCKA_LIB})

# sl_list_foreach
add_executable(test_sl_list_foreach src/sl_list_foreach.c)
target_link_libraries(test_sl_list_foreach ${CMOCKA_LIB})
