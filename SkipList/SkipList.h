#pragma once

#include <functional>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <random>

//#define MAX_LEVELS 10

template <typename Key, typename ValueType, int MAX_LEVELS = 4>
struct SkipListNode {
    std::pair<const Key, ValueType *> value;
    SkipListNode<Key, ValueType, MAX_LEVELS> *next_nodes[MAX_LEVELS];

    SkipListNode(std::pair<const Key, ValueType *> value) : value(value) {
        std::memset(next_nodes, 0, MAX_LEVELS * sizeof(SkipListNode<Key, ValueType *> *));
    }

    SkipListNode() = default;


    static SkipListNode<Key, ValueType, MAX_LEVELS> NIL(const Key &key) {
        return SkipListNode<Key, ValueType, MAX_LEVELS>{std::pair<const Key, ValueType *>{key, nullptr}};
    };

    virtual ~SkipListNode() {

    }
};

template <typename Key ,typename ValueType, int MAX_LEVELS = 4>
class SkipListIterator : public std::iterator<std::forward_iterator_tag, ValueType> {
private:
    // TODO: mb cur, next pointer
    SkipListNode<Key, ValueType, MAX_LEVELS> *cur;
public:
    SkipListIterator(SkipListNode<Key, ValueType, MAX_LEVELS> *x) {
        cur = x;
    }

    SkipListNode<Key, ValueType, MAX_LEVELS> *get() { return cur; };
    const SkipListNode<Key, ValueType, MAX_LEVELS> *get() const { return cur; };

    SkipListIterator &operator++() {
        cur = cur->next_nodes[0];
        return *this;
    }

    SkipListIterator operator++(int) {
        SkipListIterator<Key, ValueType> res = *this;
        ++res;
        return res;
    }

    bool operator==(const SkipListIterator &rhs) {
        return *cur->value.second == *rhs.cur->value.second;
    }

    bool operator!=(const SkipListIterator &rhs) {
        return *cur->value.second != *rhs.cur->value.second;
    }

    ValueType operator*() {
        return *cur->value.second;
    }

    ValueType *operator->() {
        return cur->value.second;
    }
};

template <typename Key,
        typename ValueType,
        int MAX_LEVELS = 4,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<std::pair<const Key,ValueType> > >
class SkipList {
private:
    typedef SkipList<Key, ValueType, MAX_LEVELS, Compare, Alloc> t_SkipList;
    typedef SkipListNode<Key, ValueType, MAX_LEVELS> t_Node;
    typedef std::pair<const Key, ValueType *> value_type;

    t_Node root;
    t_Node nil;

    size_t mSize;
//    size_t MAX_KEY = std::numeric_limits<Key>::max();
public:
    typedef SkipListIterator<Key, ValueType, MAX_LEVELS>        iterator;
    typedef SkipListIterator<Key, const ValueType, MAX_LEVELS>  const_iterator;


    SkipList() : root(t_Node(std::pair<size_t, ValueType *>(std::numeric_limits<Key>::min(), nullptr))),
                nil(t_Node(std::pair<size_t, ValueType *>(std::numeric_limits<Key>::max(), nullptr))) , mSize(0) {
        for (int lvl = 0; lvl < MAX_LEVELS; ++lvl) {
            root.next_nodes[lvl] = &nil;
        }
    }

    explicit SkipList(const Compare &comp, const Alloc &a = Alloc());
    SkipList(const SkipList &another);

    virtual ~SkipList() {

    }

    SkipList &operator=(const SkipList &another);

    iterator begin() { return iterator(root.next_nodes[0]); }
    const_iterator begin() const { return const_iterator(root.next_nodes[0]); }
    iterator end() { return iterator(&nil); }
    const_iterator end() const { return const_iterator(&nil); }

    bool empty() const { return mSize == 0; }
    size_t size() const { return mSize; }

    value_type &operator[](const Key &key);
    const value_type &operator[](const Key &key) const;

    value_type &at(const Key &key) {
        t_Node *cur = &root;

        for (int lvl = MAX_LEVELS - 1; lvl >= 0; --lvl) {
            while (Compare()(cur->next_nodes[lvl]->value.first, key) ) {
                cur = cur->next_nodes[lvl];
            }
        }
        value_type res{key, nullptr};

        ValueType a = *cur->next_nodes[0]->value.second;

        if (cur->next_nodes[0]->value.first == key) {
            res.second = cur->next_nodes[0]->value.second;
        }
        return res;
    }

    const ValueType &at(const Key &key) const {
        // TODO: recursion?
        return at(key);
    }

//    std::pair<iterator, bool> insert(const value_type &x) {
    void insert(const value_type &x) {
        t_Node *updateNodes[MAX_LEVELS];// TODO:
        t_Node *cur = &root;

        for (int lvl = MAX_LEVELS - 1; lvl >= 0; --lvl) {
            while (Compare()(cur->next_nodes[lvl]->value.first, x.first) ) {
                cur = cur->next_nodes[lvl];
            }
            updateNodes[lvl] = cur;
        }
        // TODO: if
        t_Node *cur_node = new t_Node(x);
        int cur_lvl = randomLevel();
        for (int lvl = 0; lvl < cur_lvl; ++lvl) {
            cur_node->next_nodes[lvl] = updateNodes[lvl]->next_nodes[lvl];
            updateNodes[lvl]->next_nodes[lvl] = cur_node;
        }
        // TODO:
//        return std::pair();
    }

    void erase(iterator position);
    void erase(const Key &key);
    void erase(iterator first, iterator last);

    void swap(t_SkipList &another);

    void clear();

    iterator find(const Key &key) {
        t_Node *cur = &root;

        for (int lvl = MAX_LEVELS - 1; lvl >= 0; --lvl) {
            while (Compare()(cur->next_nodes[lvl]->value.first, key) ) {
                cur = cur->next_nodes[lvl];
            }
        }
        cur = cur->next_nodes[0];
        return (cur->value.first == key) ? iterator(cur) : iterator(&nil);
    }

    const_iterator find(const Key &key) const {
        // TODO: recursion
        return find(key);
    }

private:
    int randomLevel() {
        static std::default_random_engine generator;
        static std::uniform_int_distribution<int> distribution(0, 1);

        int lvl = 1;
        while (distribution(generator) && lvl <= MAX_LEVELS) {
            ++lvl;
        }
        return lvl;
    }
};
