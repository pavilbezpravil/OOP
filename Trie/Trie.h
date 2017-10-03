#pragma once

#include <vector>
#include "TrieIterator.h"

#define ALPHABETS 26
#define CASE 'a'

template <typename T>
struct TrieNode {
    TrieNode *root;
    TrieNode *child[ALPHABETS];
    std::vector<int> occurrences;
};

template <class T>
class Trie {
public:
    typedef TrieIterator<T> iterator;
//    typedef ConstTrieIterator<T> const_iterator;
    typedef TrieIterator<const T> const_iterator;

    typedef T value_type;
    typedef std::string key_type;

    Trie();
    template <class InputIterator> Trie(InputIterator first, InputIterator last);
    Trie(const Trie<T> & trie);
    ~Trie();

    Trie<T> & operator= (const Trie & trie);

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    bool empty() const; //Test whether container is empty
    size_t size() const;

    value_type& operator[] (const key_type& k);

    std::pair<iterator,bool> insert (const key_type& k, const value_type& val);

    template <class InputIterator> void insert (InputIterator first, InputIterator last);

    //удаление
    void erase (iterator position);
    size_t erase (const key_type& k);
    void erase (iterator first, iterator last);

    void swap (Trie& trie);

    void clear(); //очистить структуру

    //найти элемент
    iterator find (const key_type& k);
    const_iterator find (const key_type& k) const;

    // TODO:
//    SubTrie<T> GetSubTrie(const key_type & subKey); // получить subtree
};