#ifndef ITEMDATABASE_INTERNAL_H_INCLUDED
#define ITEMDATABASE_INTERNAL_H_INCLUDED

// ��Ʒ���
struct Item_Node
{
    struct Item data; // ��Ʒ����
    struct Item_Node *prev; // ָ��ǰһ������ָ��
    struct Item_Node *next; // ָ���һ������ָ��
};

// ���ݿ��ڲ�ʹ�õ�ȫ�ֱ������ⲿ����
extern struct Item *item_database; // ��Ʒ���ݿ�

extern struct Item_Node *item_database_head;
    // ���ݿ�ͷָ�룬ָ�������һ�����

extern struct Item_Node *item_database_tail;
    // ���ݿ�βָ�룬ָ���������һ�����

extern int num_items; // ��Ʒ����


#endif // ITEMDATABASE_INTERNAL_H_INCLUDED
