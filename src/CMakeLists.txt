cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCE_FILES *.c)
file(GLOB HEADER_FILES include/*.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
add_library(${PROJECT_NAME}_static STATIC ${SOURCE_FILES})
include_directories(./include)

target_link_libraries(${PROJECT_NAME})


install(TARGETS ${PROJECT_NAME} ${PROJECT_NAME}_static
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME})