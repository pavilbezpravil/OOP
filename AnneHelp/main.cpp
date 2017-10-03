#include "MySharedPtr.h"
#include <gtest/gtest.h>


TEST(SuiteName, TestName) {
    MySharedPtr<int> s1(new int(5));
    MySharedPtr<int> s2(s1);
    ASSERT_EQ(*s1, *s2);
    ASSERT_EQ(s1.get_linksCounter(), s2.get_linksCounter());
    ASSERT_EQ(*s1.get_linksCounter(), 2);

    s2.reset(new int(10));
    ASSERT_NE(s1.get_linksCounter(), s2.get_linksCounter());
    ASSERT_EQ(*s1.get_linksCounter(), 1);
    ASSERT_EQ(*s2.get_linksCounter(), 1);

    size_t *s1_backup = s1.get_linksCounter();
    size_t *s2_backup = s2.get_linksCounter();
    s2.swap(s1);
    ASSERT_EQ(s1.get_linksCounter(), s2_backup);
    ASSERT_EQ(s2.get_linksCounter(), s1_backup);
    ASSERT_EQ(*s1.get_linksCounter(), 1);
    ASSERT_EQ(*s2.get_linksCounter(), 1);
}


TEST(SuiteName, generalOper) {
    MySharedPtr<int> sPtr(new int(12));
    ASSERT_EQ(*sPtr, 12);
    ASSERT_EQ(*sPtr.get_linksCounter(), 1);
    *sPtr = 13;
    ASSERT_EQ(*sPtr, 13);
    ASSERT_EQ(*sPtr.get_linksCounter(), 1);
    *sPtr = *sPtr + 20;
    ASSERT_EQ(*sPtr, 33);

    MySharedPtr<int> sPtr2{};
    ASSERT_EQ(sPtr2.get(), nullptr);
    ASSERT_EQ(*sPtr2.get_linksCounter(), 1);
    sPtr2 = new int(4);
    ASSERT_EQ(*sPtr2, 4);
    ASSERT_EQ(*sPtr2.get_linksCounter(), 1);

    *sPtr2 = *sPtr + *sPtr2 * 2;
    ASSERT_EQ(*sPtr2, 41);
}

TEST(SuiteName, eqTest) {
    MySharedPtr<int> ptr1{new int(13)};
    MySharedPtr<int> ptr2{new int(15)};

    int *ptr2_backup = ptr2.get();
    ptr1 = std::move(ptr2);
    ASSERT_EQ(ptr2.get(), nullptr);
    ASSERT_EQ(ptr1.get(), ptr2_backup);

    int *tmp = new int(123);
    ptr2 = tmp;
    ASSERT_EQ(*ptr2, 123);
}