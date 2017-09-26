#pragma once

#include <iterator>
#include <algorithm>
#include <iostream>
#include <cmath>

template<class RandomAccessIterator>
void RadixSortLSD(RandomAccessIterator first, RandomAccessIterator last) {
    size_t arraySize = (size_t) std::distance(first, last);
    int bucket[std::numeric_limits<typename std::iterator_traits<RandomAccessIterator>::value_type>::digits10];
    int digitPosition = 1;
    size_t maxVal = 0;

    RandomAccessIterator randomAccessIter = first;
    while (randomAccessIter != last) {
        if (*randomAccessIter > maxVal) maxVal = *randomAccessIter;
        ++randomAccessIter;
    }
    randomAccessIter = first;

    while (maxVal / digitPosition > 0) {
        int digitCount[10] = {0};

        for (size_t i = 0; i < arraySize; i++)
            digitCount[randomAccessIter[i] / digitPosition % 10]++;

        for (size_t i = 1; i < 10; i++)
            digitCount[i] += digitCount[i - 1];

        for (size_t i = arraySize - 1; i >= 0; i--) {
            bucket[--digitCount[randomAccessIter[i] / digitPosition % 10]] = randomAccessIter[i];
            if (i == 0) { break; }
        }

        for (size_t i = 0; i < arraySize; i++) {
            randomAccessIter[i] = bucket[i];
        }

        digitPosition *= 10;
    }
}

template<class RandomAccessIterator, class Type, class Compare>
struct pb_sort_impl {
    static void f(RandomAccessIterator first, RandomAccessIterator last, Compare compare) {
        std::sort(first, last, compare);
    };
};

template<typename RandomAccessIterator, class Compare>
struct pb_sort_impl<RandomAccessIterator, int, Compare> {
    static void f(RandomAccessIterator first, RandomAccessIterator last, Compare compare) {
        RadixSortLSD(first, last);
    };
};

template<class RandomAccessIterator, class Compare>
void pb_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    pb_sort_impl<
            RandomAccessIterator,
            typename std::iterator_traits<RandomAccessIterator>::value_type,
            Compare
    >::f(first, last, comp);
};
