cmake_minimum_required(VERSION 3.13)
project(data_structures C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c check_execution_time.c singly_linked_list/src/sl_list.c double_linked_list/src/dl_list.c)

add_executable(main ${SOURCE_FILES})
add_subdirectory(singly_linked_list)
add_subdirectory(double_linked_list)