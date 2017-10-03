#pragma once

#include <iterator>

template<class T>
class TrieIterator : public std::iterator<std::forward_iterator_tag, std::pair<std::string, T &>> {
public:
    TrieIterator(value_type &x);
    TrieIterator(const TrieIterator &mit);

    TrieIterator &operator++();
    TrieIterator operator++(int);

    bool operator==(const TrieIterator &rhs);
    bool operator!=(const TrieIterator &rhs);

    value_type operator*();
    value_type *operator->();
};
