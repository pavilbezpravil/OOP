#include <gtest/gtest.h>
#include "SkipList.h"

TEST(SuiteName, base) {
    SkipList<int, int> list{};

    int size = 7;
    int arr[] = {1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < size; ++i) {
        list.insert({15 + i, arr[i]});
    }

    auto it = list.find(15);
    ASSERT_EQ(*it, 1);
    it = list.find(17);
    ASSERT_EQ(*it, 3);
    it = list.find(3);
    ASSERT_EQ(it, list.end());


    ASSERT_EQ(list.at(15).second, 1);
    ASSERT_EQ(list.at(18).second, 4);
    ASSERT_NO_THROW(list.at(15));
    ASSERT_ANY_THROW(list.at(1000));

    {
        int i = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            ASSERT_EQ(*it, arr[i]);
            ++i;
        }
        ASSERT_EQ(i, size);
    }

    {
        int i = 0;
        auto it = list.begin();
        while (it != list.end()) {
            ASSERT_EQ(*it, arr[i]);
            ++i;
            ++it;
        }
        ASSERT_EQ(i, size);
    }

    list.insert({15, -12});
    it = list.find(15);
    ASSERT_EQ(*it, -12);
    ASSERT_EQ(list.at(15).second, -12);


    list.erase(15);
    ASSERT_EQ(*list.begin(), 2);
    ASSERT_EQ(list.find(15), list.end());

    list.insert({15, 1});

    {
        list.erase(17);

        ASSERT_EQ(list.find(17), list.end());
        ASSERT_ANY_THROW(list.at(17));
        it = list.find(16);
        ASSERT_EQ(*it, 2);
        ASSERT_EQ(*++it, 4);

        list.insert({17, 3});
    }

    {
        list.erase(list.find(17));

        ASSERT_EQ(list.find(17), list.end());
        ASSERT_ANY_THROW(list.at(17));
        it = list.find(16);
        ASSERT_EQ(*it, 2);
        ASSERT_EQ(*++it, 4);

        list.insert({17, 3});
    }

    {
        list.erase(list.find(17), list.find(19));

        ASSERT_EQ(list.find(17), list.end());
        ASSERT_EQ(list.find(18), list.end());
        ASSERT_ANY_THROW(list.at(17));
        ASSERT_ANY_THROW(list.at(18));
        it = list.find(16);
        ASSERT_EQ(*it, 2);
        ASSERT_EQ(*++it, 5);

        list.insert({17, 3});
        list.insert({18, 4});
    }
}

// TODO: dont work
TEST(SuiteName, swap) {
    SkipList<int, int> list{};

    int size = 7;
    int arr[] = {1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < size; ++i) {
        list.insert({15 + i, arr[i]});
    }


    SkipList<int, int> list2{};

    int size2 = 6;
    int arr2[] = {11, 12, 13, 14, 15, 16};

    for (int i = 0; i < size2; ++i) {
        list.insert({31 + i, arr2[i]});
    }

//    list.swap(list2);
//    ASSERT_EQ(list.size(), size2);
//    ASSERT_EQ(list2.size(), size);

}
