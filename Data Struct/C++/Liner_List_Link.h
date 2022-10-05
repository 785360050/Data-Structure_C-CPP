#pragma once


#include <iostream>

#include "Liner_List_ADT.h"

//链式存储结构模板
template <typename NodeType, typename DataType>
struct Liner_Structure:public Liner_List<DataType>
{
	//初始化线性表
	virtual void List_Init(int maxsize) = 0;
	//清空线性表
	virtual void List_Clear() = 0;
	//销毁线性表
	virtual void List_Destroy() = 0;
	//判断线性表是否为空
	virtual bool List_CheckEmpty() = 0;
	//求当前表长度
	virtual int List_GetLength() = 0;
	//返回第pos个元素的元素值
	virtual DataType List_GetElement(int pos) = 0;
	//显示线性表所有内容
	virtual void List_Show(const char* string) = 0;

	//定位节点
	virtual NodeType* Element_Locate(int pos) = 0;
	virtual NodeType* Element_Prior(const NodeType* const node) = 0;
	virtual NodeType* Element_Next(const NodeType* const node) = 0;
	virtual void Element_Insert(int pos, DataType element) = 0;
	virtual DataType Element_Delete(int pos) = 0;


};
///precursor node == prior node





//单链节点
template<typename DataType>
struct Node_SingleLinked
{///手动在堆上分配空间，而不是用栈
public:
	DataType element;
	struct Node_SingleLinked<DataType>* next;
public:
	//创建并初始化元素值为element，next默认为null的节点
	void Init(DataType element, Node_SingleLinked* next = nullptr)
	{
		this->element = element;
		this->next = next;
	}
};



//单链表(头节点)
template<typename DataType>
class List_SingleLinked:public Liner_Structure<Node_SingleLinked<DataType>, DataType>
{
private:
	Node_SingleLinked<DataType>* front;///模板型成员变量
	int length;
public:///链表操作
	//初始化头节点信息，存放链表信息
	void List_Init(int maxsize) override
	{
		length = 0;
		front = NULL;
		for (int i = 0; i < maxsize; i++)
		{///循环创建maxsize个节点插入链表
			Insert_Front(0);
		}
	}
	//重置所有元素值为0
	void List_Clear() override
	{
		//while (front)
		//{
		//	Node_SingleLinked<DataType>* temp = front;
		//	front = front->next;
		//	delete temp;
		//}
		try
		{
			if (!front)
				throw 1;
		}
		catch (...)
		{
			std::cout << "List is not exist" << std::endl;
			return;
		}
		Node_SingleLinked<DataType>* node = front;
		for (int i = 1; i <= length; i++)
		{
			node->element = 0;
			node = node->next;
		}
	}
	//释放整个表
	void List_Destroy() override
	{///销毁链表后不可访问
		if (length > 0)
		{
			Node_SingleLinked<DataType>* list = front;
			Node_SingleLinked<DataType>* del;
			while (list->next != NULL)
			{
				del = list;
				list = list->next;
				delete del;
			}
			delete list;
		}

		front = nullptr;
		delete this;
	}
	//检查链表是否非空
	bool List_CheckEmpty() override
	{
		if (length == 0)
			return true;
		return false;
	}
	//返回链表当前元素个数
	int List_GetLength() override
	{
		return length;
	}
	//返回第pos个元素的元素值
	DataType List_GetElement(int pos) override
	{
		try
		{
			if (pos<1 || pos>this->length)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Position is not exist" << std::endl;
			exit(0);
		}
		Node_SingleLinked<DataType>* node = this->front;
		for (int i = 1; i <= Index(pos); i++)
			node = node->next;
		return node->element;
	}
	//显示整个链表
	void List_Show(const char* string) override
	{
		std::cout << string << std::endl
			<< "[front]: " << front << std::endl
			<< "[length]: " << length << std::endl
			<< "Head->";
		for (int index = 1; index <= length; index++)
			std::cout << '[' << index << ':' << List_GetElement(index) << "]->";
		std::cout << "NULL\n";
	}
	//定位并返回单链表第pos个元素节点
public:///元素操作
	Node_SingleLinked<DataType>* Element_Locate(int pos) override
	{
		try
		{//判断非空且不超过l->length
			if (pos <= 0)
				throw 1;
			if (pos > length)
				throw 2;
		}
		catch (int x)
		{
			if (x == 1)
			{
				std::cout << "LocateNode Faild: Position < 0" << std::endl;
				exit(0);
			}
			if (x == 2)
			{
				std::cout << "LocateNode Faild: Position > List Length" << std::endl;
				exit(0);
			}
		}

		Node_SingleLinked<DataType>* p = this->front;
		for (int i = 1; i < pos; i++)
		{//遍历定位到第pos个元素节点
			p = p->next;
		}
		return p;
	}
	//定位并返回node节点的前驱节点
	//(遍历链表)
	Node_SingleLinked<DataType>* Element_Prior(const Node_SingleLinked<DataType>* const node) override
	{
		try
		{
			if (length <= 1 || !front)
				throw 1;
		}
		catch (...)
		{
			std::cout << "前驱节点不存在" << std::endl;
			exit(0);
		}
		Node_SingleLinked<DataType>* t = front;
		while (t->next != node)
		{///定位前驱节点
			t = t->next;
		}
		return t;
	}
	//定位并返回node节点的后继节点
	Node_SingleLinked<DataType>* Element_Next(const Node_SingleLinked<DataType>* const node) override
	{
		return node->next;
	}
	//在单链表第pos位置插入新建的元素element
	void Element_Insert(int pos, DataType element) override
	{
		try
		{
			if (pos< 1 || pos>length+1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Insert Faild: Illegal position" << std::endl;
			exit(0);
		}
		Node_SingleLinked<DataType>* p = new Node_SingleLinked<DataType>;
		p->Init(element);
		if (pos == 1)
		{
			p->next = front;
			front = p;
			length++;
		}
		else
		{
			Node_SingleLinked<DataType>* p_pri;
			p_pri= Element_Locate(pos-1);
			p->next = p_pri->next;
			p_pri->next = p;
			length++;
		}
	}
	//删除链表L的第pos个元素节点
	DataType Element_Delete(int pos) override
	{
		Node_SingleLinked<DataType>* node = Element_Locate(pos - 1);
		Node_SingleLinked<DataType>* del = node->next;
		node->next = del->next;
		DataType temp = del->element;
		delete del;
		length--;
		return temp;
	}

public:
	//单链表头插法
	void Insert_Front(DataType element)
	{
		Node_SingleLinked<DataType>* node = new Node_SingleLinked<DataType>;
		node->Init(element);
		if (front)
		{
			node->next = front;
			front = node;
		}
		else
			front = node;
		length++;
	}

	
};










