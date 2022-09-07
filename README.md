链表的结构体定义有问题
不能typedef ListNode* ListNode;
会导致头节点存放在数据段导致段错误
    即——头节点不要定义指针类型
        声明的时候再定义，LinkList* L的时候存放在堆中而不是只读数据段中



