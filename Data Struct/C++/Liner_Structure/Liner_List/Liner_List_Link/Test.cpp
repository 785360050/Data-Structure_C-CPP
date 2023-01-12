#include <iostream>
#include "../../List_Node.h"
#include "List_Head.h"

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


void Test_Forward_List()
{
	Link_List_Forward<int>* L = new Link_List_Forward<int>;
	for (int i = 1; i <= 10; i++)
		L->Insert_Front(i);
	L->List_Show("头插法插入10个节点后：");
	List_Node_SingleWay<int>* pri = L->Element_Prior(L->Element_Locate(5));
	std::cout << "第5个元素的前驱节点为: " << pri->element << std::endl;
	List_Node_SingleWay<int>* next = L->Element_Next(L->Element_Locate(5));
	std::cout << "第5个元素的后继节点为: " << next->element << std::endl;
	L->Element_Delete(2);
	L->List_Show("删除第2个节点后：");
	L->Element_Insert(2, 2);
	L->List_Show("在第2个节点插入元素2后：");
	L->List_Clear();
	L->List_Show("重置链表后：");
	std::cout << "当前链表长度为: " << L->List_GetLength() << std::endl;
	std::cout << "链表判空: " << L->List_CheckEmpty() << std::endl;
	L->List_Destroy();
	L->List_Show("销毁链表后");
}

void Test_Link_List_Double()
{
	Link_List_Double<int>* L = new Link_List_Double<int>;
	for (int i = 1; i <= 10; i++)
		L->Element_Insert(1,i);
	L->List_Show("头插法插入10个节点后：");
	List_Node_DoubleWay<int>* pri = L->Element_Prior(L->Element_Locate(5));
	std::cout << "第5个元素的前驱节点为: " << pri->element << std::endl;
	List_Node_DoubleWay<int>* next = L->Element_Next(L->Element_Locate(5));
	std::cout << "第5个元素的后继节点为: " << next->element << std::endl;
	L->Element_Delete(2);
	L->List_Show("删除第2个节点后：");
	L->Element_Insert(2, 2);
	L->List_Show("在第2个节点插入元素2后：");
	L->List_Clear();
	L->List_Show("重置链表后：");
	std::cout << "当前链表长度为: " << L->List_GetLength() << std::endl;
	std::cout << "链表判空: " << L->List_CheckEmpty() << std::endl;
	L->List_Destroy();
	L->List_Show("销毁链表后");
}

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	Test_Forward_List();
	Test_Link_List_Double();
}