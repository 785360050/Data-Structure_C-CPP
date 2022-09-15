#include "../API/Liner_List_Link.h"
#include <iostream>


LinkList* LinkList_Init()
{
	/// <summary>
	/// 定义头节点、首元节点
	/// 头节点存放链表信息，指向首元节点
	/// </summary>
	/// <returns>返回头节点指针</returns>
	LinkList* L = (LinkList*)malloc(sizeof(LinkList));
	if (L)
	{
		L->length = 0;
		L->front = NULL;
	}
	else
	{
		std::cout << "头节点或首元节点分配失败" << std::endl;
	}
	return L;
}

void LinkList_FreeNode(ListNode* n)
{
	/// <summary>
	/// 若节点存在，释放节点空间
	/// </summary>
	/// <param name="n"></param>
	if(n)
		free(n);
}
void LinkList_DeleteList(LinkList* L)
{
	/// <summary>
	/// 若链表不为空(头节点或首元节点存在)
	/// 删除整个链表
	/// </summary>
	/// <param name="L">待删除链表名</param>
	if (L)
	{
		while (L->front)//循环删除首元节点
		{
			ListNode* temp = L->front;
			L->front = temp->next;
			LinkList_FreeNode(temp);
			L->length--;
		}
		free(L);
	}
	
	
}


ListNode* LinkList_MakeNode( DataType value)
{
	/// <summary>
	/// 定义并初始化新节点 
	/// data=value，next=NULL
	/// </summary>
	/// <param name="value">元素值</param>
	/// <returns>返回新建的节点指针，创建失败则返回空指针NULL</returns>
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	if (!p)
	{
		return NULL;
	}
	else
	{
		p->data = value;
		p->next = NULL;
		return p;
	}
	
}

void LinkList_AddNode_front(LinkList* Listname,DataType value)
{
	/// <summary>
	/// 用头插法在链表头插入新建节点 data=value
	/// </summary>
	/// <param name="Listname">链表名</param>
	/// <param name="value">元素值</param>
	ListNode* p = LinkList_MakeNode(value);
	p->next = Listname->front;
	Listname->front = p;
	Listname->length++;
}
void LinkList_AddNode_rear(LinkList* L, DataType e);

//检查 pos∈[ BeginPos , EndPos ]
//属于时返回true
bool CheckPosition(int Pos, int BeginPos, int EndPos)
{
	if (BeginPos <= Pos && Pos <= EndPos)
		return true;
}

DataType LinkList_GetElem(ListNode* node)
{
	/// <summary>
	/// 若当前节点存在
	/// 取出该节点的数据
	/// 否则返回NULL(0)
	/// </summary>
	/// <param name="node">当前节点</param>
	/// <returns>数据</returns>
	try
	{
		if (!node)
			throw 1;
	}
	catch (...)
	{
		std::cout << "该节点不存在" << std::endl;
		exit(0);
	}
	return node->data;		
}

ListNode* LinkList_LocateNode(const LinkList* L, int pos)
{
	/// <summary>
	/// 返回链表L中，第pos个元素节点的指针
	/// </summary>
	/// <param name="L">链表</param>
	/// <param name="pos">元素位置</param>
	/// <returns>节点指针</returns>
	//判断非空且不超过l->length
	try
	{
		if (pos<=0 || pos>L->length)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Illegal position" << std::endl;
		exit(0);
	}

	const LinkList* list = L;
	ListNode* p;	//找已存在的节点不需要malloc
	p = L->front;
	for (int i = 1; i < pos; i++)
	{//遍历定位到第pos个元素节点
		p = p->next;
	}
	return p;
}
ListNode* LinkList_PriNode(const LinkList* L, ListNode* const node)
{
	/// <summary>
	/// 返回链表L中,node节点的前驱节点
	/// </summary>
	/// <param name="L">链表</param>
	/// <param name="node">节点</param>
	/// <returns>前驱节点</returns>
	try
	{
		if (L->length<=1||!L->front)
			throw 1;
	}
	catch (...)
	{
		std::cout << "前驱节点不存在" << std::endl;
		exit(0);
	}
	ListNode* t;
	t = L->front;
	while (t->next != node)
	{
		t = t->next;
	}
	return t;	
}
ListNode* LinkList_NextNode(const LinkList* L, const ListNode* node)
{
	/// <summary>
	/// 返回链表L中node节点的后继节点
	/// </summary>
	/// <param name="L">链表</param>
	/// <param name="node">节点</param>
	/// <returns>节点指针</returns>
	return node->next;
}


void LinkList_InsertNode(LinkList* L, int pos, DataType e)
{
	/// <summary>
	/// 在链表L的第pos个位置上，创建并插入新节点，data=e
	/// </summary>
	/// <param name="L">链表</param>
	/// <param name="pos">元素位置</param>
	/// <param name="e">节点值</param>
	try
	{
		if(!CheckPosition(pos,1,L->length))
			throw 1;
	}//未调整  
	catch (...)
	{
		std::cout << "Illegal position" << std::endl;
		exit(0);
	}
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	if (p)
	{
		p->data = e;
	}
	else
	{
		std::cout << "创建失败" << std::endl;
		exit(0);
	}
	if (pos==1)
	{
		ListNode* p = LinkList_MakeNode(e);
		L->front = p;
		L->length++;
	}
	else
	{
		ListNode* p_pri = LinkList_LocateNode(L, pos - 1);
		p->next = p_pri->next;
		p_pri->next = p;
		L->length++;
	}	
}
void LinkList_DeleteNode(LinkList* L, int pos)
{
	/// <summary>
	/// 删除链表L的第pos个元素节点
	/// </summary>
	/// <param name="L">链表</param>
	/// <param name="pos">元素位置</param>
	try
	{
		if (!CheckPosition(pos, 1, L->length))
			throw 1;
	}
	catch (...)
	{
		std::cout << "Illegal position" << std::endl;
		exit(0);
	}
		
	ListNode* temp = LinkList_LocateNode(L, pos);
	ListNode* pri = LinkList_PriNode(L,temp);
	pri->next = temp->next;
	LinkList_FreeNode(temp);
	L->length--;
}

void LinkList_Show(const LinkList* L)
{
	std::cout << "Length:" << L->length << std::endl;
	for (ListNode* p = L->front; p; p = p->next)
		std::cout << "[" << p->data << "] ";
	std::cout << std::endl;
}







