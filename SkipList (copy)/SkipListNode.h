#pragma once

#include <functional>
#include <cstring>
#include <limits>
#include <random>

template <typename Key, typename ValueType>
struct SkipListNode {
    typedef SkipListNode<Key, ValueType> t_SkipListNode;
    typedef std::pair<const Key, ValueType> t_Value;

    t_Value value;
    t_SkipListNode *mRoot;
    std::vector<t_SkipListNode *> nextNodes;
    int levels;

    SkipListNode(t_Value value, int levels, t_SkipListNode *root) : value(value), levels(levels), mRoot(root),
                                              nextNodes(std::vector<t_SkipListNode *>(levels)) {
        for (auto &&node : nextNodes) {
            node = nullptr;
        }
    }

    static SkipListNode<Key, ValueType> NIL(const Key &key, int levels, t_SkipListNode *root) {
        return t_SkipListNode( t_Value(key, ValueType()) , levels, root);
    };

    virtual ~SkipListNode() {

    }
};