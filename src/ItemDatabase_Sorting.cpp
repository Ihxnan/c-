#include <string.h>

#include "ItemDatabase.h"
#include "MySort.h"
#include "ItemDatabase_Internal.h"

static int g_sort_method, g_sort_dir;

static int CompareItems(const void *p, const void *q)
// 比较函数
// 根据sort_method 和 sort_dir 比较 *p 和 *q 的大小
// 正数代表大于，零代表等于，负数代表小于
// 参数说明：
// sort_method: SORT_BY_NUMBER -> 根据编号比较, SORT_BY_NAME -> 根据名称比较, SORT_BY_QUANTITY -> 根据数量比较
// sort_dir: SORT_ASCENDING -> 升序, SORT_DESCENDING -> 降序
{

    const struct Item *p_item = (const struct Item *)p;
    const struct Item *q_item = (const struct Item *)q;

    int result = 0;

    switch (g_sort_method)
    {
        case SORT_BY_NUMBER:
            if (p_item->number < q_item->number)
                result = -1;
            else if (p_item->number > q_item->number)
                result = 1;
            break;
        case SORT_BY_NAME:
            result = strcmp(p_item->name, q_item->name);
            break;
        case SORT_BY_QUANTITY:
            if (p_item->quantity < q_item->quantity)
                result = -1;
            else if (p_item->quantity > q_item->quantity)
                result = 1;
            break;
    }

    return g_sort_dir == SORT_ASCENDING ? result : -result;
}

void ItemDB_Sort(int sort_method, int sort_dir)
{
    g_sort_method = sort_method;
    g_sort_dir = sort_dir;
    struct Item* arr = (struct Item*)malloc(sizeof(struct Item) * num_items);
    int i;
    struct Item_Node* p;
    for (p = item_database_head, i = 0; p != NULL; p = p->next)
        arr[i++] = p->data;

    QuickSort(arr, ItemDB_GetNumItems(), sizeof(struct Item), CompareItems);

    for (p = item_database_head, i = 0; p != NULL; p = p->next)
        p->data = arr[i++];

    free(arr);
}
