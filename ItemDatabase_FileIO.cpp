#include<stdio.h>
#include <string.h>

#include "ItemDatabase.h"
#include "ItemDatabase_Internal.h"

int ItemDB_SaveToFile(const char *file_name)
// �����ݿ����ݱ��浽�ļ���Ϊfile_nameָ����ַ������ļ���
// �ɹ�����1�� ���򷵻�0
{
    FILE *fp;
    struct Item_Node *p;

    // ���ļ�
    fp = fopen(file_name, "w");

    // ����ļ��Ƿ�򿪳ɹ�
    if (fp == NULL)
        return 0;

    // ����ļ�ͷ
    fprintf(fp, "ItemDatabase\n");

    // ����ļ��汾
    fprintf(fp, "version=10\n");


    // ѭ��������Ʒ
    for (p = item_database_head; p != NULL; p = p->next)
    {
        fputc('\n', fp);

        // �����Ʒ��ʼ��ǩ
        fprintf(fp, "<Item>\n");

        // �����Ʒ����
        fprintf(fp, "number=%d\n", p->data.number);

        fprintf(fp, "name=%s\n", p->data.name);

        fprintf(fp, "quantity=%d\n", p->data.quantity);

        // �����Ʒ������ǩ
        fprintf(fp, "</Item>\n");
    }


    // �ر��ļ�
    fclose(fp);

    return 1;
}

int ItemDB_LoadFromFile(const char *file_name)
// ���ļ���Ϊfile_nameָ����ַ������ļ����������ݿ�����
// �ɹ�����1�� ���򷵻�0
{
    FILE *fp;

    char buffer[1024];

    int version_number = 0;
    int in_item = 0;
    int itemp;
    struct Item temp_item;

    // ���ļ�
    fp = fopen(file_name, "r");

    // ����ļ��Ƿ�򿪳ɹ�
    if (fp == NULL)
        return 0;

    // �����һ��
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    {
        fclose(fp);
        return 0;
    }
    char *pc = strrchr(buffer, '\n');
    if (pc != NULL)
        *pc = '\0';

    // �ж��Ƿ����ļ�ͷƥ��
    if (strcmp(buffer, "ItemDatabase") != 0)
    {
        fclose(fp);
        return 0;
    }
    // ����ڶ���
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    {
        fclose(fp);
        return 0;
    }

    // ���汾��ʽ�Ƿ���ȷ
    // �Լ��汾���Ƿ���10
    if (1 != sscanf(buffer, "version=%d", &version_number) || version_number != 10)
    {
        fclose(fp);
        return 0;
    }

    // ������ݿ�����
    ItemDB_ClearDatabase();

    while (!feof(fp))
    {
        // ����һ��
        fgets(buffer, sizeof(buffer), fp);
        pc = strrchr(buffer, '\n');
        if (pc != NULL)
            *pc = '\0';
        // ��鵱ǰ�Ƿ�����Ʒ��
        if (!in_item)
        {
            // ������Ʒ��
            // ����Ƿ�����Ʒ��ʼ��ǩ
            if (strcmp(buffer, "<Item>") == 0)
            {
                // ��������Ʒ������
                in_item = 1;
            }
        }
        else
        {
            // ����Ʒ��
            // ����Ƿ�����Ʒ������ǩ
            if (strcmp(buffer, "</Item>") == 0)
            {
                // ��������Ʒ�е�����
                in_item = 0;

                // ����Ʒ�������ݿ�
                ItemDB_AddItem(&temp_item);
            }
            // ����Ƿ�����Ʒ���
            else if (1 == sscanf(buffer, "number=%d", &itemp))
            {
                temp_item.number = itemp;
            }
            // ����Ƿ�����Ʒ����
            else if (1 == sscanf(buffer, "quantity=%d", &itemp))
            {
                temp_item.quantity = itemp;
            }
            // ����Ƿ�����Ʒ����
            else if (0 == strncmp(buffer, "name=", 5))
            {
                strncpy(temp_item.name, buffer + 5, ITEM_NAME_MAX_LEN - 1);
                temp_item.name[ITEM_NAME_MAX_LEN - 1] = '\0';
            }
        }
    }

    // �ر��ļ�
    fclose(fp);
    return 1;
}
