#include <iostream>
#include "gtest/gtest.h"

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

template<typename T>
T pb_copy(T f, T l, T d_f) {
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

template<typename Iter>
void printArr(Iter first, Iter last) {
    while (first != last) {
        std::cout << *first++ << std::endl;
    }
}


TEST(SuiteName, 10) {
    int a[] = {1, 2, 3, 4};
    int b[] = {0, 0, 0, 0};

    pb_copy(a, a + 4, b);
    for (int i = 0; i < 4; ++i) {
        ASSERT_EQ(b[i], a[i]);
    }
}

TEST(SuiteName, 11) {
    char a[] = "abcd";
    char b[] = "aaaa";

    pb_copy(a, a + 5, b);
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(b[i], a[i]);
    }
}

TEST(SuiteName, 20) {
    std::vector<int> src = {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> dst = {0, 0, 0, 0, 0, 0, 0};

    pb_copy_v<int>(src.begin(), src.end(), dst.begin());
    for (int i = 0; i < src.size(); ++i) {
        ASSERT_EQ(dst[i], src[i]);
    }
}

TEST(SuiteName, 21) {
    std::vector<std::string> src = {"aa", "bb", "cc"};
    std::vector<std::string> dst = {"00", "00", "00"};

//    pb_copy_v(src.begin(), src.end(), dst.begin());
    for (int i = 0; i < src.size(); ++i) {
        ASSERT_EQ(dst[i], src[i]);
    }
}