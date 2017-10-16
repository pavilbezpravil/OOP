#pragma once

#include <functional>
#include <cstring>
#include <limits>
#include <random>

#include "SkipListNode.h"
#include "SkipListIterator.h"

template <typename Key,
        typename ValueType,
        int MAX_LEVELS = 2,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<SkipListNode<Key, ValueType> > >
class SkipList {
public:
    typedef SkipList<Key, ValueType, MAX_LEVELS, Compare, Alloc>    t_SkipList;
    typedef SkipListNode<Key, ValueType>    t_Node;
    typedef typename t_Node::t_Value        t_Value;
    typedef SkipListIterator<Key, ValueType>                iterator;
    typedef SkipListConstIterator<Key, ValueType>           const_iterator;
    typedef SkipListReverseIterator<Key, ValueType>         reverse_iterator;
    typedef SkipListConstReverseIterator<Key, ValueType>    const_reverse_iterator;
private:

    Alloc mAlloc;
    Compare mCompare;

    t_Node mRoot;
    t_Node mNil;
    size_t mSize;

public:
    SkipList() : mRoot(t_Node(t_Value(std::numeric_limits<Key>::min(), ValueType()), MAX_LEVELS, nullptr)),
                mNil(t_Node::NIL(std::numeric_limits<Key>::max(), MAX_LEVELS, &mRoot)) , mSize(0) {
        for (int lvl = 0; lvl < MAX_LEVELS; ++lvl) {
            mRoot.nextNodes[lvl] = &mNil;
        }
    }

    explicit SkipList(const Compare &comp, const Alloc &a = Alloc()) :
            mRoot(t_Node(t_Value(std::numeric_limits<Key>::min(), ValueType()) , MAX_LEVELS, nullptr)),
            mNil(t_Node::NIL(std::numeric_limits<Key>::max(), MAX_LEVELS, &mRoot)) , mSize(0), mCompare(comp), mAlloc(a) {

    }

    SkipList(const SkipList &another) : mRoot(another.mRoot), mNil(another.mNil), mSize(another.mSize) {
        *this = another;
    }

    virtual ~SkipList() {
        clear();
    }

    SkipList &operator=(const SkipList &another) {
        if (this!=&another) {
            clear();
            for (int lvl = 0; lvl < MAX_LEVELS; ++lvl) {
                mRoot.nextNodes[lvl] = &mNil;
            }

            for (auto &&val : another) {
                insert(val);
            }
        }
        return *this;
    }

    iterator begin() { return iterator(mRoot.nextNodes[0]); }
    const_iterator begin() const { return const_iterator(mRoot.nextNodes[0]); }
    iterator end() { return iterator(&mNil); }
    const_iterator end() const { return const_iterator(&mNil); }

    reverse_iterator rbegin() { return ++reverse_iterator(&mNil); }
    reverse_iterator rend() { return reverse_iterator(&mRoot); }
    const_reverse_iterator rbegin() const { return ++const_reverse_iterator(&mNil); }
    const_reverse_iterator rend() const { return const_reverse_iterator(&mRoot); }

    bool empty() const { return mSize == 0; }
    size_t size() const { return mSize; }

    t_Value &operator[](const Key &key) {
        iterator res = find(key);
        if (res == end()) {
            throw std::out_of_range("at()");
        }
        return res.get()->value;
    }

    const t_Value &operator[](const Key &key) const {
        const_iterator res = find(key);
        if (res == end()) {
            throw std::out_of_range("at()");
        }
        return res.get()->value;
    }

    ValueType &at(const Key &key) {
        iterator res = find(key);
        if (res == end()) {
            throw std::out_of_range("at()");
        }
        return {res.get()->value.second};
    }

    const ValueType &at(const Key &key) const {
        const_iterator res = find(key);
        if (res == end()) {
            throw std::out_of_range("at()");
        }
        return {res.get()->value.second};
    }

    std::pair<iterator, bool> insert(const t_Value &x) {
        t_Node *updateNodes[MAX_LEVELS];
        t_Node *cur = &mRoot;

        for (int lvl = MAX_LEVELS - 1; lvl >= 0; --lvl) {
            while (cur->nextNodes[lvl] && Compare()(cur->nextNodes[lvl]->value.first, x.first) ) {
                cur = cur->nextNodes[lvl];
            }
            updateNodes[lvl] = cur;
        }
        // if already contain
        if (cur->nextNodes[0] && cur->nextNodes[0]->value.first == x.first) {
            cur->nextNodes[0]->value.second = x.second;
            return {iterator(cur->nextNodes[0]), false};
        }
        int lvl_new_node = randomLevel();
        void *ptr = mAlloc.allocate(1);
        t_Node *cur_node = new(ptr) t_Node(x, lvl_new_node, updateNodes[0]);
        updateNodes[0]->nextNodes[0]->mRoot = cur_node;
        for (int lvl = 0; lvl < lvl_new_node; ++lvl) {
            cur_node->nextNodes[lvl] = updateNodes[lvl]->nextNodes[lvl];
            updateNodes[lvl]->nextNodes[lvl] = cur_node;
        }
        ++mSize;
        return  {iterator(cur_node), true};
    }

