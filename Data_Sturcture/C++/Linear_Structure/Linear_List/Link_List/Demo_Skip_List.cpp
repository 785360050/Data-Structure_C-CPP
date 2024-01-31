
#include <iostream>
#include "Skip_List.hpp"

using namespace std;

void Test()
{
    Skip_List list;

    // test Element_Insert
    list.Element_Insert(2);
    list.List_Show("插入2");
    list.Element_Insert(10);
    list.List_Show("插入10");
    list.Element_Insert(12);
    list.List_Show("插入12");
    list.Element_Insert(8);
    list.List_Show("插入8");
    list.Element_Insert(1);
    list.List_Show("插入1");
    list.Element_Insert(6);
    list.List_Show("插入6");
    cout << "插入6个元素后,size =  " << list.Get_Size() << endl;

    // test Search
    cout << "Element Search 1 = " << list.Element_Search(1).value_or(-1) << endl;
    cout << "Element Search 2 = " << list.Element_Search(2).value_or(-1) << endl;
    cout << "Element Search 6 = " << list.Element_Search(6).value_or(-1) << endl;
    cout << "Element Search 10 = " << list.Element_Search(10).value_or(-1) << endl;
    cout << "Element Search 12 = " << list.Element_Search(12).value_or(-1) << endl;

    cout << "Element Search 111 = " << list.Element_Search(111).value_or(-1) << endl;
    cout << "Element Search 0 = " << list.Element_Search(0).value_or(-1) << endl;

    // test Element_Delete
    list.Element_Delete(1);
    list.List_Show("删除1");
    list.Element_Delete(2);
    list.List_Show("删除2");
    list.Element_Delete(6);
    list.List_Show("删除6");
    list.Element_Delete(12);
    list.List_Show("删除12");
    cout << "删除4个元素后,size =  " << list.Get_Size() << endl;
}
void Test2()
{
    Skip_List l;
    static const int num{50};
    for (int i{}; i < num; ++i)
    {
        l.Element_Insert(i);
        l.List_Show();
    }
    // for (int i{}; i < num; ++i)
    for (int i{num - 1}; i >= 0; --i)
    {
        l.Element_Delete(i);
        l.List_Show();
    }
}

/// ============================================================================================================
/// Warn:
/// 由于rand()是伪随机，所以多个Skip_List实例之间操作的前后顺序都会互相影响最终生成的跳表结构
/// 如果要保持跳表的可重入性，则确保一次执行只有一个实例
/// ============================================================================================================
int main()
{
    
    // cout << "最坏情况，几乎退化为单链表，索引的基本用不上。是由于确定节点层数的随机的几率导致的" << endl;
    // Skip_List worst_list;
    // worst_list.Element_Insert(2);
    // worst_list.Element_Insert(10);
    // worst_list.Element_Insert(6);
    // worst_list.Element_Insert(8);
    // worst_list.Element_Insert(1);
    // worst_list.Element_Insert(12);
    // worst_list.List_Show();

    Test();
    // Test2();
    return 0;
}

/// ============================================================================================================
/// 对比Test()中不同实现的堆开销
/// ============================================================================================================
/// # 使用单链表：_Loacte_Previous_Node中的std::vector堆空间开销极大
// ==8489== HEAP SUMMARY:
// ==8489==     in use at exit: 0 bytes in 0 blocks
// ==8489==   total heap usage: 202 allocs, 202 frees, 79,456 bytes allocated
// ==8489==
// ==8489== All heap blocks were freed -- no leaks are possible
// ==8489==
// ==8489== For lists of detected and suppressed errors, rerun with: -s
// ==8489== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
/// ============================================================================================================

/// ============================================================================================================
// 使用std::map search_path 作为成员，_Loacte_Previous_Node时update search_path可以减少一部分heap 空间开销。
// ==6180== HEAP SUMMARY:
// ==6180==     in use at exit: 0 bytes in 0 blocks
// ==6180==   total heap usage: 39 allocs, 39 frees, 75,352 bytes allocated
// ==6180==
// ==6180== All heap blocks were freed -- no leaks are possible
// ==6180==
// ==6180== Use --track-origins=yes to see where uninitialised values come from
// ==6180== For lists of detected and suppressed errors, rerun with: -s
// ==6180== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
/// ============================================================================================================
