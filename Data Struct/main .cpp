#include <iostream>



//#define C
#define CPP

#ifdef C
///C
#include "C/API/Liner_List_Link.h"
#include "C/API/Liner_List_Sequential.h"
#include "C/API/Liner_Stack.h"
#include "C/API/Liner_Queue.h"
#include "C/API/Tree_Binary.h"
#include "C/API/Tree_Binary_Thread.h"
#include "C/API/Tree_Binary_Search.h"
#include "C/API/Tree_Binary_AVL.h"
#include "C/API/Tree_MergeFind_Set.h"
#include "C/API/Graph_matrix.h"

///C function
void TestSeqList()
{
	SeqList* L = SeqList_Init(10);
	SeqList_Show(L);
	for (int i = 1; i <= 5; i++)
		SeqList_Insert(L, i, i);
	std::cout << SeqList_Delete(L, 3) << std::endl;
	SeqList_Update(L, 9, 9);
	SeqList_Show(L);
	SeqList_Destroy(L);
}

void TestLinkList()
{
	/// <summary>
	/// 测试链表的函数
	/// </summary>
	LinkList* L = LinkList_Init();
	for (int i = 1; i <= 10; i++)
		LinkList_AddNode_front(L, i);
	//LinkList_AddNode_rear(L, e);
	LinkList_Show(L);


	LinkList_InsertNode(L, 2, 2);
	LinkList_Show(L);
	ListNode* s = (ListNode*)malloc(sizeof(ListNode));
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	s = LinkList_LocateNode(L, 2);
	std::cout << LinkList_GetElem(s) << std::endl;
	p = LinkList_PriNode(L, s);
	std::cout << LinkList_GetElem(p) << std::endl;
	LinkList_DeleteList(L);

}

void TestSeqStack()
{
	SeqStack* s = SeqStack_Init(5);
	for (int i = 0; i < StackSize; i++)
	{
		SeqStack_Push(s, i);
	}
	for (int i = 0; i < StackSize; i++)
		std::cout << s->data[i] << " ";
	std::cout << std::endl;
	DataType x;
	while (s->top > 0)
	{
		x = SeqStack_Pop(s);
		std::cout << x << " ";
	}

	SeqStack_Destroy(s);
}
void TestLinkStack()
{
	LinkStack* S = LinkStack_Init();
	for (int i = 0; i < 5; i++)
	{
		LinkStack_Push(S, i);
	}
	LinkStack_Push(S, 1);
	while (S->next)
	{
		std::cout << LinkStack_Pop(S) << std::endl;
	}
	LinkStack_Destroy(S);
}

void TestSeqQueue()
{
	SeqQueue* q;
	q = SeqQueue_Init();
	for (int i = 1; i < 6; i++)
	{
		SeqQueue_Push(q, i);
	}
	while (q->front != q->rear)
	{
		std::cout << SeqQueue_Pop(q) << std::endl;
	}
	SeqQueue_Destory(q);

}
void TestLinkQueue()
{
	LinkQueue* q = LinkQueue_Init();
	for (int i = 1; i <= 5; i++)
	{
		LinkQueue_Push(q, i);
	}
	while (q->length > 0)
	{
		std::cout << LinkQueue_Pop(q) << std::endl;
	}
	LinkQueue_Destroy(q);
}

