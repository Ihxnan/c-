#include "MySort.h"
#include <stdlib.h>

static unsigned char *FindSplitElement(
    unsigned char *low, unsigned char *high,
    size_t element_size,
    int (*compare_func)(const void *, const void *))
// 从数组中选择分割元素并返回指向该元素的指针。
// low指向数组的第一个元素，high指向数组的最后一个元素。
// 数组每个元素的尺寸为element_size个字节。
// 元素的大小关系由compare_func指向的比较函数判断。
// 该函数的返回值含义：正数代表大于，零代表等于，负数代表小于
{
    unsigned char* temp = (unsigned char*)malloc(element_size);
    memcpy(temp, low, element_size);

    for (;;)
    {
        while (low < high && compare_func(temp, high) < 0)
            high -= element_size;
        if (low >= high)
            break;

        memcpy(low, high, element_size);

        low += element_size;

        while (low < high && compare_func(temp, low) > 0)
            low += element_size;
        if (low >= high)
            break;

        memcpy(high, low, element_size);

        high -= element_size;
    }

    memcpy(high, temp, element_size);

    free(temp);

    return high;
}

void QuickSort(void *base,
               size_t num_elements, size_t element_size,
               int (*compare_func)(const void *, const void *))
// 对base指向的数组按照从小到大的顺序进行排序。
// 数组有num_elements个元素，
// 每个元素的尺寸为element_size个字节。
// 元素的大小关系由compare_func指向的比较函数判断。
// 该函数的返回值含义：正数代表大于，零代表等于，负数代表小于。
{
    size_t num_elements_before;
    unsigned char *middle;
    unsigned char *base_ub = (unsigned char *)base;

    if (num_elements <= 1)
        return;

    middle = FindSplitElement(base_ub, base_ub + (num_elements - 1) * element_size, element_size,
                              compare_func);

    num_elements_before = (middle - base_ub) / element_size;

    QuickSort(base, num_elements_before,
              element_size, compare_func);
    QuickSort(middle + element_size,
              num_elements - num_elements_before - 1,
              element_size, compare_func);
}
