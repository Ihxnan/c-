#ifndef ITEMDATABASE_INTERNAL_H_INCLUDED
#define ITEMDATABASE_INTERNAL_H_INCLUDED

// 物品结点
struct Item_Node
{
    struct Item data; // 物品数据
    struct Item_Node *prev; // 指向前一个结点的指针
    struct Item_Node *next; // 指向后一个结点的指针
};

// 数据库内部使用的全局变量的外部链接
extern struct Item *item_database; // 物品数据库

extern struct Item_Node *item_database_head;
    // 数据库头指针，指向链表第一个结点

extern struct Item_Node *item_database_tail;
    // 数据库尾指针，指向链表最后一个结点

extern int num_items; // 物品总数


#endif // ITEMDATABASE_INTERNAL_H_INCLUDED
