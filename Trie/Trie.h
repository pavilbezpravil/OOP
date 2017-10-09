#pragma once

#include <vector>
#include "TrieIterator.h"
#include "TrieNode.h"

template <class ValueType>
class Trie {
    typedef Trie<ValueType> t_Trie;
    typedef TrieNode<ValueType> t_Node;

    typedef TrieIterator<ValueType> iterator;
    typedef TrieIterator<const ValueType> const_iterator;

    typedef std::string key_type;

private:
    size_t mSize;
    t_Node mRoot;

public:

    Trie() : mSize(0), mRoot("", ValueType(), &mRoot) {

    }

    template <class InputIterator> Trie(InputIterator first, InputIterator last);
    Trie(const Trie<ValueType> & trie);

    ~Trie() {
        clear();
    }

    Trie<ValueType> & operator= (const Trie & trie);

    iterator begin() {
        return ++iterator(&mRoot, CASE);
    }
    const_iterator begin() const { return ++const_iterator(&mRoot, CASE); }

    iterator end() { return iterator(&mRoot, CASE); }
    const_iterator end() const { return const_iterator(&mRoot, CASE); }

    bool empty() const { return mSize == 0; }
    size_t size() const { return mSize; }

    ValueType& operator[] (const key_type& k);

//    std::pair<iterator, bool> insert (const std::string& key, const ValueType& value) {
    void insert (const key_type& key, const ValueType& value) {
        t_Node *cur = &mRoot;
        for (size_t i = 0; i < key.size(); ++i) {
            if (!cur->getChild(key[i])) {
                cur->operator[](key[i]) = new t_Node({key.substr(0, i + 1)}, ValueType(), cur, false);
                cur->operator[](key[i])->getValue() = value;
            }
            cur = cur->getChild(key[i]);
        }

//        cur->getValue() = value;
        cur->setIsWord(true);
        ++mSize;
    };

    template <class InputIterator> void insert (InputIterator first, InputIterator last);

    //удаление
    void erase (iterator position);
    size_t erase (const key_type& k);
    void erase (iterator first, iterator last);

    void swap (Trie& trie);

    void clear() {
        clearInternal(&mRoot);
    }

    //найти элемент
    iterator find (const key_type& k);
    const_iterator find (const key_type& k) const;

    // TODO:
//    SubTrie<ValueType> GetSubTrie(const key_type & subKey); // получить subtree

private:
    void clearInternal(t_Node *node) {
        for (char i = CASE; i < CASE + node->getChildSize(); ++i) {
            if (node->getChild(i)) {
                clearInternal(node->getChild(i));
            }
        }
        if (node != &mRoot) {
            delete (node);
        }
    }
};

