#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ItemDatabase.h"

// ������Ʒ
void UI_AddItem(void)
{
    struct Item temp_item;
    PItemIterator it = ItemDB_CreateItemIterator();

    // ��������Ʒ���
    printf("����������Ʒ��ţ�");
    scanf("%d", &temp_item.number);

    // �����Ʒ����Ƿ��Ѿ�����
    // �����򷵻ش�����Ϣ������
    ItemDB_FindItem(temp_item.number, it);
    if (ItemDB_IsItemIteratorValid(it))
        printf("��Ʒ�Ѿ�����\n");
    else
    {
        // ��������Ʒ����
        printf("����������Ʒ���ƣ�");
        scanf("%s", temp_item.name);

        // ��������Ʒ����
        printf("����������Ʒ������");
        scanf("%d", &temp_item.quantity);

        // ������Ʒ�������ݿ���
        if (!ItemDB_AddItem(&temp_item))
            printf("��Ʒ���ʧ��!\n");
        else
            printf("��ӳɹ�!\n");
    }

    ItemDB_DeleteItemIterator(it);
}

// ɾ����Ʒ
void UI_DeleteItem(void)
{
    // Ҫɾ������Ʒ�ı��
    int delete_number = 0;
    PItemIterator it = ItemDB_CreateItemIterator();

    // ����Ҫɾ����Ʒ���
    printf("������Ҫɾ����Ʒ��ţ�");
    scanf("%d", &delete_number);

    // �����Ʒ�±�
    ItemDB_FindItem(delete_number, it);
    if (!ItemDB_IsItemIteratorValid(it))
    {
        printf("ɾ����Ʒ������\n");
    }
    else
    {
        ItemDB_DeleteItem(it);
        printf("ɾ���ɹ�\n");
    }
    ItemDB_DeleteItemIterator(it);
}

// ������Ʒ
void UI_UpdateItem(void)
{
    int number;
    struct Item *p_item;
    PItemIterator it = ItemDB_CreateItemIterator();

    printf("������Ҫ������Ʒ�ı�ţ�");
    scanf("%d", &number);

    ItemDB_FindItem(number, it);

    if (!ItemDB_IsItemIteratorValid(it))
    {
        printf("��Ʒ������!\n");
    }
    else
    {
        p_item = ItemDB_GetItemPointer(it);

        // ��������Ʒ����
        printf("����������Ʒ���ƣ�");
        scanf("%s", p_item->name);

        // ��������Ʒ����
        printf("����������Ʒ������");
        scanf("%d", &p_item->quantity);

        printf("��Ʒ���³ɹ���\n");
    }
    ItemDB_DeleteItemIterator(it);
}

// ������Ʒ
void UI_SearchItem(void)
{
    int number;
    PItemIterator p_iter;
    struct Item *p_item;

    p_iter = ItemDB_CreateItemIterator();
    // ������Ʒ���
    printf("��������Ʒ��ţ�");
    scanf("%d", &number);

    // ������Ӧ��ŵ���Ʒ
    ItemDB_FindItem(number, p_iter);

    // �����Ʒ����������ʾ�����ڲ�����
    if (!ItemDB_IsItemIteratorValid(p_iter))
    {
        printf("��Ʒ������!\n");
    }
    else
    {
        // ��ȡָ����Ʒ��ָ��
        p_item = ItemDB_GetItemPointer(p_iter);

        printf("��Ʒ�����ƣ�%s\n��Ʒ��������%d\n", p_item->name, p_item->quantity);
    }
    ItemDB_DeleteItemIterator(p_iter);
}

// ������ݿ�
void UI_PrintDatabase(void)
{
    int n;
    struct Item *p;
    PItemIterator p_iter;

    // ��ȡ����ʾ��Ʒ����
    n = ItemDB_GetNumItems();
    printf("��Ʒ��������%d\n", n);

    // �����Ʒ����Ϊ0�򷵻�
    if (n == 0)
        return;

    p_iter = ItemDB_CreateItemIterator();
    // ����������Ʒ����ʾ��Ʒ��Ϣ
    printf("   ���            ����            ����\n");
    for (ItemDB_GetFirstItemIterator(p_iter);
         ItemDB_IsItemIteratorValid(p_iter);
         ItemDB_GetNextItemIterator(p_iter))
    {
        p = ItemDB_GetItemPointer(p_iter);
        printf("%10d %20s %10d\n", p->number, p->name, p->quantity);
    }
    ItemDB_DeleteItemIterator(p_iter);
}