void BinaryTree()
{
	TNode* a = BinaryTree_CreateNode("A");
	TNode* b = BinaryTree_CreateNode("B");
	TNode* c = BinaryTree_CreateNode("C");
	TNode* d = BinaryTree_CreateNode("D");
	TNode* e = BinaryTree_CreateNode("E");
	TNode* f = BinaryTree_CreateNode("F");
	TNode* g = BinaryTree_CreateNode("G");
	TNode* h = BinaryTree_CreateNode("H");
	TNode* k = BinaryTree_CreateNode("K");

	BTree* Tree = BinaryTree_Init_Root(a);

	BinaryTree_Insert(Tree, a, left, b);
	BinaryTree_Insert(Tree, a, right, e);
	BinaryTree_Insert(Tree, b, right, c);
	BinaryTree_Insert(Tree, c, left, d);
	BinaryTree_Insert(Tree, e, right, f);
	BinaryTree_Insert(Tree, f, left, g);
	BinaryTree_Insert(Tree, g, left, h);
	BinaryTree_Insert(Tree, g, right, k);

	std::cout << "非递归：";
	std::cout << std::endl << "DLR：";
	BinaryTree_Traversal_Preorder_NoneRecursion(Tree->root);
	std::cout << std::endl << "LDR：";
	BinaryTree_Traversal_Inorder_NonRecursive(Tree->root);
	std::cout << std::endl << "LRD：";
	BinaryTree_Traversal_Postorder_NonRecursive(Tree->root);

	std::cout << std::endl << std::endl << "递归：";
	std::cout << std::endl << "DLR：";
	BinaryTree_Traversal_Preorder(Tree->root);
	std::cout << std::endl << "LDR：";
	BinaryTree_Traversal_Inorder(Tree->root);
	std::cout << std::endl << "LRD：";
	BinaryTree_Traversal_Postorder(Tree->root);
	//std::cout << std::endl << "Level：";
	//BinaryTree_Traversal_Level(Tree);
	///BUG
	std::cout << std::endl;
	BinaryTree_Destory(Tree);
}
void BinaryThreadTree()
{
	ThreadNode* a = BinaryTree_CreateNode_Thread("A");
	ThreadNode* b = BinaryTree_CreateNode_Thread("B");
	ThreadNode* c = BinaryTree_CreateNode_Thread("C");
	ThreadNode* d = BinaryTree_CreateNode_Thread("D");
	ThreadNode* e = BinaryTree_CreateNode_Thread("E");
	ThreadNode* f = BinaryTree_CreateNode_Thread("F");
	ThreadNode* g = BinaryTree_CreateNode_Thread("G");
	ThreadNode* h = BinaryTree_CreateNode_Thread("H");
	ThreadNode* k = BinaryTree_CreateNode_Thread("K");

	BTree_Thread* Tree = BinaryTree_Init_Root(a);

	BinaryTree_Insert_Thread(Tree, a, left, b);
	BinaryTree_Insert_Thread(Tree, a, right, e);
	BinaryTree_Insert_Thread(Tree, b, right, c);
	BinaryTree_Insert_Thread(Tree, c, left, d);
	BinaryTree_Insert_Thread(Tree, e, right, f);
	BinaryTree_Insert_Thread(Tree, f, left, g);
	BinaryTree_Insert_Thread(Tree, g, left, h);
	BinaryTree_Insert_Thread(Tree, g, right, k);

	BinaryTree_Thread_Inorder(Tree->root);

	BinaryTree_Traversal_Inorder_Thread(Tree->root);

	std::cout << std::endl;
	BinaryTree_Destory(Tree);
}

void BinarySearch()
{
	TNode* d = BinaryTree_CreateNode(4);

	BTree* Tree = BinaryTree_Init_Root(d);

	BinaryTree_Search_Insert(Tree, 2);
	BinaryTree_Search_Insert(Tree, 1);
	BinaryTree_Search_Insert(Tree, 3);
	BinaryTree_Search_Insert(Tree, 6);
	BinaryTree_Search_Insert(Tree, 5);
	BinaryTree_Search_Insert(Tree, 7);

	BinaryTree_Order_Increase(Tree->root);

	TNode* node = BinaryTree_Search_LocateElement(Tree, 7);///查找测试
	if (node)
		std::cout << std::endl << "Node Found" << std::endl;
	else
		std::cout << std::endl << "Node Not Found" << std::endl;

	BinaryTree_Search_Delete(Tree->root, 2);///可能有缺陷
	BinaryTree_Order_Increase(Tree->root);
	BinaryTree_Destory(Tree);
}
void BinarySearch_AVL()
{
	BinaryTree_AVL* Tree = BinaryTree_Init_Root_AVL();
	BinaryTree_Insert_AVL(Tree, 8);
	BinaryTree_Insert_AVL(Tree, 4);
	BinaryTree_Insert_AVL(Tree, 2);
	BinaryTree_Insert_AVL(Tree, 6);
	BinaryTree_Insert_AVL(Tree, 9);
	//std::cout << Tree->num << std::endl;
	BinaryTree_Traversal_Inorder_AVL(Tree->root);
	BinaryTree_AVL_Delete(Tree, Tree->root, 8);
	std::cout << std::endl;
	BinaryTree_Traversal_Inorder_AVL(Tree->root);
	BinaryTree_Destory(Tree);
}

