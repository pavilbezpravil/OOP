#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "UniquePTR.h"

int global_mem_alloc = 0;
void *operator new(size_t size) {
    ++global_mem_alloc;
    return malloc(size);
}

void operator delete(void *ptr) {
    --global_mem_alloc;
    free(ptr);
}

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


TEST(SuiteName, construct) {
    UniquePTR<int> uPtr{};
    ASSERT_EQ(uPtr.get(), nullptr);

    int *ptr = new int(42);
    uPtr = ptr;
    ASSERT_EQ(*uPtr, 42);
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
    UniquePTR<std::string, deleterArr<std::string>> ptrArr(new std::string[14]);
}


TEST(SuiteName, release) {
    UniquePTR<int> uPtr(new int(13));
    int *ptr = uPtr.release();

    ASSERT_EQ(uPtr.get(), nullptr);
    ASSERT_EQ(*ptr, 13);
    delete(ptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int mem_alloc = global_mem_alloc;
//    std::cout << mem_alloc << std::endl;
//    std::cout << 12 << std::endl;
    int res = RUN_ALL_TESTS();
//    std::cout << mem_alloc << std::endl;

//    assert(global_mem_alloc == mem_alloc);
//    return res;
}