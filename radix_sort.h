#pragma once

#include <iterator>
#include <algorithm>

template<class T>
int getMax(T arr[], size_t n) {
    int mx = arr[0];
    for (size_t i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

template<class RandomAccessIterator, class Compare>
void countSort(RandomAccessIterator iter, size_t n, int exp) {
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[(iter[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[(iter[i] / exp) % 10] - 1] = iter[i];
        count[(iter[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        iter[i] = output[i];
}

template<class RandomAccessIterator>
size_t getSize(RandomAccessIterator first, RandomAccessIterator last) {
    size_t size = 0;
    while(first != last) {
        ++size;
        ++first;
    }
    return size;
}

template<class RandomAccessIterator, class Compare>
void radixsort(RandomAccessIterator first, RandomAccessIterator last, Compare compare) {
    size_t size = getSize(first, last);
    int m = getMax(first, size);

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(first, size, exp);
}

template<class RandomAccessIterator, class Type, class Compare>
struct radix_sort_impl {
    static void f(RandomAccessIterator first, RandomAccessIterator last, Compare compare) {
        std::sort(first, last, compare);
    };
};

template<typename RandomAccessIterator, class Compare>
struct radix_sort_impl<RandomAccessIterator, int, Compare> {
    static void f(RandomAccessIterator first, RandomAccessIterator last, Compare compare) {
        // FIXME
        std::sort(first, last, compare);
    };
};

template<class RandomAccessIterator, class Compare>
void radix_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    radix_sort_impl<
            RandomAccessIterator,
            typename std::iterator_traits<RandomAccessIterator>::value_type,
            Compare
    >::f(first, last, comp);
};
