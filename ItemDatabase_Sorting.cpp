#include <string.h>

#include "ItemDatabase.h"
#include "MySort.h"
#include "ItemDatabase_Internal.h"

static int g_sort_method, g_sort_dir;

static int CompareItems(const void *p, const void *q)
// �ȽϺ���
// ����sort_method �� sort_dir �Ƚ� *p �� *q �Ĵ�С
// ����������ڣ��������ڣ���������С��
// ����˵����
// sort_method: SORT_BY_NUMBER -> ���ݱ�űȽ�, SORT_BY_NAME -> �������ƱȽ�, SORT_BY_QUANTITY -> ���������Ƚ�
// sort_dir: SORT_ASCENDING -> ����, SORT_DESCENDING -> ����
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
