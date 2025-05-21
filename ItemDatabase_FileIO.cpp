#include<stdio.h>
#include <string.h>

#include "ItemDatabase.h"
#include "ItemDatabase_Internal.h"

int ItemDB_SaveToFile(const char *file_name)
// 把数据库数据保存到文件名为file_name指向的字符串的文件中
// 成功返回1， 否则返回0
{
    FILE *fp;
    struct Item_Node *p;

    // 打开文件
    fp = fopen(file_name, "w");

    // 检查文件是否打开成功
    if (fp == NULL)
        return 0;

    // 输出文件头
    fprintf(fp, "ItemDatabase\n");

    // 输出文件版本
    fprintf(fp, "version=10\n");


    // 循环所有物品
    for (p = item_database_head; p != NULL; p = p->next)
    {
        fputc('\n', fp);

        // 输出物品开始标签
        fprintf(fp, "<Item>\n");

        // 输出物品属性
        fprintf(fp, "number=%d\n", p->data.number);

        fprintf(fp, "name=%s\n", p->data.name);

        fprintf(fp, "quantity=%d\n", p->data.quantity);

        // 输出物品结束标签
        fprintf(fp, "</Item>\n");
    }


    // 关闭文件
    fclose(fp);

    return 1;
}

int ItemDB_LoadFromFile(const char *file_name)
// 从文件名为file_name指向的字符串的文件中载入数据库数据
// 成功返回1， 否则返回0
{
    FILE *fp;

    char buffer[1024];

    int version_number = 0;
    int in_item = 0;
    int itemp;
    struct Item temp_item;

    // 打开文件
    fp = fopen(file_name, "r");

    // 检查文件是否打开成功
    if (fp == NULL)
        return 0;

    // 读入第一行
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    {
        fclose(fp);
        return 0;
    }
    char *pc = strrchr(buffer, '\n');
    if (pc != NULL)
        *pc = '\0';

    // 判断是否与文件头匹配
    if (strcmp(buffer, "ItemDatabase") != 0)
    {
        fclose(fp);
        return 0;
    }
    // 读入第二行
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    {
        fclose(fp);
        return 0;
    }

    // 检查版本格式是否正确
    // 以及版本号是否是10
    if (1 != sscanf(buffer, "version=%d", &version_number) || version_number != 10)
    {
        fclose(fp);
        return 0;
    }

    // 清空数据库内容
    ItemDB_ClearDatabase();

    while (!feof(fp))
    {
        // 读入一行
        fgets(buffer, sizeof(buffer), fp);
        pc = strrchr(buffer, '\n');
        if (pc != NULL)
            *pc = '\0';
        // 检查当前是否在物品中
        if (!in_item)
        {
            // 不在物品中
            // 检查是否是物品开始标签
            if (strcmp(buffer, "<Item>") == 0)
            {
                // 升起在物品中旗帜
                in_item = 1;
            }
        }
        else
        {
            // 在物品中
            // 检查是否是物品结束标签
            if (strcmp(buffer, "</Item>") == 0)
            {
                // 降下在物品中的旗帜
                in_item = 0;

                // 把物品加入数据库
                ItemDB_AddItem(&temp_item);
            }
            // 检查是否是物品编号
            else if (1 == sscanf(buffer, "number=%d", &itemp))
            {
                temp_item.number = itemp;
            }
            // 检查是否是物品数量
            else if (1 == sscanf(buffer, "quantity=%d", &itemp))
            {
                temp_item.quantity = itemp;
            }
            // 检查是否是物品名称
            else if (0 == strncmp(buffer, "name=", 5))
            {
                strncpy(temp_item.name, buffer + 5, ITEM_NAME_MAX_LEN - 1);
                temp_item.name[ITEM_NAME_MAX_LEN - 1] = '\0';
            }
        }
    }

    // 关闭文件
    fclose(fp);
    return 1;
}
