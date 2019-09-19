cmake_minimum_required(VERSION 3.10)
project(sl_list)

set(SOURCE_FILES example.c src/sl_list.c)



add_executable(sl_list ${SOURCE_FILES})

add_subdirectory(tests)
