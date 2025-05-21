#include <stdio.h>
#include <stdlib.h>

#include "ItemDatabase.h"
#include "ItemDatabase_Internal.h"

struct Item_Node *item_database_head = NULL;
// 数据库头指针， 指向链表第一个结点

struct Item_Node *item_database_tail = NULL;
// 数据库尾指针， 指向链表最后一个结点

// 实际物品数量
int num_items = 0;

// 迭代器类型的完整定义
struct ItemIterator
{
    struct Item_Node *p; // 指向物品结点的指针
};

PItemIterator ItemDB_CreateItemIterator(void)
// 创建一个新的迭代器并返回指向它的指针
{
    return (PItemIterator)
        malloc(sizeof(struct ItemIterator));
}

void ItemDB_DeleteItemIterator(const PItemIterator p_iter)
// 删除p_iter指向的迭代器的存储空间
{
    free(p_iter);
}

void ItemDB_GetFirstItemIterator(PItemIterator p_iter)
// 获取指向下一个物品的迭代器, 保存到p_iter指向的存储空间中
{
    p_iter->p = item_database_head;
}

void ItemDB_GetNextItemIterator(PItemIterator p_iter)
// 将p_iter指向的迭代器改为指向下一个物品的迭代器
{
    p_iter->p = p_iter->p->next;
}

int ItemDB_IsItemIteratorValid(const PItemIterator p_iter)
// 如果p_iter指向的迭代器有效则返回1,否则返回0
{
    return p_iter->p != NULL;
}

void ItemDB_FindItem(int number, PItemIterator p_iter)
// 搜索编号为number的物品，
// 将指向该该物品的迭代器存放到p_iter指向的空间中。
// 如果该物品不存在则存储一个无效迭代器
{
    struct Item_Node *p;
    for (p = item_database_head; p != NULL; p = p->next)
    {
        if (p->data.number == number)
            break;
    }
    p_iter->p = p;
}

int ItemDB_AddItem(const struct Item *p_item)
// 把p_item指向的物品加入数据库中， 成功返回1， 否则返回0
{
    struct Item_Node *new_item = (struct Item_Node *)malloc(sizeof(struct Item_Node));

    new_item->data = *p_item;

    new_item->prev = item_database_tail;
    new_item->next = NULL;

    item_database_head ? item_database_tail->next = new_item : item_database_head = new_item;

    item_database_tail = new_item;

    ++num_items;

    return 1;
}

void ItemDB_DeleteItem(const PItemIterator p_iter)
// 删除p_iter指向的迭代器对应的物品
{
    p_iter->p == item_database_head ? item_database_head = p_iter->p->next : 
        p_iter->p->prev->next = p_iter->p->next;

    p_iter->p == item_database_tail ? item_database_tail = p_iter->p->prev : 
        p_iter->p->next->prev = p_iter->p->prev;

    free(p_iter->p);

    --num_items;
}

struct Item *ItemDB_GetItemPointer(const PItemIterator p_iter)
// 返回p_iter指向的迭代器对应的物品的指针
// 如果物品不存在则返回NULL
{
    if (!ItemDB_IsItemIteratorValid(p_iter))
        return NULL;
    return &p_iter->p->data;
}

void ItemDB_ClearDatabase(void)
{
    struct Item_Node *p, *p_temp;
    num_items = 0;
    for (p = item_database_head; p != NULL; p = p_temp)
    {
        p_temp = p->next;
        free(p);
    }
    item_database_head = NULL;
    item_database_tail = NULL;
}

int ItemDB_GetNumItems(void)
{
    return num_items;
}
