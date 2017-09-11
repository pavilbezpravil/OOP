#pragma once

#include <iostream>
#include "gtest/gtest.h"

#if 0
template<typename T>
T *pb_copy(T *f, T *l, T *d_f) {
    if (std::is_fundamental<T>::value) {
        return (T *) memmove(d_f, f,
                             (l - f) * sizeof(T));
    }
    T *d_f_backup = d_f;
    while (true) {
        if (f != l) { return d_f_backup; }
        *d_f++ = *f++;
    }
}

template<typename Iterator>
Iterator pb_copy(Iterator f, Iterator l, Iterator d_f) {
//    if (std::is_fundamental<Iterator>::value) {
//        return (Iterator *) memmove(d_f, f,
//                             (l - f) * sizeof(Iterator));
//    }
    Iterator d_f_backup = d_f;
    while (true) {
        if (f != l) { return d_f_backup; }
        *d_f++ = *f++;
    }
}

template<typename T>
typename std::vector<T>::iterator pb_copy_v(typename std::vector<T>::iterator f, typename std::vector<T>::iterator l,
                                            typename std::vector<T>::iterator d_f) {
//    if (std::is_fundamental<T>::value) {
//        memmove((void *) d_f, (void *) f,
//                (l - f) * sizeof(T));
//        return d_f;
//    }
//
//    T *d_f_backup = d_f;
//    while (true) {
//        if (f != l) { return d_f_backup; }
//        *d_f++ = *f++;
//    }
    typename std::vector<T>::iterator d_f_backup = d_f;
    while (true) {
        if (f != l) { return d_f_backup; }
        *d_f++ = *f++;
    }
}
#endif

template<typename Iter>
void printArr(Iter first, Iter last) {
    while (first != last) {
        std::cout << *first++ << std::endl;
    }
}

// ------------ implementation ----------------

template<class Iter, class IterRepeat, class Type>
struct pbt_copy_impl {
    static void f(Iter first, Iter last, Iter d_first);
};

template<class Iter, class IterRepeat, class Type>
void pbt_copy_impl<Iter, IterRepeat, Type>::f(Iter first, Iter last, Iter d_first) {
    Iter d_f_backup = d_first;
    while (true) {
        if (first == last) { return; }
        *d_first++ = *first++;
    }
}


// case : general
//template<class Iter, class IterRepeat, class Type>
//struct pbt_copy_impl {
//    static void f(Iter first, Iter last, Iter d_first) {
//        Iter d_f_backup = d_first;
//        while (true) {
//            if (first == last) { return; }
//            *d_first++ = *first++;
//        }
//    };
//};

// case : point
template<class Iter, class Type>
struct pbt_copy_impl<Iter, Type *, Type> {
    static void f(Iter first, Iter last, Iter d_first) {
        if (std::is_fundamental<Type>::value) {
            memmove(d_first, first, (last - first) * sizeof(Type));
            return;
        }
        while (true) {
            if (first == last) { return; }
            *d_first++ = *first++;
        }
    };
};

// case : vector
template<class Iter, class Type>
struct pbt_copy_impl<Iter, typename std::vector<Type>::iterator, Type> {
    static void f(Iter first, Iter last, Iter d_first) {
//        pbt_copy_impl<
//                Iter,
//                Type *,
//                Type
//        >::f(first, last, d_first);
        Iter d_f_backup = d_first;
        while (true) {
            if (first == last) { return; }
            *d_first++ = *first++;
        }
    };
};
// ------------ implementation END ----------------

template<class Iter>
void pbt_copy(Iter first, Iter last, Iter d_first) {
    pbt_copy_impl<
            Iter,
            Iter,
            typename std::iterator_traits<Iter>::value_type
    >::f(first, last, d_first);
};
