cmake_minimum_required(VERSION 3.13)

project(sl_list_test C)

set(CMAKE_C_STANDARD 11)

include_directories(/usr/local/include)

find_library(CMOCKA_LIBRARY libcmocka.so.0)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -lcmocka")

set(TESTED_SOURCE_DIR ../src)

# tests list DO NOT DELETE THIS LINE

list(APPEND tests_names "test_SL_LIST_create")
list(APPEND tests_flags "-Wl,--wrap=malloc")
list(APPEND tests_source_files src/SL_LIST_create.c)

list(APPEND tests_names "test_SL_LIST_create_node")
list(APPEND tests_flags "-Wl,--wrap=malloc")
list(APPEND tests_source_files src/SL_LIST_create_node.c)

list(APPEND tests_names "test_SL_LIST_size")
list(APPEND tests_flags " ")
list(APPEND tests_source_files src/SL_LIST_size.c)

list(APPEND tests_names "test_SL_LIST_add_item")
list(APPEND tests_flags "-Wl,--wrap=SL_LIST_create_node")
list(APPEND tests_source_files src/SL_LIST_add_item.c)

list(APPEND tests_names "test_SL_LIST_item_at")
list(APPEND tests_flags " ")
list(APPEND tests_source_files src/SL_LIST_item_at.c)

list(APPEND tests_names "test_SL_LIST_apply_foreach")
list(APPEND tests_flags " ")
list(APPEND tests_source_files src/SL_LIST_apply_foreach.c)

list(APPEND tests_names "test_SL_LIST_delete_item_at")
list(APPEND tests_flags " ")
list(APPEND tests_source_files src/SL_LIST_delete_item_at.c)

list(APPEND tests_names "test_SL_LIST_delete_list")
list(APPEND tests_flags " ")
list(APPEND tests_source_files src/SL_LIST_delete.c)

list(APPEND tests_names "test_sl_list_foreach")
list(APPEND tests_flags " ")
list(APPEND tests_source_files src/sl_list_foreach.c)

list(LENGTH tests_names count)
math(EXPR count "${count} - 1")
foreach (i RANGE ${count})
    list(GET tests_names ${i} test_name)
    list(GET tests_flags ${i} test_flags)
    list(GET tests_source_files ${i} test_source_files)
    add_executable(${test_name} ${test_source_files})
    target_link_libraries(${test_name} ${CMOCKA_LIBRARY})
    if (test_flags STREQUAL " ")
    else ()
        target_link_libraries(${test_name} ${test_flags})
    endif ()
    #add_test(${test_name} ${test_name})
endforeach ()