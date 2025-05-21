# C语言课程设计
### 双链表实现简易数据库

### 系统功能

- 功能介绍：

1. 增加物品；
2. 删除物品；
3. 搜索物品；
4. 更新物品；
5. 显示所有物品信息；
6. 清空物品数据库;
7. 保存到文件；
8. 从文件载入；
9. 对数据库排序；

- 模块划分

![图1 模块划分](.img/模块划分.png)


### 逻辑结构设计

## 数据类型定义

1. struct Item

| 数据项名 | 数据类型 | 注释 |
| --- | --- | --- |
| number | int | 编号 |
| name | char * | 名称 |
| quantity | int | 数量 |

2. struct Item_Node

| 数据项名 | 数据类型 | 注释 |
| --- | --- | --- |
| data | struct Item | 物品数据 |
| prev | struct Item_Node* | 指向前一个结点的指针 |
| next | struct Item_Node* | 指向后一个结点的指针 |

3. struct ItemIterator

| 数据项名 | 数据类型 | 注释 |
| --- | --- | --- |
| p | struct Item_Node* | 指向物品结点的指针 |
