#pragma once


#include <iostream>

#include "../Liner_Stack_ADT.h"
#include "../../../Node.h"
#include "../../List_Node.h"

//template <typename DataType>
//struct Stack_Node:public Node<DataType>
//{///链栈单链节点
//	Stack_Node* next;
//public:
//	//格式化节点内元素值为element
//	Stack_Node()
//		:Node<DataType>(), next{nullptr} {};
//	Stack_Node(DataType element, Stack_Node<DataType>* next = nullptr)
//		:Node<DataType>(element), next{ next } {};
//};
template <typename DataType>
using Stack_Node = List_Node_SingleWay<DataType>;

template <typename DataType>
class Link_Stack:public Stack<DataType>
{///空栈
protected:
	Stack_Node<DataType>* top;
	int length;			///当前元素个数
	int maxsize;		///链栈元素上限
private:
	bool Stack_CheckFull()
	{return length == maxsize ? true : false;}
public:///对象维护头节点，存放栈信息
	Link_Stack()
		:top{ nullptr }, length{ 0 } {};
	Link_Stack(int maxsize)
	{
		try
		{
			if (maxsize < 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Stack Init Failed: maxsize must be greater than 1" << std::endl;
			return;
		}
		this->maxsize = maxsize;
	}
	//销毁栈
	~Link_Stack() 
	{
		while (top)
		{
			Stack_Node<DataType>* del = top;
			top = top->next;
			delete del;
		}
		std::cout << "Link_Stack Destroyed" << std::endl;
	}
public:///栈操作
	//清空栈(等价于销毁栈空间)
	///由于链栈空间利用率高，不存在空节点，所以清空链表元素==销毁所有链表节点
	void Stack_Clear() override
	{
		while (top)
		{
			Stack_Node<DataType>* del = top;
			top = top->next;
			delete del;
		}
	}
	//判断是否栈空
	bool Stack_CheckEmpty() override
	{return length == 0 ? true : false;}
	//返回栈长度(元素个数)
	int Stack_GetLength() override
	{
		return length;
	}
	//返回栈顶元素
	DataType Stack_GetTop() override
	{
		return top->element;
	}
	//输出栈所有信息
	void Stack_Show(string string) override
	{
		Stack_Node<DataType>* node = top;
		std::cout << string << std::endl
			<< "[Length/Maxsize]:\n" << '[' << Stack_GetLength() << '/'
			<< maxsize << ']' << std::endl
			<< "Top->";
		for (int index = 1; index <= length; index++,node=node->next)
			std::cout << '[' << index << ':' << node->element << "]->";
		std::cout << "Bottom(NULL)" << std::endl;
	}
public:///元素操作
	//元素入栈
	void Element_Push(DataType element) override
	{
		try
		{
			if (Stack_CheckFull())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Stack is Full" << std::endl;
			return;
		}
		Stack_Node<DataType>* node = new Stack_Node<DataType>(element, top);
		top = node;
		++length;
		
	}
	//元素出栈
	DataType Element_Pop() override
	{
		try
		{
			if (Stack_CheckEmpty())
			{
				throw 1;
			}
		}
		catch (...)
		{
			std::cout << "Stack is empty" << std::endl;
			return NULL;
		}
		Stack_Node<DataType>* node = top;
		top = top->next;
		DataType x = node->element;
		delete node;
		--length;
		return x;
	}
	//更新节点元素值
};




















