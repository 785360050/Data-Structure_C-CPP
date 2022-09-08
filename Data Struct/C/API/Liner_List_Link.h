#pragma once

typedef int DataType;

struct Node
{
	DataType data;
	struct Node* next;
};
typedef struct Node ListNode;

struct head
{
	ListNode* front;
	//ListNode* rear;
	int length;
};
typedef struct head LinkList;

//创建带头节点的空链表
LinkList* LinkList_Init();
//删除链表
void LinkList_DeleteList(LinkList* L);

//头插法
void LinkList_AddNode_front(LinkList* L, DataType e);
//void LinkList_AddNode_rear(LinkList L, DataType e);//尾插法

ListNode* LinkList_LocateNode(const LinkList* L, int pos);
ListNode* LinkList_PriNode(const LinkList* L, ListNode* const node);
ListNode* LinkList_NextNode(const LinkList* L, const ListNode* node);


DataType LinkList_GetElem(ListNode* node);
void LinkList_InsertNode(LinkList* L, int p, DataType e);
void LinkList_DeleteNode(LinkList* L, int p);



void LinkList_Show(const LinkList* L);







