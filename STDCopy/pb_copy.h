#pragma once

#include <iostream>
#include "gtest/gtest.h"

// general
template<class InIter, class OutIter>
typename std::enable_if< !std::is_fundamental<typename std::iterator_traits<InIter>::value_type >::value,
        OutIter>::type
pb_copy(InIter first, InIter last, OutIter d_first) {
    OutIter d_f_backup = d_first;
    while (first != last) {
        *d_first++ = *first++;
    }
    return d_f_backup;
};

// pointer
template<class InIter, class OutIter>
typename std::enable_if<std::is_fundamental<typename std::iterator_traits<InIter>::value_type >::value &&
        std::is_same<typename std::iterator_traits<InIter>::value_type *, InIter>::value,
        OutIter>::type
pb_copy(InIter first, InIter last, OutIter d_first) {
    typename std::iterator_traits<InIter>::value_type Type;

    OutIter d_f_backup = d_first;
    size_t size = std::distance(first, last);
    memmove(d_first, first, size * sizeof(Type));
    return d_f_backup;
};

// vector
template<class InIter, class OutIter>
typename std::enable_if<std::is_fundamental<typename std::iterator_traits<InIter>::value_type >::value &&
        std::is_same<InIter, typename std::vector<typename std::iterator_traits<InIter>::value_type>::iterator>::value,
        OutIter>::type
pb_copy(InIter first, InIter last, OutIter d_first) {
    typename std::iterator_traits<InIter>::value_type Type;

    OutIter d_f_backup = d_first;
    size_t size = std::distance(first, last);
    memmove(&*d_first, &*first, size * sizeof(Type));
    return d_f_backup;
};