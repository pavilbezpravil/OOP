#pragma once

#include <algorithm>

template<class T>
struct deleter {
    void operator()(T *p) {
        if (p) {
            delete p;
        }
    }
};

template<class Type, class TDeleter = deleter<Type>>
class UniquePTR {
    typedef UniquePTR<Type, TDeleter> t_UniquePTR;
    typedef TDeleter t_Deleter;

    t_Deleter _del;
    Type *mPtr;

public: // Constructors and destructor.
    UniquePTR();
    UniquePTR(Type *pObject);
    UniquePTR(t_UniquePTR &&uniquePTR); // Move constructor.
    ~UniquePTR();

public: // Assignment.
    UniquePTR &operator=(t_UniquePTR &&uniquePTR);
    UniquePTR &operator=(Type *pObject);

public: // Observers.
    Type &operator*() const; // Dereference the stored pointer.
    Type *operator->() const; // Return the stored pointer.
    Type *get() const; // Return the stored pointer.
    TDeleter &get_deleter(); // Return a reference to the stored deleter.
    operator bool() const; // Return false if the stored pointer is null.
public: // Modifiers.
    void release(); // Release ownership of any stored pointer.
    void reset(Type *pObject = nullptr); // Replace the stored pointer.
    void swap(t_UniquePTR &uniquePTR); // Exchange the pointer with another object.
private: // Disable copy from lvalue.
    UniquePTR(const t_UniquePTR &) = delete;
    t_UniquePTR &operator=(const t_UniquePTR &) = delete;
};

template<class Type, class TDeleter>
UniquePTR<Type, TDeleter>::UniquePTR() : mPtr(nullptr) {

}

template<class Type, class TDeleter>
UniquePTR<Type, TDeleter>::UniquePTR(Type *pObject) : mPtr(pObject) {

}

template<class Type, class TDeleter>
UniquePTR<Type, TDeleter>::UniquePTR(UniquePTR::t_UniquePTR &&uniquePTR) {
    // TODO: norm?
    *this = uniquePTR;
}

template<class Type, class TDeleter>
UniquePTR<Type, TDeleter>::~UniquePTR() {
    reset(nullptr);
}

template<class Type, class TDeleter>
UniquePTR<Type, TDeleter> &UniquePTR<Type, TDeleter>::operator=(UniquePTR::t_UniquePTR &&uniquePTR) {
    mPtr = uniquePTR.get();
    uniquePTR.mPtr = nullptr;
    return *this;
}

template<class Type, class TDeleter>
UniquePTR<Type, TDeleter> &UniquePTR<Type, TDeleter>::operator=(Type *pObject) {
    release();
    mPtr = pObject;
    return *this;
}

template<class Type, class TDeleter>
Type &UniquePTR<Type, TDeleter>::operator*() const {
    return *mPtr;
}

template<class Type, class TDeleter>
Type *UniquePTR<Type, TDeleter>::operator->() const {
    return mPtr;
}

template<class Type, class TDeleter>
Type *UniquePTR<Type, TDeleter>::get() const {
    return mPtr;
}

template<class Type, class TDeleter>
TDeleter &UniquePTR<Type, TDeleter>::get_deleter() {
    return _del;
}

template<class Type, class TDeleter>
UniquePTR<Type, TDeleter>::operator bool() const {
    return mPtr != nullptr;
}

// TODO:
template<class Type, class TDeleter>
void UniquePTR<Type, TDeleter>::release() {
    _del(mPtr);
    mPtr = nullptr;
}

template<class Type, class TDeleter>
void UniquePTR<Type, TDeleter>::reset(Type *pObject) {
    _del(mPtr);
    mPtr = pObject;
}

template<class Type, class TDeleter>
void UniquePTR<Type, TDeleter>::swap(UniquePTR::t_UniquePTR &uniquePTR) {
    std::swap(mPtr, uniquePTR.mPtr);
}
