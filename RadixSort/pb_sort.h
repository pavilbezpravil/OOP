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

template<class RandomAccessIterator, class Compare>
typename std::enable_if<!std::is_integral<typename std::iterator_traits<RandomAccessIterator>::value_type>::value, void>::type
pb_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    std::sort(first, last, comp);
};

template<class RandomAccessIterator, class Compare>
typename std::enable_if<std::is_integral<typename std::iterator_traits<RandomAccessIterator>::value_type>::value, void>::type
pb_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    RadixSortLSD(first, last);
};
