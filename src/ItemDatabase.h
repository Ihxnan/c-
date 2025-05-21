#ifndef ITEMDATABASE_H_INCLUDED
#define ITEMDATABASE_H_INCLUDED

#include <stdlib.h>

// 物品名称最大长度
#define ITEM_NAME_MAX_LEN 64

// 排序方式
#define SORT_BY_NUMBER    0 // 按编号排序
#define SORT_BY_NAME      1 // 按名称排序
#define SORT_BY_QUANTITY  2 // 按数量排序
#define SORT_ASCENDING  0   // 按升序排序
#define SORT_DESCENDING 1   // 按降序排序

// 物品结构
struct Item
{
    // 编号
    int number;
    // 名称
    char name[ITEM_NAME_MAX_LEN];
    // 数量
    int quantity;
};

typedef struct ItemIterator // 迭代器类型(目前还不完整)
    *PItemIterator;         // 指向迭代器的指针类型

PItemIterator ItemDB_CreateItemIterator(void);
// 创建一个新的迭代器并返回指向它的指针

void ItemDB_DeleteItemIterator(const PItemIterator p_iter);
// 删除p_iter指向的迭代器的存储空间

void ItemDB_GetFirstItemIterator(PItemIterator p_iter);
// 获取指向第一一个物品的迭代器, 保存到p_iter指向的存储空间中

void ItemDB_GetNextItemIterator(PItemIterator p_iter);
// 将p_iter指向的迭代器改为指向下一个物品的迭代器

int ItemDB_IsItemIteratorValid(const PItemIterator p_iter);
// 如果p_iter指向的迭代器有效则返回1,否则返回0

void ItemDB_FindItem(int number, PItemIterator p_iter);
// 搜索编号为number的物品，
// 将指向该该物品的迭代器存放到p_iter指向的空间中。
// 如果该物品不存在则存储一个无效迭代器

int ItemDB_AddItem(const struct Item *p_item);
// 把p_item指向的物品加入数据库中, 成功返回1, 否则返回0

void ItemDB_DeleteItem(PItemIterator p_iter);
// 删除p_iter指向的迭代器对应的物品

struct Item *ItemDB_GetItemPointer(const PItemIterator p_iter);
// 返回p_iter指向的迭代器对应的物品的指针
// 如果物品不存在则返回NULL

void ItemDB_ClearDatabase(void);
// 清空数据库

int ItemDB_GetNumItems(void);

int ItemDB_SaveToFile(const char *file_name);
// 把数据库数据保存到文件名为file_name指向的字符串的文件中
// 成功返回1， 否则返回0

int ItemDB_LoadFromFile(const char *file_name);
// 从文件名为file_name指向的字符串的文件中载入数据库数据
// 成功返回1， 否则返回0

void ItemDB_Sort(int sort_method, int sort_dir);
//   对数据库中的物品进行排序。
//   sort_method是排序方法，可以取下列值之一：
//   SORT_BY_NUMBER, SORT_BY_NAME, SORT_BY_QUANTITY
//   sort_dir是排序方向，可以取下列值之一：
//   SORT_ASCENDING, SORT_DESCENDING

#endif // ITEMDATABASE_H_INCLUDED
