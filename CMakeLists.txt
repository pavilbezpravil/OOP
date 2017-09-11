cmake_minimum_required(VERSION 3.7)
project(OOP)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(extern/googletest)
include_directories(extern/googletest/googletest)

set(SOURCE_FILES STDCopy/pb_copy.cpp RadixSort/radix_sort.cpp RadixSort/test_radix_sort.cpp RadixSort/radix_sort.h STDCopy/pb_copy.h STDCopy/pb_copy_test.cpp)
add_executable(OOP ${SOURCE_FILES})

target_link_libraries(OOP gtest gtest_main)