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
	Link_List_Forward<int>L;
	for (int i = 1; i <= 10; i++)
		L.Element_Insert(i,i);
	L.List_Show("头插法插入10个节点后：");
	// std::cout << "第5个元素的前驱元素为: " << L.Element_Prior(5) << std::endl;
	List_Node_SingleWay<int> *pri = L.Element_Prior(L.Element_Locate(5));
	std::cout << "第5个元素的前驱节点为: " << pri->element << std::endl;
	List_Node_SingleWay<int>* next = L.Element_Next(L.Element_Locate(5));
	std::cout << "第5个元素的后继节点为: " << next->element << std::endl;
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
	List_Node_DoubleWay<int>* pri = L.Element_Prior(L.Element_Locate(5));
	std::cout << "第5个元素的前驱节点为: " << pri->element << std::endl;
	List_Node_DoubleWay<int>* next = L.Element_Next(L.Element_Locate(5));
	std::cout << "第5个元素的后继节点为: " << next->element << std::endl;
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
	Test_Forward_List();
	Test_Link_List_Double();

	return EXIT_SUCCESS;
}