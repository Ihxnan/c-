#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ItemDatabase.h"

// 增加物品
void UI_AddItem(void)
{
    struct Item temp_item;
    PItemIterator it = ItemDB_CreateItemIterator();

    // 读入新物品编号
    printf("请输入新物品编号：");
    scanf("%d", &temp_item.number);

    // 检查物品编号是否已经存在
    // 存在则返回错误信息并返回
    ItemDB_FindItem(temp_item.number, it);
    if (ItemDB_IsItemIteratorValid(it))
        printf("物品已经存在\n");
    else
    {
        // 读入新物品名称
        printf("请输入新物品名称：");
        scanf("%s", temp_item.name);

        // 读入新物品数量
        printf("请输入新物品数量：");
        scanf("%d", &temp_item.quantity);

        // 将新物品加入数据库中
        if (!ItemDB_AddItem(&temp_item))
            printf("物品添加失败!\n");
        else
            printf("添加成功!\n");
    }

    ItemDB_DeleteItemIterator(it);
}

// 删除物品
void UI_DeleteItem(void)
{
    // 要删除的物品的编号
    int delete_number = 0;
    PItemIterator it = ItemDB_CreateItemIterator();

    // 读入要删除物品编号
    printf("请输入要删除物品编号：");
    scanf("%d", &delete_number);

    // 获得物品下标
    ItemDB_FindItem(delete_number, it);
    if (!ItemDB_IsItemIteratorValid(it))
    {
        printf("删除物品不存在\n");
    }
    else
    {
        ItemDB_DeleteItem(it);
        printf("删除成功\n");
    }
    ItemDB_DeleteItemIterator(it);
}

// 更新物品
void UI_UpdateItem(void)
{
    int number;
    struct Item *p_item;
    PItemIterator it = ItemDB_CreateItemIterator();

    printf("请输入要更新物品的编号：");
    scanf("%d", &number);

    ItemDB_FindItem(number, it);

    if (!ItemDB_IsItemIteratorValid(it))
    {
        printf("物品不存在!\n");
    }
    else
    {
        p_item = ItemDB_GetItemPointer(it);

        // 读入新物品名称
        printf("请输入新物品名称：");
        scanf("%s", p_item->name);

        // 读入新物品数量
        printf("请输入新物品数量：");
        scanf("%d", &p_item->quantity);

        printf("物品更新成功！\n");
    }
    ItemDB_DeleteItemIterator(it);
}

// 搜索物品
void UI_SearchItem(void)
{
    int number;
    PItemIterator p_iter;
    struct Item *p_item;

    p_iter = ItemDB_CreateItemIterator();
    // 输入物品编号
    printf("请输入物品编号：");
    scanf("%d", &number);

    // 搜索对应编号的物品
    ItemDB_FindItem(number, p_iter);

    // 如果物品不存在则显示不存在并返回
    if (!ItemDB_IsItemIteratorValid(p_iter))
    {
        printf("物品不存在!\n");
    }
    else
    {
        // 获取指向物品的指针
        p_item = ItemDB_GetItemPointer(p_iter);

        printf("物品的名称：%s\n物品的数量：%d\n", p_item->name, p_item->quantity);
    }
    ItemDB_DeleteItemIterator(p_iter);
}

// 输出数据库
void UI_PrintDatabase(void)
{
    int n;
    struct Item *p;
    PItemIterator p_iter;

    // 获取并显示物品数量
    n = ItemDB_GetNumItems();
    printf("物品的数量：%d\n", n);

    // 如果物品数量为0则返回
    if (n == 0)
        return;

    p_iter = ItemDB_CreateItemIterator();
    // 遍历所有物品并显示物品信息
    printf("   编号            名称            数量\n");
    for (ItemDB_GetFirstItemIterator(p_iter);
         ItemDB_IsItemIteratorValid(p_iter);
         ItemDB_GetNextItemIterator(p_iter))
    {
        p = ItemDB_GetItemPointer(p_iter);
        printf("%10d %20s %10d\n", p->number, p->name, p->quantity);
    }
    ItemDB_DeleteItemIterator(p_iter);
}

// 清空数据库
void UI_ClearDatabase(void)
{
    ItemDB_ClearDatabase();
    printf("删除成功\n");
}

// 把数据库数据保存到文件中
void UI_SaveDatabaseToFile(void)
{
    char file_name[1024];
    // 输入文件名
    printf("请输入要保存的文件名：");
    scanf("%s", file_name);

    // 把数据库保存到该文件中
    if (ItemDB_SaveToFile(file_name))
        printf("保存成功。\n");
    else
        printf("保存失败！\n");
}

// 从文件中载入数据库数据
void UI_LoadDatabaseFromFile(void)
{
    char file_name[1024];
    // 输入文件名
    printf("请输入要载入的文件名：");
    scanf("%s", file_name);

    // 把数据库保存到该文件中
    if (ItemDB_LoadFromFile(file_name))
        printf("载入成功。\n");
    else
        printf("载入失败！\n");
}

void UI_SortDatabase(void)
{
    int sort_method, sort_dir;
    printf("请选择排序方式：\n");
    printf("\t\t0->按编号排序\n");
    printf("\t\t1->按名称排序\n");
    printf("\t\t2->按数量排序\n");
    scanf("%d", &sort_method);
    if (sort_method > 2 || sort_method < 0)
    {
        printf("输入非法！！！\n");
        return;
    }
    printf("请输入排序方向：\n");
    printf("\t\t0->按升序排序\n");
    printf("\t\t1->按降序排序\n");
    scanf("%d", &sort_dir);
    if (sort_dir > 1 || sort_dir < 0)
    {
        printf("输入非法！！！\n");
        return;
    }
    ItemDB_Sort(sort_method, sort_dir);
    printf("排序成功\n");
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

// 菜单项结构
struct {
    int number; // 编号
    const char* name; // 名称
    void (*f) (void); // 指向处理函数的指针
} main_menu[] // 主菜单
={
    {0, "退出", NULL},
    {1, "增加项目",     UI_AddItem},
    {2, "删除项目",     UI_DeleteItem},
    {3, "搜索项目",     UI_SearchItem},
    {4, "更新项目",     UI_UpdateItem},
    {5, "输出所有项目", UI_PrintDatabase},
    {6, "清空所有项目", UI_ClearDatabase},
    {7, "保存到文件",   UI_SaveDatabaseToFile},
    {8, "从文件载入",   UI_LoadDatabaseFromFile},
    {9, "排序项目",     UI_SortDatabase}
};

const int num_main_menu_items = (int)(sizeof(main_menu) / sizeof(main_menu[0]));

// 显示菜单
void UI_DisplayMenu(void)
{
    for (int i= 0; i < num_main_menu_items; ++i)
        printf("%d-%s\n", main_menu[i].number, main_menu[i].name);
}

// 处理菜单项
int UI_ProcessMenuItem(int menu_item)
// menu_item: (in) 菜单项编号
// 返回值：1-菜单项为退出， 0-其他
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
        printf("菜单项非法！！！\n");
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

        printf("请选择菜单项：");
        scanf("%d", &choice);

        if (UI_ProcessMenuItem(choice))
            break;
    }
    return 0;
}
