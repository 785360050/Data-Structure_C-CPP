#pragma once

#include "Object.h"
#include <iostream>

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
class List_SingleLinked:public Liner_Structure<Node_SingleLinked<int>,int>
{
private:
	Node_SingleLinked<DataType>* front;///模板型成员变量
	int length;
public:
	//初始化头节点信息，存放链表信息
	void List_Init() override
	{
		length = 0;
		front = NULL;
	}
	//清空所有表节点
	void List_Clear() override
	{
		while (front)
		{
			Node_SingleLinked<DataType>* temp = front;
			front = front->next;
			delete temp;
		}
	}
	//释放整个表
	void List_Destroy() override
	{
		List_Clear();
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
	//显示整个链表
	void List_Show(const char* string) override
	{
		std::cout << string << std::endl
			<< "[front]: " << front << std::endl
			<< "[length]: " << length << std::endl
			<< "Head->";
		for (int index = 1; index <= length; index++)
			std::cout << '[' << index << ':' << Element_Show(Element_Locate(index)) << "]->";
		std::cout << "NULL\n";
	}
	//定位并返回单链表第pos个元素节点
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
	void Element_Delete(int pos) override
	{
		Node_SingleLinked<DataType>* node = Element_Locate(pos - 1);
		Node_SingleLinked<DataType>* del = node->next;
		node->next = del->next;
		delete del;
		length--;
	}
	//返回当前节点node的元素值
	DataType Element_Show(Node_SingleLinked<DataType>* node) override
	{
		try
		{
			if (!node)
				throw 1;
		}
		catch (...)
		{
			std::cout << "当前节点不存在" << std::endl;
			exit(0);
		}
		return node->element;
	}
};










