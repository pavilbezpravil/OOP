#include "pb_sort.h"
#include "gtest/gtest.h"

template <typename Digit>
bool digit_cmp (Digit i,Digit j) { return i<j; }

bool char_cmp(char a, char b) { return int(a) < int(b); }

// TODO: why do not work?
//template <class T, class Compare>
//bool test_pb_sort(typename std::vector<T> &v, Compare compare) {
//    std::vector<T> right {v};
//
//    std::sort(right.begin(), right.end(), compare);
//    radix_sort(v.begin(), v.end(), compare);
//    for (size_t i = 0; i < right.size(); ++i) {
//        ASSERT_EQ(right[i], v[i]);
//    }
//}

TEST(SuiteName, 1) {
    std::vector<int> v =        {7, 3, 5, 2, 6, 1, 4};
    std::vector<int> right =    {1, 2, 3, 4, 5, 6, 7};

    pb_sort(v.begin(), v.end(), digit_cmp<int>);
    for (size_t i = 0; i < right.size(); ++i) {
        ASSERT_EQ(right[i], v[i]);
    }
//    test_pb_sort(v, digit_cmp<int>);
}

TEST(SuiteName, 2) {
    std::vector<long> v =       {7, 3, 5, 2, 6, 1, 4};
    std::vector<long> right =   {1, 2, 3, 4, 5, 6, 7};

    pb_sort(v.begin(), v.end(), digit_cmp<int>);
    for (size_t i = 0; i < right.size(); ++i) {
        ASSERT_EQ(right[i], v[i]);
    }
}

TEST(SuiteName, 3) {
    std::vector<char> v =       {'s', 'c', 'd', 'a', 'b'};
    std::vector<char> right =   {'a', 'b', 'c', 'd', 's'};

    pb_sort(v.begin(), v.end(), char_cmp);
    for (size_t i = 0; i < right.size(); ++i) {
        ASSERT_EQ(right[i], v[i]);
    }
}

TEST(SuiteName, 4) {
    int v[] =       {7, 3, 5, 2, 6, 1, 4};
    int right[] =   {1, 2, 3, 4, 5, 6, 7};

    pb_sort(v, v + 7, digit_cmp<int>);
    for (size_t i = 0; i < 7; ++i) {
        ASSERT_EQ(right[i], v[i]);
    }
}