    void erase(iterator it) {
        if (it != end()) {
            erase(it.get()->value.first);
        }
    }

    void erase(const Key &key) {
        t_Node *updateNodes[MAX_LEVELS];
        t_Node *cur = &mRoot;

        for (int lvl = MAX_LEVELS - 1; lvl >= 0; --lvl) {
            while (cur->nextNodes[lvl] && Compare()(cur->nextNodes[lvl]->value.first, key) ) {
                cur = cur->nextNodes[lvl];
            }
            updateNodes[lvl] = cur;
        }
        if (cur->nextNodes[0]->value.first != key) {
            return;
        }

        t_Node *removedNode = cur->nextNodes[0];
        for (int lvl = 0; lvl < MAX_LEVELS; ++lvl) {
            if (updateNodes[lvl]->nextNodes[lvl] != removedNode) { break; }
            updateNodes[lvl]->nextNodes[lvl] = removedNode->nextNodes[lvl];
        }
        updateNodes[0]->mRoot = updateNodes[0];
        mAlloc.deallocate(removedNode, 1);
        --mSize;
    }

    void erase(iterator first, iterator last) {
        iterator it = first;
        iterator next = first;
        while (it != last) {
            ++next;
            erase(it);
            it = next;
        }
    }

    void swap(t_SkipList &another) {
        std::swap(mSize, another.mSize);
        for (int lvl = 0; lvl < MAX_LEVELS; ++lvl) {
            std::swap(mRoot.nextNodes[lvl], another.mRoot.nextNodes[lvl]);
        }
        std::vector<t_Node *> thisBeforeNodes = internalFindBeforeOnRange(mNil.value.first, MAX_LEVELS, 0);
        std::vector<t_Node *> anotherBeforeNodes = another.internalFindBeforeOnRange(another.mNil.value.first, MAX_LEVELS, 0);
        for (int i = 0; i < thisBeforeNodes.size(); ++i) {
            std::swap(thisBeforeNodes[i]->nextNodes[i], anotherBeforeNodes[i]->nextNodes[i]);
        }
        std::swap(mCompare, another.mCompare);
        std::swap(mAlloc, another.mAlloc);
    }

    void clear() {
        t_Node *cur = mRoot.nextNodes[0];
        while (cur != &mNil) {
            t_Node *next = cur->nextNodes[0];
            mAlloc.deallocate(cur, 1);
            cur = next;
        }
        mSize = 0;
    }

    iterator find(const Key &key) {
        t_Node *before = internalFindBefore(key);

        return (before != &mNil && before->nextNodes[0]->value.first == key) ?
               iterator(before->nextNodes[0]) : iterator(&mNil);
    }

    const_iterator find(const Key &key) const {
        const t_Node *before = internalFindBefore(key);

        return (before != &mNil && before->nextNodes[0]->value.first == key) ?
               const_iterator(before->nextNodes[0]) : const_iterator(&mNil);
    }

private:

    t_Node *internalFindBefore(const Key &key) {
        t_Node *cur = &mRoot;

        for (int lvl = MAX_LEVELS - 1; lvl >= 0; --lvl) {
            while (cur->nextNodes[lvl] && Compare()(cur->nextNodes[lvl]->value.first, key)) {
                cur = cur->nextNodes[lvl];
            }
        }
        return cur;
    }

    const t_Node *internalFindBefore(const Key &key) const {
        const t_Node *cur = &mRoot;

        for (int lvl = MAX_LEVELS - 1; lvl >= 0; --lvl) {
            while (cur->nextNodes[lvl] && Compare()(cur->nextNodes[lvl]->value.first, key)) {
                cur = cur->nextNodes[lvl];
            }
        }
        return cur;
    }

    std::vector<t_Node *> internalFindBeforeOnRange(const Key &key, int highest, int lower) {
        std::vector<t_Node *> beforeNodes(highest - lower);

        t_Node *cur = &mRoot;
        for (int lvl = MAX_LEVELS - 1; lvl >= 0; --lvl) {
            if (lvl < lower) { break; }
            while (cur->nextNodes[lvl] && Compare()(cur->nextNodes[lvl]->value.first, key)) {
                cur = cur->nextNodes[lvl];
            }
            if (lvl < highest) {
                beforeNodes[lvl - lower] =cur;
            }
        }
        assert(beforeNodes.size() == (highest - lower) );
        return beforeNodes;
    }

    int randomLevel() {
        static std::default_random_engine generator;
        static std::uniform_int_distribution<int> distribution(0, 1);

        int lvl = 1;
        while (distribution(generator) && lvl < MAX_LEVELS) {
            ++lvl;
        }
        return lvl;
    }
};
