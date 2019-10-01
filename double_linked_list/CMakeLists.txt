cmake_minimum_required(VERSION 3.13)
project(dl_list C)

set(CMAKE_C_STANDARD 99)

add_executable(dl_list_example dl_list_example.c src/dl_list.c)

add_subdirectory(tests)