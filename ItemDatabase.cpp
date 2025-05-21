#include <stdio.h>
#include <stdlib.h>

#include "ItemDatabase.h"
#include "ItemDatabase_Internal.h"

struct Item_Node *item_database_head = NULL;
// ���ݿ�ͷָ�룬 ָ�������һ�����

struct Item_Node *item_database_tail = NULL;
// ���ݿ�βָ�룬 ָ���������һ�����

// ʵ����Ʒ����
int num_items = 0;

// ���������͵���������
struct ItemIterator
{
    struct Item_Node *p; // ָ����Ʒ����ָ��
};

PItemIterator ItemDB_CreateItemIterator(void)
// ����һ���µĵ�����������ָ������ָ��
{
    return (PItemIterator)
        malloc(sizeof(struct ItemIterator));
}

void ItemDB_DeleteItemIterator(const PItemIterator p_iter)
// ɾ��p_iterָ��ĵ������Ĵ洢�ռ�
{
    free(p_iter);
}

void ItemDB_GetFirstItemIterator(PItemIterator p_iter)
// ��ȡָ����һ����Ʒ�ĵ�����, ���浽p_iterָ��Ĵ洢�ռ���
{
    p_iter->p = item_database_head;
}

void ItemDB_GetNextItemIterator(PItemIterator p_iter)
// ��p_iterָ��ĵ�������Ϊָ����һ����Ʒ�ĵ�����
{
    p_iter->p = p_iter->p->next;
}

int ItemDB_IsItemIteratorValid(const PItemIterator p_iter)
// ���p_iterָ��ĵ�������Ч�򷵻�1,���򷵻�0
{
    return p_iter->p != NULL;
}

void ItemDB_FindItem(int number, PItemIterator p_iter)
// �������Ϊnumber����Ʒ��
// ��ָ��ø���Ʒ�ĵ�������ŵ�p_iterָ��Ŀռ��С�
// �������Ʒ��������洢һ����Ч������
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
// ��p_itemָ�����Ʒ�������ݿ��У� �ɹ�����1�� ���򷵻�0
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
// ɾ��p_iterָ��ĵ�������Ӧ����Ʒ
{
    p_iter->p == item_database_head ? item_database_head = p_iter->p->next : 
        p_iter->p->prev->next = p_iter->p->next;

    p_iter->p == item_database_tail ? item_database_tail = p_iter->p->prev : 
        p_iter->p->next->prev = p_iter->p->prev;

    free(p_iter->p);

    --num_items;
}

struct Item *ItemDB_GetItemPointer(const PItemIterator p_iter)
// ����p_iterָ��ĵ�������Ӧ����Ʒ��ָ��
// �����Ʒ�������򷵻�NULL
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
