#pragma once

#include <iostream>
#include "gtest/gtest.h"

// ------------ implementation ----------------

// case : general
template<class Iter, class IterRepeat, class Type>
struct pbt_copy_impl {
    static void f(Iter first, Iter last, Iter d_first) {
        Iter d_f_backup = d_first;
        while (first != last) {
            *d_first++ = *first++;
        }
    };
};

// case : pointer
template<class Iter, class Type>
struct pbt_copy_impl<Iter, Type *, Type> {
    static void f(Iter first, Iter last, Iter d_first) {
        if (std::is_fundamental<Type>::value) {
            memmove(d_first, first, (last - first) * sizeof(Type));
            return;
        }
        while (first!= last) {
            *d_first++ = *first++;
        }
    };
};

// case : vector
template<class Iter, class Type>
struct pbt_copy_impl<Iter, typename std::vector<Type>::iterator, Type> {
    static void f(Iter first, Iter last, Iter d_first) {
        Type *b = &*first;
        Type *e = &*last;
        Type *d_b = &*d_first;
//        size_t size = std::distance(first, last);
        // FIXME: dont work
//        pbt_copy_impl<
//                Iter,
//                Type *,
//                Type
//        >::f(b, e, d_b);
        if (std::is_fundamental<Type>::value) {
            memmove(d_b, b, (e - b) * sizeof(Type));
//            memmove(d_b, b, size * sizeof(Type));
            return;
        }
        while (first != last) {
            *first++ = *last++;
        }
    };// SFINIE
};
// ------------ implementation END ----------------

template<class Iter>
void pb_copy(Iter first, Iter last, Iter d_first) {
    pbt_copy_impl<
            Iter,
            Iter,
            typename std::iterator_traits<Iter>::value_type
    >::f(first, last, d_first);
};
