#pragma once


#include <iostream>

#include "../Liner_Stack.h"
#include "../../../Node.h"
#include "../../List_Node.h"


template <typename DataType, typename NodeType = List_Node_SingleWay<DataType>>
class Link_Stack:public Stack<DataType>
{///空栈
protected:
	NodeType* top;
	int length;			///当前元素个数
private:
	bool Stack_CheckFull()
	{return length == this->maxsize ? true : false;}
public:///对象维护头节点，存放栈信息
	Link_Stack(int maxsize=5)
		:Stack<DataType>(maxsize),
		top{ nullptr }, length{ 0 } {};
	//销毁栈
	~Link_Stack() 
	{
		Stack_Clear();
		std::cout << "Link_Stack Destroyed" << std::endl;
	}
public:///栈操作
	//清空栈(等价于销毁栈空间)
	///由于链栈空间利用率高，不存在空节点，所以清空链表元素==销毁所有链表节点
	void Stack_Clear() override
	{
		while (top)
		{
			NodeType* del = top;
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
	void Stack_Show(const std::string& string) override
	{
		NodeType* node = top;
		std::cout << string << std::endl
			<< "[Length/Maxsize]:\n" << '[' << Stack_GetLength() << '/'
			<< this->maxsize << ']' << std::endl
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
		NodeType* node = new NodeType(element, top);
		top = node;
		++length;
		
	}
	//元素出栈
	void Element_Pop() override
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
			return ;
		}
		NodeType* node = top;
		top = top->next;
		DataType x = node->element;
		delete node;
		--length;
	}
	//更新节点元素值
};




















