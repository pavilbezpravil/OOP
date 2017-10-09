#pragma once

#include "SkipListNode.h"

template <typename Key ,typename ValueType>
class SkipListIterator : public std::iterator<std::forward_iterator_tag, ValueType> {
private:
    typedef SkipListNode<Key, ValueType> t_SkipListIterator;
    typedef SkipListNode<Key, ValueType> t_Node;
    typedef typename t_Node::t_Value t_Value;

    SkipListNode<Key, ValueType> *mCur;

public:
    SkipListIterator(SkipListNode<Key, ValueType> *x) {
        mCur = x;
    }

    t_SkipListIterator *get() { return mCur; };
    const t_SkipListIterator *get() const { return mCur; };

    SkipListIterator &operator++() {
        mCur = mCur->nextNodes[0];
        return *this;
    }

    SkipListIterator operator++(int) {
        SkipListIterator<Key, ValueType> res = *this;
        ++res;
        return res;
    }

    bool operator==(const SkipListIterator &rhs) const {
        return mCur->value.first == rhs.mCur->value.first;
    }

    bool operator!=(const SkipListIterator &rhs) const {
        return mCur->value.first != rhs.mCur->value.first;
    }

    ValueType operator*() {
        return mCur->value.second;
    }

    ValueType *operator->() {
        return mCur->value.second;
    }
};
