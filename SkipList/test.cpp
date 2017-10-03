#include <gtest/gtest.h>
#include "SkipList.h"


TEST(SuiteName, base) {
    SkipList<int, int> list{};
//    list.insert({15, 13});

    int size = 7;
    int arr[] = {1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < size; ++i) {
        list.insert(std::pair<int, int *>(15 + i, &arr[i]));
    }

    for (int i = 0; i < size; ++i) {
//        int * a = list.at(15 + i).second;
        std::pair<int, int *> a = list.at(15 + i);
//        auto a = list.at(15 + i);

        ASSERT_EQ(*list.at(15 + i).second, arr[i]);
    }


//    std::cout << std::less<int>()(13, 12) << std::endl;



}
