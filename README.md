# MyDataStructures

这是一个模仿 STL 手造的数据结构轮子 (不齐全), 主要包括

* 位于 `MyDataStructure` 命名空间下
    | 类名 | 头文件 | 说明|
    |:--|:--|:--|
    |`arrayList`|`arrayList.h`|模拟 `std::vector` 实现的动态数组|
    |`doublyLinkedList`|`linkedList.h`|模拟 `std::list` 实现的链表|
    |`Stack`|`listAdapters.h`|模拟 `std::stack` 实现的栈 (用链表实现)|
    |`Queue`|`listAdapters.h`|模拟 `std::queue` 实现的队列 (用链表实现)|
    |`binaryTree`|`binaryTree.h`| 二叉树基类|
    |`binarySearchTree`|`binarySearchTree.h`|二叉查找树, 实现了查找/插入/删除|

    以下是想写但未完成的
    | 类名(计划)|头文件|说明(计划)|
    |:--|:--|:--|
    |`AVLTree`|`binarySearchTree.h`|模拟 `std::set` 与 `std::map`|
    |`RBTree`|`binarySearchTree.h`|模拟 `std::set` 与 `std::map`|
