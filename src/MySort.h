#ifndef MYSORT_H_INCLUDED
#define MYSORT_H_INCLUDED

#include <string.h>

void QuickSort(void *base,
    size_t num_elements, size_t element_size,
    int (*compare_func)(const void *, const void *));
// 对base指向的数组按照从小到大的顺序进行排序。
// 数组有num_elements个元素，
// 每个元素的尺寸为element_size个字节。
// 元素的大小关系由compare_func指向的比较函数判断。
// 该函数的返回值含义：正数代表大于，零代表等于，负数代表小于。

#endif // MYSORT_H_INCLUDED
