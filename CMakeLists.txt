cmake_minimum_required(VERSION 3.13)
project(collections_c VERSION 0.1)
enable_language(C)

set(C_FLAGS "-Wall -Werror --std=c99")
set(CMAKE_C_FLAGS "${C_FLAGS}")
enable_testing()

add_subdirectory(src)
#add_subdirectory(test)
#add_subdirectory(examples)