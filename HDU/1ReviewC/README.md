# 复习C语言编程和数据结构链表
> 用C语言编写程序，完成如下功能：

* 用结构体存储学生信息（学号sno、姓名sname、年龄sage、班级sclass）
* 用链表存储班级所有同学
* 实现新增、查找（根据学号）、修改、删除、打印名单的功能

>思路描述

1. 定义一个学生的结构体来储存各种信息
2. 定义一个学生链表来管理各个节点
3. 在已定义的数据结构的基础上实现CRUD的操作
4. 测试各个函数


>问题说明

```
struct Student{
    char sno[20];
    char sname[20];
    int sage;
    char sclass[20];
    struct Student* next;
};
```
我刚开始把' sno '声明为' char * ' ,这导致申请内存时只分配了一个指针的空间，每次读入的数据，都反复地写在一个临时的空间，每次读入时都会覆盖之前的内容，导致结果错误。

>体会

C语言的难点在于指针操作

>注意

若要测试程序，需要将源代码中的'ROAD'修改至正确位置

>针对老师意见进行的修改

1. 已采用老师的算法，刚开始主要是我还想把find用于删除，因此想返回目标节点前一个节点的指针，可是后来发现这不符合find的功能要求，就对已经写的代码进行修改，导致代码并不是最优。
2. 已增加将插入的节点的下址指针置空的代码，但我这里其实将生成学生节点的代码一起封装在'createStudent'中了，那里已经提前置空了
3. 已删除多余代码
4. 已处理可能的内存泄漏。