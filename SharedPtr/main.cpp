#include "SharedPtr.h"
#include <gtest/gtest.h>
#include <memory>

int global_mem_alloc = 0;
void *operator new(size_t size) {
    ++global_mem_alloc;
    return malloc(size);
}

void operator delete(void *ptr) {
    --global_mem_alloc;
    free(ptr);
}

TEST(SuiteName, TestName) {
    int count_alloc = global_mem_alloc;
    {
        SharedPtr<int> s1(new int(5));
        SharedPtr<int> s2(s1);
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
    ASSERT_EQ(count_alloc, global_mem_alloc);
}

TEST(SuiteName, generalOper) {
    int count_alloc = global_mem_alloc;
    {
        SharedPtr<int> sPtr(new int(12));
        ASSERT_EQ(*sPtr, 12);
        ASSERT_EQ(*sPtr.get_linksCounter(), 1);
        *sPtr = 13;
        ASSERT_EQ(*sPtr, 13);
        ASSERT_EQ(*sPtr.get_linksCounter(), 1);
        *sPtr = *sPtr + 20;
        ASSERT_EQ(*sPtr, 33);

        SharedPtr<int> sPtr2{};
        ASSERT_EQ(sPtr2.get(), nullptr);
        ASSERT_EQ(sPtr2.get_linksCounter(), nullptr);
        sPtr2 = new int(4);
        ASSERT_EQ(*sPtr2, 4);
        ASSERT_EQ(*sPtr2.get_linksCounter(), 1);

        *sPtr2 = *sPtr + *sPtr2 * 2;
        ASSERT_EQ(*sPtr2, 41);
    }
    ASSERT_EQ(count_alloc, global_mem_alloc);
}

TEST(SuiteName, eqTest) {
    int count_alloc = global_mem_alloc;
    {
        SharedPtr<int> ptr1{new int(13)};
        SharedPtr<int> ptr2{new int(15)};

        int *ptr2_backup = ptr2.get();
        ptr1 = std::move(ptr2);
        ASSERT_EQ(ptr2.get(), nullptr);
        ASSERT_EQ(ptr2.get_linksCounter(), nullptr);
        ASSERT_EQ(ptr1.get(), ptr2_backup);

        int *tmp = new int(123);
        ptr2 = tmp;
        ASSERT_EQ(*ptr2, 123);
    }
    ASSERT_EQ(count_alloc, global_mem_alloc);
}

TEST(SuiteName, sadfasdf) {
    int count_alloc = global_mem_alloc;
    {
        SharedPtr<int> ptr1{new int(13)};

        {
            SharedPtr<int> ptr2(ptr1);
            ASSERT_EQ(ptr2.get_linksCounter(), ptr1.get_linksCounter());
            ASSERT_EQ(*ptr2.get_linksCounter(), 2);
            ASSERT_EQ(*ptr1, *ptr2);
        }
        ASSERT_EQ(*ptr1.get_linksCounter(), 1);
    }
    ASSERT_EQ(count_alloc, global_mem_alloc);
}


TEST(SuiteName, vlozhenast) {
    int count_alloc = global_mem_alloc;
    {
        SharedPtr<int> ptr1{new int(13)};

        {
            SharedPtr<int> ptr2(ptr1);
            *ptr2 = 111;
        }
        ASSERT_EQ(*ptr1.get_linksCounter(), 1);
        ASSERT_EQ(*ptr1, 111);

        {
            SharedPtr<int> ptr2(ptr1);
            *ptr2 = 505;
            ptr2 = new int(177);
        }
        ASSERT_EQ(*ptr1.get_linksCounter(), 1);
        ASSERT_EQ(*ptr1, 505);

        {
            SharedPtr<int> ptr2(ptr1);
            *ptr2 = 505;
            ptr2 = new int(504);
            ptr1 = ptr2;
        }
        ASSERT_EQ(*ptr1.get_linksCounter(), 1);
        ASSERT_EQ(*ptr1, 504);

    }
    ASSERT_EQ(count_alloc, global_mem_alloc);
}
