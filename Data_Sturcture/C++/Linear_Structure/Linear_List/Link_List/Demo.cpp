#include <iostream>

#include "../../List_Node.hpp"
#include "Link_List.hpp"


#ifdef _Win32 // ARM32/64, x86/x64
// 详见 https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170

#include <Windows.h>
///修改cmd编码方式
static bool  SetEncode(int EncodeId = 936)
{
	/// <summary>
	/// EncodeId 是代码页，设置它等于设置我们指定的编码格式。
	///	默认936为unicode编码
	/// SetConsoleCP() 设置控制台输入时使用的编码。
	///	SetConsoleOutputCP() 设置控制台输出时使用的编码。
	/// </summary>
	/// <param name="EncodeId"></param>
	/// <returns></returns>
	return SetConsoleCP(EncodeId) && SetConsoleOutputCP(EncodeId);
}
#endif


void Test_Forward_List()
{
	Link_List_Forward<int> L;
	for (int i = 1; i <= 10; i++)
		L.Element_Insert(i,i);
	L.List_Show("按顺序插入10个节点后：");
	L.Element_Delete(2);
	L.List_Show("删除第2个节点后：");
	L.Element_Insert(2, 2);
	L.List_Show("在第2个节点插入元素2后：");
	L.Element_Update(2, 999);
	L.List_Show("更新第2个节点为999后：");
	L.List_Clear();
	L.List_Show("重置链表后：");
	std::cout << "当前链表长度为: " << L.Get_Size() << std::endl;
	std::cout << "链表判空: " <<std::boolalpha<< L.Is_Empty() << std::endl;
}

void Test_Link_List_Double()
{
	Link_List_Double<int> L ;
	for (int i = 1; i <= 10; i++)
		L.Element_Insert(1,i);
	L.List_Show("头插法插入10个节点后：");
	L.Element_Delete(2);
	L.List_Show("删除第2个节点后：");
	L.Element_Insert(2, 2);
	L.List_Show("在第2个节点插入元素2后：");
	L.Element_Update(2, 999);
	L.List_Show("更新第2个节点为999后：");
	L.List_Clear();
	L.List_Show("重置链表后：");
	std::cout << "当前链表长度为: " << L.Get_Size() << std::endl;
	std::cout << "链表判空: " << L.Is_Empty() << std::endl;
}
void Test_Link_List_Static()
{
	Link_List_Static<int,5> L;
	for (int i = 1; i <= 5; i++)
		L.Element_Insert(i, i);
	L.List_Show("头插法插入10个节点后：");
	L.Element_Delete(2);
	L.List_Show("删除第2个节点后：");
	L.Element_Insert(2, 2);
	L.List_Show("在第2个节点插入元素2后：");
	L.Element_Update(2, 999);
	L.List_Show("更新第2个节点为999后：");
	L.List_Clear();
	L.List_Show("重置链表后：");
	std::cout << "当前链表长度为: " << L.Get_Size() << std::endl;
	std::cout << "链表判空: " << L.Is_Empty() << std::endl;
}

int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	// Test_Forward_List();
	// Test_Link_List_Double();
	Test_Link_List_Static();
	
	return EXIT_SUCCESS;
}