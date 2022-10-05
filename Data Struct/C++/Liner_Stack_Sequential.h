#pragma once


#include <iostream>

#include "Liner_Stack_ADT.h"



template <typename DataType>
class Sequence_Stack:public Stack<DataType>
{///递增空栈
private:
	int top;
	int maxsize;
	DataType* element;
public:
	//初始化头节点信息
	Sequence_Stack()
	{
		top = 0;
		element = nullptr;
		maxsize = 0;
	}
public:///栈操作
	//初始化栈空间
	void Stack_Init(int maxsize) override
	{///申请空间并置为0
		element = new DataType[maxsize];
		memset(element, 0, sizeof(DataType) * maxsize);
		this->maxsize = maxsize;
	}
	//销毁栈
	void Stack_Destroy()
	{
		try
		{
			if (!element)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Stack is not exist" << std::endl;
			return;
		}
		delete[] element;
		element = nullptr;
	}
	//清空栈
	void Stack_Clear()
	{///重置栈内存为0
		memset(element, 0, sizeof(DataType) * maxsize);
		top = 0;
	}
	//判断是否栈空
	bool Stack_CheckEmpty()
	{
		if (top == 0)
			return true;
		return false;
	}
	//返回栈长度(元素个数)
	int Stack_GetLength()
	{///满栈top从0开始
		return top;
	}
	//返回栈顶元素
	DataType Stack_GetTop()
	{
		try
		{
			if (Stack_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Stack is Empty" << std::endl;
			return NULL;
		}
		return element[--top];//top不一定是栈顶索引
	}
public:///元素操作
	//元素入栈
	void Element_Push(DataType element)
	{
		try
		{
			if (top >= maxsize + 1)
			{
				throw 1;
			}
		}
		catch (...)
		{
			std::cout << "Stack Overflow" << std::endl;
			return;
		}
		this->element[top] = element;
		top++;
	}
	//元素出栈
	DataType Element_Pop()
	{
		try
		{
			if (top <1 )
			{
				throw 1;
			}
		}
		catch (...)
		{
			std::cout << "Stack is Empty" << std::endl;
			exit(0);
		}
		top--;
		return this->element[top];
	}

public:
	//输出栈所有信息
	void Stack_Show(const char* string)
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:\n"
			<< " [" << Stack_GetLength() << '/' << maxsize << ']' << std::endl
			<< "Bottom-";
		for (int index = 0; index < maxsize; index++)
			std::cout << '[' << index << ':' << element[index] << "]-";
		std::cout << "TOP[" << top << ']' << std::endl;
	}
};










