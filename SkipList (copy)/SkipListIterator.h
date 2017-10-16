#pragma once

#include "SkipListNode.h"

template <typename Key ,typename ValueType>
class SkipListIterator : public std::iterator<std::forward_iterator_tag, ValueType> {
private:
    typedef SkipListIterator<Key, ValueType> t_SkipListIterator;
    typedef SkipListNode<Key, ValueType> t_Node;
    typedef typename t_Node::t_Value t_Value;

    SkipListNode<Key, ValueType> *mCur;

public:
    SkipListIterator(SkipListNode<Key, ValueType> *x) {
        mCur = x;
    }

    t_Node *get() { return mCur; };
    const t_Node *get() const { return mCur; };

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

    t_Value operator*() {
        return mCur->value;
    }

    t_Value *operator->() {
        return &mCur->value;
    }
};

template <typename Key ,typename ValueType>
class SkipListConstIterator : public std::iterator<std::forward_iterator_tag, ValueType> {
private:
    typedef SkipListConstIterator<Key, ValueType> t_SkipListIterator;
    typedef SkipListNode<Key, ValueType> t_Node;
    typedef const typename t_Node::t_Value t_Value;

    const t_Node *mCur;

public:
    SkipListConstIterator(const t_Node *x) : mCur(x) {

    }

    const t_Node *get() const { return mCur; };

    SkipListConstIterator &operator++() {
        mCur = mCur->nextNodes[0];
        return *this;
    }

    SkipListConstIterator operator++(int) {
        SkipListConstIterator<Key, ValueType> res = *this;
        ++res;
        return res;
    }

    bool operator==(const SkipListConstIterator &rhs) const {
        return mCur->value.first == rhs.mCur->value.first;
    }

    bool operator!=(const SkipListConstIterator &rhs) const {
        return mCur->value.first != rhs.mCur->value.first;
    }

    t_Value operator*() {
        return mCur->value;
    }

    t_Value *operator->() {
        return &mCur->value;
    }
};

template <typename Key ,typename ValueType>
class SkipListReverseIterator : public std::iterator<std::forward_iterator_tag, ValueType> {
private:
    typedef SkipListReverseIterator<Key, ValueType> t_SkipListReverseIterator;
    typedef SkipListNode<Key, ValueType> t_Node;
    typedef typename t_Node::t_Value t_Value;

    SkipListNode<Key, ValueType> *mCur;

public:
    SkipListReverseIterator(SkipListNode<Key, ValueType> *x) {
        mCur = x;
    }

    t_Node *get() { return mCur; };
    const t_Node *get() const { return mCur; };

    SkipListReverseIterator &operator++() {
        mCur = mCur->mRoot;
        return *this;
    }

    SkipListReverseIterator operator++(int) {
        SkipListReverseIterator<Key, ValueType> res = *this;
        ++res;
        return res;
    }

    bool operator==(const SkipListReverseIterator &rhs) const {
        return mCur->value.first == rhs.mCur->value.first;
    }

    bool operator!=(const SkipListReverseIterator &rhs) const {
        return mCur->value.first != rhs.mCur->value.first;
    }

    t_Value operator*() {
        return mCur->value;
    }

    t_Value *operator->() {
        return &mCur->value;
    }
};

template <typename Key ,typename ValueType>
class SkipListConstReverseIterator : public std::iterator<std::forward_iterator_tag, ValueType> {
private:
    typedef SkipListConstReverseIterator<Key, ValueType> t_SkipListReverseIterator;
    typedef SkipListNode<Key, ValueType> t_Node;
    typedef typename t_Node::t_Value t_Value;

    SkipListNode<Key, ValueType> *mCur;

public:
    SkipListConstReverseIterator(SkipListNode<Key, ValueType> *x) {
        mCur = x;
    }

    t_Node *get() { return mCur; };
    const t_Node *get() const { return mCur; };

    SkipListConstReverseIterator &operator++() {
        mCur = mCur->mRoot;
        return *this;
    }

    SkipListConstReverseIterator operator++(int) {
        SkipListConstReverseIterator<Key, ValueType> res = *this;
        ++res;
        return res;
    }

    bool operator==(const SkipListConstReverseIterator &rhs) const {
        return mCur->value.first == rhs.mCur->value.first;
    }

    bool operator!=(const SkipListConstReverseIterator &rhs) const {
        return mCur->value.first != rhs.mCur->value.first;
    }

    t_Value operator*() {
        return mCur->value;
    }

    t_Value *operator->() {
        return &mCur->value;
    }
};
