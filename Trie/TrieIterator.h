#pragma once

#include <iterator>
#include <cassert>
#include "TrieNode.h"

template<class ValueType>
class TrieIterator : public std::iterator<std::forward_iterator_tag, ValueType> {
    typedef TrieIterator<ValueType> t_TrieIterator;
    typedef TrieNode<ValueType> t_Node;

private:
    t_Node *mCur;

public:
    TrieIterator(t_Node *x, char letter) : mCur(x) {

    }

    TrieIterator &operator++() {
        char next = findNext(*mCur, mCur->getLetter());
        if (next == '\0') {
            mCur = up(mCur->getRoot(), mCur->getLetter());
            next = findNext(*mCur, mCur->getLetter() + 1);
            mCur = down(mCur->getChild(next), next);
        } else {
            mCur = down(mCur->getChild(next), CASE);
        }
        return *this;
    }

    TrieIterator operator++(int);

    bool operator==(const t_TrieIterator &rhs) const {
        return mCur->getKey() == rhs.mCur->getKey();
    }

    bool operator!=(const t_TrieIterator &rhs) const {
        return mCur->getKey() != rhs.mCur->getKey();
    }

    ValueType operator*() {
        return mCur->getValue();
    }

    ValueType *operator->() {
        return mCur->getValue();
    }

protected:

    char findNext(const t_Node &node, char letter) {
        for (char i = letter; i < CASE + ALPHABETS; ++i) {
            if (node.getChild(i)) {
                return i;
            }
        }
        return '\0';
    }

    t_Node *down(t_Node *node, char letter) {
        if (node->isWord()) {
            return node;
        }

        int nextLetter = findNext(*node, CASE);
        return down(node->getChild(nextLetter), CASE);
    }

    t_Node *up(t_Node *node, char letter) {
        char res = findNext(*node, letter + 1);
        if (res == '\0') {
            return up(node->getRoot(), node->getLetter());
        }
        return node;
    }

};