void TestBinaryTree()
{
	//BinaryTree();
	//BinaryThreadTree();
	//BinarySearch();
	BinarySearch_AVL();
}

void TestMergeFindSet()
{
	int n = 5;
	DataType data[5] = { 0,1,2,3,4 };

	///——————————————————QucikFind
	MFSet_QuickFind* set_QF = Set_Create_QuickFind(n);
	Set_Init(set_QF, data, n);
	Merge(set_QF, 0, 2);
	Merge(set_QF, 4, 2);
	std::cout << Find(set_QF, 0, 2) << std::endl;
	std::cout << Find(set_QF, 1, 2) << std::endl;
	Set_Show(set_QF);
	Set_Destroy(set_QF);

	///———————————————————QuickMerge
	MFSet_QuickMerge* set_QM = Set_Create_QuickMerge(n);
	Set_Init(set_QM, data, n);
	Set_Show(set_QM);
	Merge(set_QM, 0, 2);
	Merge(set_QM, 4, 2);
	Merge(set_QM, 1, 3);
	std::cout << Find(set_QM, 0, 2) << std::endl;
	std::cout << Find(set_QM, 1, 2) << std::endl;
	Set_Show(set_QM);
	std::cout << "RootIndex(2)= " << RootIndex(set_QM, 2) << std::endl;
	std::cout << "RootIndex(2)= " << RootIndex_Optimized(set_QM, 2) << std::endl;
	Set_Destroy(set_QM);

}

void TestGraph()
{

}

void Test_C()
{
	//TestSeqList();//完毕
	//TestLinkList();//完毕
	//TestSeqStack();//完毕
	//TestLinkStack();//完毕
	//TestSeqQueue();//完毕
	//TestLinkQueue();//完毕
	//TestBinaryTree();//完毕
	//TestMergeFindSet();
	//TestGraph();
}

#endif // C

#ifdef CPP
///C++

#include "C++/Object.h"
#include "C++/Liner_List_ADT.h"
#include "C++/Liner_List_Sequential.h"
#include "C++/Liner_List_Link.h"
void TestSeqList()
{
	Sequential_List<int> L;
	L.List_Init(5);
	L.List_Show("初始化5个元素空间的顺序表后");

	for (int i = 1; i <= 5; i++)
		L.Element_Insert(i, i);
	L.List_Show("插入5个元素后");

	L.Element_Insert(2, 9);
	L.List_Show("第二个位置插入9后，检测到存储空间已满，扩展空间");

	std::cout << std::endl;
	L.Element_Insert(20, 20);
	L.List_Show("第20个非法位置插入20后");

	std::cout << std::endl;
	L.Element_Update(2, 999);
	L.List_Show("第二个元素改为999后");

	int del;
	L.Element_Delete(2, del);
	L.List_Show("删除第二个元素后");
	std::cout << "删除的第二个元素为:" << del << std::endl;

	std::cout << "获取第二个元素值:" << L.List_GetElement(2) << std::endl;
	
	std::cout << "判空 {0=F,1=T}:" << L.List_CheckEmpty() << std::endl;
	std::cout << "当前表长：" << L.List_GetLenghth() << std::endl;
	L.List_Clear();
	L.List_Show("清空后");
	std::cout << "当前表长：" << L.List_GetLenghth() << std::endl;

	L.List_Destroy();
}

void TestLinkList()
{///在堆上而不是栈上新建链表节点(不用构造函数新建)
	List_SingleLinked<int>* L = new List_SingleLinked<int>;
	L->List_Init();
	for (int i = 1; i <= 5; i++)
		L->Insert_Front(i);
	Node_SingleLinked<int>* pri = L->Element_Prior(L->Element_Locate(2));
	Node_SingleLinked<int>* next = L->Element_Next(L->Element_Locate(2));
	std::cout << pri->element << next->element << std::endl;
	L->Element_Delete(2);
	L->List_Show("删除第2个节点后：");
	L->Element_Insert(2, 2);
	L->List_Show("删除第2个节点元素2后：");
	L->List_Destroy();


}

void Test_CPP()
{
	TestSeqList();
	//TestLinkList();

}

#endif // CPP


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

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	
	//Test_C();
	Test_CPP();
}









