#include <gtest/gtest.h>
#include "SkipList.h"

TEST(SuiteName, base) {
    SkipList<int, int> list;

    int size = 7;
    int arr[] = {1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < size; ++i) {
        list.insert({15 + i, arr[i]});
    }

    auto it = list.find(15);
    ASSERT_EQ(it->second, 1);
    it = list.find(17);
    ASSERT_EQ(it->second, 3);
    it = list.find(3);
    ASSERT_EQ(it, list.end());


    ASSERT_EQ(list.at(15), 1);
    ASSERT_EQ(list.at(18), 4);
    ASSERT_NO_THROW(list.at(15));
    ASSERT_ANY_THROW(list.at(1000));

    {
        int i = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            ASSERT_EQ(it->second, arr[i]);
            ++i;
        }
        ASSERT_EQ(i, size);
    }

    {
        int i = 0;
        auto it = list.begin();
        while (it != list.end()) {
            ASSERT_EQ(it->second, arr[i]);
            ++i;
            ++it;
        }
        ASSERT_EQ(i, size);
    }

    list.insert({15, -12});
    it = list.find(15);
    ASSERT_EQ(it->second, -12);
    ASSERT_EQ(list.at(15), -12);


    list.erase(15);
    ASSERT_EQ(list.begin()->second, 2);
    ASSERT_EQ(list.find(15), list.end());

    list.insert({15, 1});

    {
        list.erase(17);

        ASSERT_EQ(list.find(17), list.end());
        ASSERT_ANY_THROW(list.at(17));
        it = list.find(16);
        ASSERT_EQ(it->second, 2);
        ASSERT_EQ((++it)->second, 4);

        list.insert({17, 3});
    }

    {
        list.erase(list.find(17));

        ASSERT_EQ(list.find(17), list.end());
        ASSERT_ANY_THROW(list.at(17));
        it = list.find(16);
        ASSERT_EQ(it->second, 2);
//        ASSERT_EQ(*++it, 4);
        ASSERT_EQ((++it)->second, 4);

        list.insert({17, 3});
    }

    {
        list.erase(list.find(17), list.find(19));

        ASSERT_EQ(list.find(17), list.end());
        ASSERT_EQ(list.find(18), list.end());
        ASSERT_ANY_THROW(list.at(17));
        ASSERT_ANY_THROW(list.at(18));
        it = list.find(16);
        ASSERT_EQ(it->second, 2);
        ASSERT_EQ((++it)->second, 5);

        list.insert({17, 3});
        list.insert({18, 4});
    }
}

std::vector<int> vget() {
    std::vector<int> v = { 0, 1, 2 };
    return v;
}

TEST(SuiteName, swap) {
    SkipList<int, int> list;

    int size = 3;
    int arr[] = {1, 2, 3};

    for (int i = 0; i < size; ++i) {
        list.insert({15 + i, arr[i]});
    }


    SkipList<int, int> list2;

    int size2 = 7;
    int arr2[] = {11, 12, 13, 14, 15, 16, 17};

    for (int i = 0; i < size2; ++i) {
        list2.insert({31 + i, arr2[i]});
    }

    list.swap(list2);
    ASSERT_EQ(list.size(), size2);
    ASSERT_EQ(list2.size(), size);

    int i = 0;
    for (auto &&item : list) {
        ASSERT_EQ(item.second, arr2[i]);
        ++i;
    }

    i = 0;
    for (auto &&item : list2) {
        ASSERT_EQ(item.second, arr[i]);
        ++i;
    }
}


TEST(SuiteName, copy) {
    SkipList<int, int> list;

    int size = 1;
    int arr[] = {1};

    for (int i = 0; i < size; ++i) {
        list.insert({15 + i, arr[i]});
    }

    SkipList<int, int> list2;

    int size2 = 2;
    int arr2[] = {11, 12};

    for (int i = 0; i < size2; ++i) {
        list2.insert({31 + i, arr2[i]});
    }

    list = list2;
    ASSERT_EQ(list.size(), size2);
    ASSERT_EQ(list2.size(), size2);

    int i = 0;
    for (auto &&item : list) {
        ASSERT_EQ(item.second, arr2[i]);
        ++i;
    }
}


TEST(SuiteName, riter) {
    SkipList<int, int> list;

    int size = 7;
    int arr[] = {1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < size; ++i) {
        list.insert({15 + i, arr[i]});
    }

    auto it = list.rbegin();
    for (int j = 0; j < size; ++j) {
        ASSERT_EQ(it->second, arr[size - 1 - j]);
        ++it;
    }

    int i = size - 1;
    it = list.rbegin();
    while (it != list.rend()) {
        ASSERT_EQ(it->second, arr[i]);
        --i;
        ++it;
    }
    ASSERT_EQ(i, -1);
}


TEST(SuiteName, 12) {
    SkipList<int, int> list;

    int size = 7;
    int arr[] = {1, 2, 3, 4, 5, 6, 7};

    for (int i = 0; i < size; ++i) {
        list.insert({15 + i, arr[i]});
    }

    ASSERT_EQ(list.at(15), 1);
    ASSERT_EQ(list[15].second, 1);
    ASSERT_EQ(list.at(17), 3);
    ASSERT_EQ(list[17].second, 3);

    ASSERT_ANY_THROW(list.at(13));
    ASSERT_ANY_THROW(list[13]);
}
