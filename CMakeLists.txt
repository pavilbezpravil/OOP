cmake_minimum_required(VERSION 3.7)
project(OOP)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(extern/googletest)
include_directories(extern/googletest/googletest)

set(SOURCE_FILES main.cpp radix_sort.cpp test_radix_sort.cpp radix_sort.h)
add_executable(OOP ${SOURCE_FILES})

target_link_libraries(OOP gtest gtest_main)