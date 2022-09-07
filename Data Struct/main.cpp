#include <iostream>
#include "API/Liner_List_Link.h"
#include "API/Liner_List_Sequential.h"
#include "API/Liner_Stack.h"
#include "API/Liner_Queue.h"



void TestSeqList()
{
	SeqList* L = SeqList_Init(10);
	SeqList_Show(L);
	for(int i=1;i<=5;i++)
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
	for(int i=1;i<=10;i++)
		LinkList_AddNode_front(L, i);
	//LinkList_AddNode_rear(L, e);
	LinkList_Show(L);


	LinkList_InsertNode(L, 2, 2);
	LinkList_Show(L);
	ListNode* s = (ListNode*)malloc(sizeof(ListNode));
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	s = LinkList_LocateNode(L, 2);
	std::cout << LinkList_GetElem(s) << std::endl;
	p = LinkList_PriNode(L,s);
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
	while(s->top>0)
	{
		x=SeqStack_Pop(s);
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
	while (q->front!=q->rear)
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
	while (q->length>0)
	{
		std::cout << LinkQueue_Pop(q)<<std::endl;
	}
	LinkQueue_Destroy(q);
}


void main()
{
	//TestSeqList();//完毕
	//TestLinkList();//完毕
	//TestSeqStack();//完毕
	//TestLinkStack();//完毕
	//TestSeqQueue();//完毕
	//TestLinkQueue();//完毕


	
	
	
	
}



