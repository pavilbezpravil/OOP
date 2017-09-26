#include <gtest/gtest.h>
#include "UniquePTR.h"

TEST(SuiteName, baseOperation) {
    int curVal = 12;
    UniquePTR<int> ptr(new int(curVal));
    ASSERT_EQ(*ptr, curVal);

    curVal = 17; *ptr = curVal;
    ASSERT_EQ(*ptr, curVal);

    curVal = 2; ptr.reset(new int(curVal));
    ASSERT_EQ(*ptr, curVal);

    ++curVal; ++*ptr;
    ASSERT_EQ(*ptr, curVal);
}

TEST(SuiteName, swap) {
    int Val1 = 12; UniquePTR<int> ptr1(new int(Val1));
    int Val2 = 15; UniquePTR<int> ptr2(new int(Val2));

    ptr1.swap(ptr2);
    ASSERT_EQ(*ptr1, Val2);
    ASSERT_EQ(*ptr2, Val1);
}


TEST(SuiteName, errorTest) {
    // TODO:
    UniquePTR<int> ptr{};
//    *ptr = 12;
}

TEST(SuiteName, eqTest) {
    UniquePTR<int> ptr1{new int(13)};
    UniquePTR<int> ptr2{new int(15)};

    int *ptr2_backup = ptr2.get();
    ptr1 = std::move(ptr2);
    ASSERT_EQ(ptr2.get(), nullptr);
    ASSERT_EQ(ptr1.get(), ptr2_backup);

    int *tmp = new int(123);
    ptr2 = tmp;
    ASSERT_EQ(*ptr2, 123);

}


TEST(SuiteName, arrayDeleter) {

}
