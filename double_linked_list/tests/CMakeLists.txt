cmake_minimum_required(VERSION 3.13)

project(dl_list_test C)

set(CMAKE_C_STANDARD 11)

include_directories(/usr/local/include)

find_library(CMOCKA_LIB libcmocka.so.0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -lcmocka")

set(TESTED_SOURCE_DIR ../src)

# tests list DO NOT DELETE THIS LINE

# DL_LIST_create()
set(test test_DL_LIST_create)
add_executable(${test} src/DL_LIST_create.c ../src/dl_list.c)
target_link_libraries(${test} ${CMOCKA_LIB} -Wl,--wrap=malloc)

# dl_list_create_node()
add_executable(test_dl_list_create_node src/dl_list_create_node.c)
target_link_libraries(test_dl_list_create_node ${CMOCKA_LIB} -Wl,--wrap=malloc -Wl,--wrap=exit)

# DL_LIST_add_item()
add_executable(test_DL_LIST_add_item src/DL_LIST_add_item.c ../src/dl_list.c)
target_link_libraries(test_DL_LIST_add_item ${CMOCKA_LIB} -Wl,--wrap=malloc)

# DL_LIST_size()
add_executable(test_DL_LIST_size src/DL_LIST_size.c ../src/dl_list.c)
target_link_libraries(test_DL_LIST_size ${CMOCKA_LIB})

# dl_list_get_node()
add_executable(test_dl_get_node src/dl_list_get_node.c)
target_link_libraries(test_dl_get_node ${CMOCKA_LIB})

# DL_LIST_item_at()
add_executable(test_DL_LIST_item_at src/DL_LIST_item_at.c ../src/dl_list.c)
target_link_libraries(test_DL_LIST_item_at ${CMOCKA_LIB})

# dl_list_delete_node()
add_executable(test_dl_list_delete_node src/dl_list_delete_node.c)
target_link_libraries(test_dl_list_delete_node ${CMOCKA_LIB})

# DL_LIST_delete_item_at()
add_executable(test_DL_LIST_delete_item_at src/DL_LIST_delete_item_at.c)
target_link_libraries(test_DL_LIST_delete_item_at ${CMOCKA_LIB})