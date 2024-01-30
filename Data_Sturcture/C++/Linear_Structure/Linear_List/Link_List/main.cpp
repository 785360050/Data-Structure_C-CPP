
#include <iostream>
#include "Skip_List.hpp"

using namespace std;

void Test()
{
    Skip_List list;

    // test Element_Insert
    list.Element_Insert(2);
    list.Show();
    list.Element_Insert(10);
    list.Show();
    list.Element_Insert(12);
    list.Show();
    list.Element_Insert(8);
    list.Show();
    list.Element_Insert(1);
    list.Show();
    list.Element_Insert(6);
    list.Show();
    // std::vector<char> v(1,'c');
    cout << "Its size is " << list.Size() << endl;

    // test Search
    cout << "Element associated with 1 is " << list.Search(1).value_or(-1) << endl;
    cout << "Element associated with 2 is " << list.Search(2).value_or(-1) << endl;
    cout << "Element associated with 6 is " << list.Search(6).value_or(-1) << endl;
    cout << "Element associated with 10 is " << list.Search(10).value_or(-1) << endl;
    cout << "Element associated with 12 is " << list.Search(12).value_or(-1) << endl;

    cout << "Element associated with 111 is " << list.Search(111).value_or(-1) << endl;
    cout << "Element associated with 0 is " << list.Search(0).value_or(-1) << endl;

    // test Element_Delete
    list.Element_Delete(1);
    list.Show();
    list.Element_Delete(2);
    list.Show();
    list.Element_Delete(6);
    list.Show();
    list.Element_Delete(12);
    cout << "Deleted 1, 2, 6, 12" << endl;
    list.Show();
    cout << "Its size is " << list.Size() << endl;
}
void Test2()
{
    Skip_List l;
    static const int num{50};
    for (int i{}; i < num; ++i)
    {
        l.Element_Insert(i);
        l.Show();
    }
    // for (int i{}; i < num; ++i)
    for (int i{num - 1}; i >= 0; --i)
    {
        l.Element_Delete(i);
        l.Show();
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
    // worst_list.Show();

    Test();
    // Test2();
    return 0;
}

/// ============================================================================================================
///
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
