#include <iostream>
#include "List_Node.h"
#include "List_Head.h"

void Test()
{
	using namespace std;
	List_Node<int>* node1 = new List_Node_SingleWay<int>(5);
	List_Node<int>* node2 = new List_Node_DoubleWay<int>(5);
	cout << node1->element << endl;
	cout << node2->element << endl;

	node1->Show();
	node2->Show();

	delete node1;
	delete node2;

	Link_List_Forward<int> l;
	for (int i = 0; i < 5; ++i)
		l.Insert_Front(i);
	l.List_Show("");


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
	Test_Forward_List();
	Test_Link_List_Double();
}