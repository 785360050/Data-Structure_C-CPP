#include "C:/Users/len/Desktop/Data Struct/Data Struct/API/Liner_List_Link.h"
#include <iostream>


LinkList* LinkList_Init()
{
	/// <summary>
	/// ����ͷ�ڵ㡢��Ԫ�ڵ�
	/// ͷ�ڵ���������Ϣ��ָ����Ԫ�ڵ�
	/// </summary>
	/// <returns>����ͷ�ڵ�ָ��</returns>
	LinkList* L = (LinkList*)malloc(sizeof(LinkList));
	if (L)
	{
		L->length = 0;
		L->front = NULL;
	}
	else
	{
		std::cout << "ͷ�ڵ����Ԫ�ڵ����ʧ��" << std::endl;
	}
	return L;
}

void LinkList_FreeNode(ListNode* n)
{
	/// <summary>
	/// ���ڵ���ڣ��ͷŽڵ�ռ�
	/// </summary>
	/// <param name="n"></param>
	if(n)
		free(n);
}
void LinkList_DeleteList(LinkList* L)
{
	/// <summary>
	/// ������Ϊ��(ͷ�ڵ����Ԫ�ڵ����)
	/// ɾ����������
	/// </summary>
	/// <param name="L">��ɾ��������</param>
	if (L)
	{
		while (L->front)//ѭ��ɾ����Ԫ�ڵ�
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
	/// ���岢��ʼ���½ڵ� 
	/// data=value��next=NULL
	/// </summary>
	/// <param name="value">Ԫ��ֵ</param>
	/// <returns>�����½��Ľڵ�ָ�룬����ʧ���򷵻ؿ�ָ��NULL</returns>
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
	/// ��ͷ�巨������ͷ�����½��ڵ� data=value
	/// </summary>
	/// <param name="Listname">������</param>
	/// <param name="value">Ԫ��ֵ</param>
	ListNode* p = LinkList_MakeNode(value);
	p->next = Listname->front;
	Listname->front = p;
	Listname->length++;
}
void LinkList_AddNode_rear(LinkList* L, DataType e);

//��� pos��[ BeginPos , EndPos ]
//����ʱ����true
bool CheckPosition(int Pos, int BeginPos, int EndPos)
{
	if (BeginPos <= Pos && Pos <= EndPos)
		return true;
}

DataType LinkList_GetElem(ListNode* node)
{
	/// <summary>
	/// ����ǰ�ڵ����
	/// ȡ���ýڵ������
	/// ���򷵻�NULL(0)
	/// </summary>
	/// <param name="node">��ǰ�ڵ�</param>
	/// <returns>����</returns>
	try
	{
		if (!node)
			throw 1;
	}
	catch (...)
	{
		std::cout << "�ýڵ㲻����" << std::endl;
		exit(0);
	}
	return node->data;		
}

ListNode* LinkList_LocateNode(const LinkList* L, int pos)
{
	/// <summary>
	/// ��������L�У���pos��Ԫ�ؽڵ��ָ��
	/// </summary>
	/// <param name="L">����</param>
	/// <param name="pos">Ԫ��λ��</param>
	/// <returns>�ڵ�ָ��</returns>
	//�жϷǿ��Ҳ�����l->length
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
	ListNode* p;	//���Ѵ��ڵĽڵ㲻��Ҫmalloc
	p = L->front;
	for (int i = 1; i < pos; i++)
	{//������λ����pos��Ԫ�ؽڵ�
		p = p->next;
	}
	return p;
}
ListNode* LinkList_PriNode(const LinkList* L, ListNode* const node)
{
	/// <summary>
	/// ��������L��,node�ڵ��ǰ���ڵ�
	/// </summary>
	/// <param name="L">����</param>
	/// <param name="node">�ڵ�</param>
	/// <returns>ǰ���ڵ�</returns>
	try
	{
		if (L->length<=1||!L->front)
			throw 1;
	}
	catch (...)
	{
		std::cout << "ǰ���ڵ㲻����" << std::endl;
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
	/// ��������L��node�ڵ�ĺ�̽ڵ�
	/// </summary>
	/// <param name="L">����</param>
	/// <param name="node">�ڵ�</param>
	/// <returns>�ڵ�ָ��</returns>
	return node->next;
}


void LinkList_InsertNode(LinkList* L, int pos, DataType e)
{
	/// <summary>
	/// ������L�ĵ�pos��λ���ϣ������������½ڵ㣬data=e
	/// </summary>
	/// <param name="L">����</param>
	/// <param name="pos">Ԫ��λ��</param>
	/// <param name="e">�ڵ�ֵ</param>
	try
	{
		if(!CheckPosition(pos,1,L->length))
			throw 1;
	}//δ����  
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
		std::cout << "����ʧ��" << std::endl;
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
	/// ɾ������L�ĵ�pos��Ԫ�ؽڵ�
	/// </summary>
	/// <param name="L">����</param>
	/// <param name="pos">Ԫ��λ��</param>
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







