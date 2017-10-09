cmake_minimum_required(VERSION 3.7)
project(OOP)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(extern/googletest)
include_directories(extern/googletest/googletest extern/googletest/googlemock)

# ++++++++ UTILS +++++++++
set(UTILS_FILES  utils/log.h)

set(RadixSort_SRC RadixSort/pb_sort.h RadixSort/test_radix_sort.cpp)
add_executable(RadixSort ${RadixSort_SRC})
target_link_libraries(RadixSort gtest gtest_main)

set(STDCopy_SRC STDCopy/pb_copy.h STDCopy/pb_copy_test.cpp)
add_executable(STDCopy ${STDCopy_SRC})
target_link_libraries(STDCopy gtest gtest_main)

set(Unique_ptr_SRC UniquePtr/UniquePTR.h UniquePtr/test.cpp)
add_executable(Unique_ptr ${Unique_ptr_SRC})
target_link_libraries(Unique_ptr gtest gtest_main gmock)

set(SkipList_SRC SkipList/SkipList.h SkipList/test.cpp SkipList/SkipListNode.h SkipList/SkipListIterator.h)
add_executable(SkipList ${SkipList_SRC})
target_link_libraries(SkipList gtest gtest_main)

set(Trie_SRC Trie/Trie.h Trie/TrieIterator.h Trie/SubTrie.h Trie/TrieNode.h Trie/test.cpp)
add_executable(Trie ${Trie_SRC})
target_link_libraries(Trie gtest gtest_main)

set(ANNE_HELP_SRC AnneHelp/MySharedPtr.h AnneHelp/main.cpp)
add_executable(ANNE_HELP ${ANNE_HELP_SRC})
target_link_libraries(ANNE_HELP gtest gtest_main)
