#pragma once

#include <functional>
#include <cstring>
#include <limits>
#include <random>

#include "SkipListNode.h"
#include "SkipListIterator.h"

template <typename Key,
        typename ValueType,
        int MAX_LEVELS = 4,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<std::pair<const Key,ValueType> > >
class SkipList {
private:
    typedef SkipList<Key, ValueType, MAX_LEVELS, Compare, Alloc> t_SkipList;
    typedef SkipListNode<Key, ValueType> t_Node;
    typedef typename t_Node::t_Value t_Value;
    typedef SkipListIterator<Key, ValueType>        iterator;
    typedef SkipListIterator<Key, const ValueType>  const_iterator;

    Alloc mAlloc;
    Compare mCompare;

    t_Node mRoot;
    t_Node mNil;
    size_t mSize;

public:
    // TODO: key?
    SkipList() : mRoot(t_Node(t_Value(std::numeric_limits<Key>::min(), ValueType()) , MAX_LEVELS)),
                mNil(t_Node::NIL(std::numeric_limits<Key>::max(), MAX_LEVELS)) , mSize(0) {
        for (int lvl = 0; lvl < MAX_LEVELS; ++lvl) {
            mRoot.nextNodes[lvl] = &mNil;
        }
    }

//    explicit SkipList(const Compare &comp, const Alloc &a = Alloc()) : mCompare(comp), mAlloc(a), SkipList() {
//
//    }

    SkipList(const SkipList &another) : mRoot(another.mRoot), mNil(another.mNil), mSize(another.mSize) {
        t_Node **nodes = new t_Node*[mSize];
        auto it = another.begin();
        for (size_t i = 0; i < mSize; ++i) {
            nodes[i] = new t_Node(*it.get());
            ++it;
        }

        for (auto it = another.begin(); it != another.end(); ++it) {
            t_Node *node{};
        }
    }

    virtual ~SkipList() {
        clear();
    }

//    SkipList &operator=(const SkipList &origVal) {
//        if (this!=&origVal)
//        {
//            clear();
//
//            head.Initialize(NULL);
//            maxLevel = origVal.maxLevel;
//            size = origVal.size;
//
//            if (size == 0)
//                currentPtr = NULL;
//            else
//            {
//                // update is an array that, for each level in the new list, will
//                //   point to the rightmost node in that level that we've created
//                //   so far.
//                Array<SkipNode*> update(0, maxLevel);
//                update.Initialize(NULL);
//
//                // origTravPtr starts pointing to first node
//                SkipNode *origTravPtr = origVal.head[0];
//                *copyTravPtr;
//
//                while (origTravPtr != NULL)
//                {
//                    // create a new node that has the same height as the current node
//                    //   in the origVal, and copy into it the origVal node's element
//                    copyTravPtr = new SkipNode(origTravPtr->nodeTopLevel, maxLevel);
//                    copyPtr->element = origTravPtr->element;
//
//                    // for all the levels that this node has...
//                    for (int level = 0; level <= copyPtr->nodeTopLevel; level++)
//                    {
//                        // if this is the first node on this level, then head should
//                        //  point to it; otherwise, the most recent prior node on this
//                        //  level should point to it
//                        if (update[level] == NULL)
//                            head[level] = copyTravPtr;
//                        else
//                            (update[level]->ptrArray)[level] = copyTravPtr;
//
//                        // and now this is the "most recent node" for this level
//                        update[level] = copyTravPtr;
//                    }
//
//                    if (origVal.currentPtr == origTravPtr)
//                        currentPtr = copyTravPtr;
//
//                    // move origTravPtr to the next node in the parameter skiplist
//                    origTravPtr = (origTravPtr->ptrArray)[0];
//                }
//            }
//        }
//        return *this;
//    }

    iterator begin() { return iterator(mRoot.nextNodes[0]); }
    const_iterator begin() const { return const_iterator(mRoot.nextNodes[0]); }
    iterator end() { return iterator(&mNil); }
    const_iterator end() const { return const_iterator(&mNil); }

    bool empty() const { return mSize == 0; }
    size_t size() const { return mSize; }

    t_Value &operator[](const Key &key);
    const t_Value &operator[](const Key &key) const;

    t_Value &at(const Key &key) {
        iterator res = find(key);
        if (res == end()) {
            // TODO:
            throw std::out_of_range("at()");
        }
        return {res.get()->value};
    }

    const ValueType &at(const Key &key) const;

    // TODO: iterator?
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
            return {iterator(cur->nextNodes[0]), true};
        }
        int lvl_new_node = randomLevel();
        t_Node *cur_node = new t_Node(x, lvl_new_node);
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
        // TODO: aloc
        delete(removedNode);
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
        std::swap(mRoot, another.mRoot);
        std::swap(mNil, another.mNil);
        std::swap(mCompare, another.mCompare);
        std::swap(mAlloc, another.mAlloc);
    }

    void clear() {
        t_Node *cur = mRoot.nextNodes[0];
        while (cur != &mNil) {
            t_Node *next = cur->nextNodes[0];
            delete(cur);
            cur = next;
        }
    }

    iterator find(const Key &key) {
        t_Node *before = internalFindBefore(key);

        return (before != &mNil && before->nextNodes[0]->value.first == key) ?
               iterator(before->nextNodes[0]) : iterator(&mNil);
    }

    // TODO: how to avoid duplication
    const_iterator find(const Key &key) const;

private:

    // TODO: ask how named
    t_Node *internalFindBefore(const Key &key) {
        t_Node *cur = &mRoot;

        for (int lvl = MAX_LEVELS - 1; lvl >= 0; --lvl) {
            while (cur->nextNodes[lvl] && Compare()(cur->nextNodes[lvl]->value.first, key)) {
                cur = cur->nextNodes[lvl];
            }
        }
        return cur;
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
