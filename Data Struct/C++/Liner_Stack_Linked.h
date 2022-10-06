#pragma once


#include <iostream>

#include "Liner_Stack_ADT.h"


template <typename DataType>
struct Stack_Node
{///链栈单链节点
	DataType element;
	Stack_Node* next;
public:
	//格式化节点内元素值为element
	void Node_Init(DataType element, Stack_Node<DataType>* next=nullptr)
	{
		this->element = element;
		this->next = next;
	}
};

template <typename DataType>
class Link_Stack:public Stack<DataType>
{///空栈
private:
	Stack_Node<DataType>* top;
	int length;
	int maxsize;
public:///对象维护头节点，存放栈信息
	//初始化头节点信息
	Link_Stack()
	{
		top = nullptr;
		length = 0;
	}
public:///栈操作
	//初始化栈空间，maxsize个元素(节点)空间
	void Stack_Init(int maxsize) override
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
	void Stack_Destroy() override
	{
		try
		{
			if (!top)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Destroy Faild: Stack is not exist" << std::endl;
			return;
		}
		while (top)
		{
			Stack_Node<DataType>* del = top;
			top = top->next;
			delete del;
		}

	}
	//清空栈(等价于销毁栈空间)
	///由于链栈空间利用率高，不存在空节点，所以不存在清空链表元素
	void Stack_Clear() override
	{
		Stack_Destroy();
	}
	//判断是否栈空
	bool Stack_CheckEmpty() override
	{
		if (length == 0)
			return true;
		return false;
	}
	
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
	void Stack_Show(const char* string) override
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
		Stack_Node<DataType>* node = new Stack_Node<DataType>;
		node->Node_Init(element, top);
		top = node;
		length++;
		
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
		length--;
		return x;
	}
	//更新节点元素值


public:
	bool Stack_CheckFull()
	{
		if (length == maxsize)
			return true;
		return false;
	}



};




