// ������ݿ�
void UI_ClearDatabase(void)
{
    ItemDB_ClearDatabase();
    printf("ɾ���ɹ�\n");
}

// �����ݿ����ݱ��浽�ļ���
void UI_SaveDatabaseToFile(void)
{
    char file_name[1024];
    // �����ļ���
    printf("������Ҫ������ļ�����");
    scanf("%s", file_name);

    // �����ݿⱣ�浽���ļ���
    if (ItemDB_SaveToFile(file_name))
        printf("����ɹ���\n");
    else
        printf("����ʧ�ܣ�\n");
}

// ���ļ����������ݿ�����
void UI_LoadDatabaseFromFile(void)
{
    char file_name[1024];
    // �����ļ���
    printf("������Ҫ������ļ�����");
    scanf("%s", file_name);

    // �����ݿⱣ�浽���ļ���
    if (ItemDB_LoadFromFile(file_name))
        printf("����ɹ���\n");
    else
        printf("����ʧ�ܣ�\n");
}

void UI_SortDatabase(void)
{
    int sort_method, sort_dir;
    printf("��ѡ������ʽ��\n");
    printf("\t\t0->���������\n");
    printf("\t\t1->����������\n");
    printf("\t\t2->����������\n");
    scanf("%d", &sort_method);
    if (sort_method > 2 || sort_method < 0)
    {
        printf("����Ƿ�������\n");
        return;
    }
    printf("������������\n");
    printf("\t\t0->����������\n");
    printf("\t\t1->����������\n");
    scanf("%d", &sort_dir);
    if (sort_dir > 1 || sort_dir < 0)
    {
        printf("����Ƿ�������\n");
        return;
    }
    ItemDB_Sort(sort_method, sort_dir);
    printf("����ɹ�\n");
}

 #if _DEBUG

void CreatTestDatabase(void)
{
    struct Item temp_item;
    for (int i = 0; i < 20; ++i)
    {
        temp_item.number = i + 1;
        temp_item.quantity = rand() % 1000 + 1;
        for (int k = 0; k <5; ++k)
        {
            temp_item.name[k] = rand() % 26 + 'A';
        }
        temp_item.name[5] = '\0';
        ItemDB_AddItem(&temp_item);
    }
}

#endif // _DEBUG

// �˵���ṹ
struct {
    int number; // ���
    const char* name; // ����
    void (*f) (void); // ָ��������ָ��
} main_menu[] // ���˵�
={
    {0, "�˳�", NULL},
    {1, "������Ŀ",     UI_AddItem},
    {2, "ɾ����Ŀ",     UI_DeleteItem},
    {3, "������Ŀ",     UI_SearchItem},
    {4, "������Ŀ",     UI_UpdateItem},
    {5, "���������Ŀ", UI_PrintDatabase},
    {6, "���������Ŀ", UI_ClearDatabase},
    {7, "���浽�ļ�",   UI_SaveDatabaseToFile},
    {8, "���ļ�����",   UI_LoadDatabaseFromFile},
    {9, "������Ŀ",     UI_SortDatabase}
};

const int num_main_menu_items = (int)(sizeof(main_menu) / sizeof(main_menu[0]));

// ��ʾ�˵�
void UI_DisplayMenu(void)
{
    for (int i= 0; i < num_main_menu_items; ++i)
        printf("%d-%s\n", main_menu[i].number, main_menu[i].name);
}

// ����˵���
int UI_ProcessMenuItem(int menu_item)
// menu_item: (in) �˵�����
// ����ֵ��1-�˵���Ϊ�˳��� 0-����
{
    int i;
    for (i = 0; i < num_main_menu_items; ++i)
        if (main_menu[i].number == menu_item)
            break;

    if (i < num_main_menu_items)
    {
        if (main_menu[i].f == NULL)
            return 1;

        else
        {
            main_menu[i].f();
            return 0;
        }
    }
    else
    {
        printf("�˵���Ƿ�������\n");
        return 0;
    }
}

int main()
{
    srand((unsigned int)time(NULL));

    int choice;

#if _DEBUG

     CreatTestDatabase();

#endif // _DEBUG


    for (;;)
    {
        UI_DisplayMenu();

        printf("��ѡ��˵��");
        scanf("%d", &choice);

        if (UI_ProcessMenuItem(choice))
            break;
    }
    return 0;
}
