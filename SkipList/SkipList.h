#pragma once

#include <functional>
#include <unordered_map>

template <typename Key,
        typename Value,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<std::pair<const Key,Value> > >
class skip_list {
    // ...
public:
    typedef Value *                     iterator;
    typedef const Value *               const_iterator;
    typedef std::pair<const Key, Value> value_type;

    skip_list();
    explicit skip_list(const Compare &comp, const Alloc &a = Alloc());
    skip_list(const skip_list &another);

    skip_list &operator=(const skip_list &another);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    bool empty() const;
    size_t size() const;

    Value &operator[](const Key &key);
    Value &at(const Key &key);
    const Value &at(const Key &key);

    std::pair<iterator, bool> insert(const value_type &);

    void erase(iterator position);
    size_type erase(const Key &key);
    void erase(iterator first, iterator last);

    void swap(skip_list &another);
    void clear();

    iterator find(const Key &key);
    const_iterator find(const Key &key) const;
};

template <typename K, typename V, typename C, typename A>
inline bool operator==(const skip_list<K,V,C,A> &x, const skip_list<K,V,C,A> &y) {
    // ....
}

template <typename K, typename V, typename C, typename A>
inline bool operator!=(const skip_list<K,V,C,A> &x, const skip_list<K,V,C,A> &y) {
    // ....
}
