#include "gtest/gtest.h"
#include "pb_sort.h"
#include <functional>


TEST(SuiteName, 1) {
    std::vector<int> v =        {7, 3, 5, 2, 6, 1, 4};
    std::vector<int> right =    {1, 2, 3, 4, 5, 6, 7};

    pb_sort(v.begin(), v.end(), std::less<int>() );
    for (size_t i = 0; i < right.size(); ++i) {
        ASSERT_EQ(right[i], v[i]);
    }
}

TEST(SuiteName, 2) {
    std::vector<long> v =       {7, 3, 5, 2, 6, 1, 4};
    std::vector<long> right =   {1, 2, 3, 4, 5, 6, 7};

    pb_sort(v.begin(), v.end(), std::less<int>() );
    for (size_t i = 0; i < right.size(); ++i) {
        ASSERT_EQ(right[i], v[i]);
    }
}

TEST(SuiteName, 3) {
    std::vector<char> v =       {'s', 'c', 'd', 'a', 'b'};
    std::vector<char> right =   {'a', 'b', 'c', 'd', 's'};

    pb_sort(v.begin(), v.end(), std::less<char>() );
    for (size_t i = 0; i < right.size(); ++i) {
        ASSERT_EQ(right[i], v[i]);
    }
}

TEST(SuiteName, 4) {
    int v[] =       {7, 3, 5, 2, 6, 1, 4};
    int right[] =   {1, 2, 3, 4, 5, 6, 7};

    pb_sort(v, v + 7, std::less<int>() );
    for (size_t i = 0; i < 7; ++i) {
        ASSERT_EQ(right[i], v[i]);
    }
}