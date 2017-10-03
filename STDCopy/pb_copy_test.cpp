#include "gtest/gtest.h"
#include "pb_copy.h"

TEST(SuiteName, 10) {
    int a[] = {1, 2, 3, 4};
    int b[] = {0, 0, 0, 0};

    pb_copy(a, a + 4, b);
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(b[i], a[i]);
    }
}

TEST(SuiteName, 11) {
    char a[] = "abcd";
    char b[] = "aaaa";

    pb_copy(a, a + 5, b);
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(b[i], a[i]);
    }
}

TEST(SuiteName, 20) {
    std::vector<int> src = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> dst = {0, 0, 0, 0, 0, 0, 0};

    pb_copy(src.begin(), src.end(), dst.begin());
    for (int i = 0; i < src.size(); ++i) {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(SuiteName, 21) {
    std::vector<std::string> src = {"aa", "bb", "cc"};
    std::vector<std::string> dst = {"00", "00", "00"};

    pb_copy(src.begin(), src.end(), dst.begin());
    for (int i = 0; i < src.size(); ++i) {
        ASSERT_EQ(dst[i], src[i]);
    }
}