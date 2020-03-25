cmake_minimum_required(VERSION 3.13)
project(sl_list C)

set(CMAKE_C_STANDARD 99)

add_executable(sl_list_example sl_list_example.c src/sl_list.c)

add_subdirectory(tests)