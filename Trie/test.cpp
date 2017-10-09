#include "Trie.h"
#include <gtest/gtest.h>

TEST(SuiteName, insertAndIter) {
    Trie<int> trie;

    int size = 6;
    std::string keys[size] = {
            "a",
            "aa",
            "aaa",
            "aaaa",
            "b",
            "bbb"
    };

    int values[size] = {
            0,
            1,
            2,
            3,
            4,
            5
    };

    for (int i = 0; i < size; ++i) {
        trie.insert(keys[i], values[i]);
    }


    {
        auto it = trie.begin();
        for (int i = 0; i < size; ++i) {
            ASSERT_EQ(*it, values[i]);
            ++it;
        }
        ASSERT_EQ(it, trie.end());
    }

    {
        int i = 0;
        for (auto it = trie.begin(); it != trie.end(); ++it) {
            ASSERT_EQ(*it, values[i]);
            ++i;
            ASSERT_TRUE(i < size);
        }
        ASSERT_EQ(i, size);
    }

    {
        int i = 0;
        for (auto &&item : trie) {
            ASSERT_EQ(item, values[i]);
            ++i;
        }
        ASSERT_EQ(i, size);
    }
}


TEST(SuiteName, base2) {
    Trie<int> trie;

    int size = 6;
    std::string keys[size] = {
            "a",
            "b",
            "c",
            "d",
            "e"
    };
    int values[size] = {
            0,
            1,
            2,
            3,
            4,
            5
    };

    for (int i = 0; i < size; ++i) {
        trie.insert(keys[i], values[i]);
    }

    int i = 0;
    for (auto &&item : trie) {
        ASSERT_EQ(item, values[i]);
        ++i;
    }
}

TEST(SuiteName, base3) {
    Trie<int> trie;

    int size = 6;
    std::string keys[size] = {
            "aaaa",
            "aaab",
            "aaac",
            "aaad",
            "aaae"
    };
    int values[size] = {
            0,
            1,
            2,
            3,
            4,
            5
    };

    for (int i = 0; i < size; ++i) {
        trie.insert(keys[i], values[i]);
    }

    int i = 0;
    for (auto &&item : trie) {
        ASSERT_EQ(item, values[i]);
        ++i;
    }
}

TEST(SuiteName, base4) {
    Trie<int> trie;

    int size = 6;
    std::string keys[size] = {
            "aaaa",
            "aaba",
            "aabb",
            "aabc",
            "aaca"
    };
    int values[size] = {
            0,
            1,
            2,
            3,
            4,
            5
    };

    for (int i = 0; i < size; ++i) {
        trie.insert(keys[i], values[i]);
    }

    int i = 0;
    for (auto &&item : trie) {
        ASSERT_EQ(item, values[i]);
        ++i;
    }
}

TEST(SuiteName, base5) {
    Trie<int> trie;

    int size = 6;
    std::string keys[size] = {
            "aaaa",
            "aa",
            "aaa",
            "a",
            "b",
            "bbb"
    };
    int values[size] = {
            3,
            1,
            2,
            0,
            4,
            5
    };

    for (int i = 0; i < size; ++i) {
        trie.insert(keys[i], values[i]);
    }

    {
        auto it = trie.begin();
        for (int i = 0; i < size; ++i) {
            ASSERT_EQ(*it, values[i]);
            ++it;
        }
    }

    {
        int i = 0;
        for (auto &&item : trie) {
            ASSERT_EQ(item, values[i]);
            ++i;
        }
    }
}

