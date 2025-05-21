#ifndef ITEMDATABASE_H_INCLUDED
#define ITEMDATABASE_H_INCLUDED

#include <stdlib.h>

// ��Ʒ������󳤶�
#define ITEM_NAME_MAX_LEN 64

// ����ʽ
#define SORT_BY_NUMBER    0 // ���������
#define SORT_BY_NAME      1 // ����������
#define SORT_BY_QUANTITY  2 // ����������
#define SORT_ASCENDING  0   // ����������
#define SORT_DESCENDING 1   // ����������

// ��Ʒ�ṹ
struct Item
{
    // ���
    int number;
    // ����
    char name[ITEM_NAME_MAX_LEN];
    // ����
    int quantity;
};

typedef struct ItemIterator // ����������(Ŀǰ��������)
    *PItemIterator;         // ָ���������ָ������

PItemIterator ItemDB_CreateItemIterator(void);
// ����һ���µĵ�����������ָ������ָ��

void ItemDB_DeleteItemIterator(const PItemIterator p_iter);
// ɾ��p_iterָ��ĵ������Ĵ洢�ռ�

void ItemDB_GetFirstItemIterator(PItemIterator p_iter);
// ��ȡָ���һһ����Ʒ�ĵ�����, ���浽p_iterָ��Ĵ洢�ռ���

void ItemDB_GetNextItemIterator(PItemIterator p_iter);
// ��p_iterָ��ĵ�������Ϊָ����һ����Ʒ�ĵ�����

int ItemDB_IsItemIteratorValid(const PItemIterator p_iter);
// ���p_iterָ��ĵ�������Ч�򷵻�1,���򷵻�0

void ItemDB_FindItem(int number, PItemIterator p_iter);
// �������Ϊnumber����Ʒ��
// ��ָ��ø���Ʒ�ĵ�������ŵ�p_iterָ��Ŀռ��С�
// �������Ʒ��������洢һ����Ч������

int ItemDB_AddItem(const struct Item *p_item);
// ��p_itemָ�����Ʒ�������ݿ���, �ɹ�����1, ���򷵻�0

void ItemDB_DeleteItem(PItemIterator p_iter);
// ɾ��p_iterָ��ĵ�������Ӧ����Ʒ

struct Item *ItemDB_GetItemPointer(const PItemIterator p_iter);
// ����p_iterָ��ĵ�������Ӧ����Ʒ��ָ��
// �����Ʒ�������򷵻�NULL

void ItemDB_ClearDatabase(void);
// ������ݿ�

int ItemDB_GetNumItems(void);

int ItemDB_SaveToFile(const char *file_name);
// �����ݿ����ݱ��浽�ļ���Ϊfile_nameָ����ַ������ļ���
// �ɹ�����1�� ���򷵻�0

int ItemDB_LoadFromFile(const char *file_name);
// ���ļ���Ϊfile_nameָ����ַ������ļ����������ݿ�����
// �ɹ�����1�� ���򷵻�0

void ItemDB_Sort(int sort_method, int sort_dir);
//   �����ݿ��е���Ʒ��������
//   sort_method�����򷽷�������ȡ����ֵ֮һ��
//   SORT_BY_NUMBER, SORT_BY_NAME, SORT_BY_QUANTITY
//   sort_dir�������򣬿���ȡ����ֵ֮һ��
//   SORT_ASCENDING, SORT_DESCENDING

#endif // ITEMDATABASE_H_INCLUDED
