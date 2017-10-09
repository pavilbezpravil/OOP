#pragma once

#include <vector>
#include <cstring>
#include <string>

#define ALPHABETS 26
#define CASE 'a'

template <typename ValueType>
class TrieNode {
    typedef TrieNode<ValueType> t_Node;
private:

    t_Node *mRoot;
//    char mLetter;
    t_Node *mChild[ALPHABETS];
    bool mIsEndOfWord;
    std::string mWord;

    ValueType mValue;
    //    std::vector<int> occurrences;

public:

//    TrieNode(const char *word, TrieNode *root = nullptr, bool isEndOfWord = false) :
//            mRoot(root), mIsEndOfWord(isEndOfWord), mWord(word) {
//        memset(mChild, 0, ALPHABETS);
//    }

    TrieNode(const std::string &word, const ValueType &value, TrieNode *root = nullptr, bool isEndOfWord = false) :
            mRoot(root), mIsEndOfWord(isEndOfWord), mWord(word), mValue(value) {
        for (int i = 0; i < ALPHABETS; ++i) {
            mChild[i] = nullptr;
        }
    }

    ValueType &getValue() {
        return mValue;
    }

    const ValueType &getValue() const {
        return mValue;
    }

    t_Node *getChild(char letter) {
        return mChild[letter - CASE];
    }

    t_Node *getChild(char letter) const {
        return mChild[letter - CASE];
    }

    t_Node *getRoot() const {
        return mRoot;
    }

    t_Node *&operator[] (char letter) {
        return mChild[letter - CASE];
    }

    char getLetter() const {
        if (mWord.size() == 0) {
            return 'a';
        }
        return mWord.back();
    }

    const std::string &getKey() const {
        return mWord;
    }

    void setIsWord(bool isWord) {
        mIsEndOfWord = isWord;
    }

    bool isWord() const {
        return mIsEndOfWord;
    }

    int getChildSize() {
        return ALPHABETS;
    }

};
