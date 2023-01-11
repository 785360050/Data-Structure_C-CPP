#pragma once


#include <iostream>

#include "../Liner_Stack_ADT.h"



template <typename DataType>
class Sequence_Stack:public Stack<DataType>
{///空栈
private:
	int top;
	size_t maxsize;
	DataType* element;
public:
	//初始化头节点信息
	Sequence_Stack()
		:top{ 0 }, element{ nullptr }, maxsize{ 0 } {};
	//初始化栈空间
	Sequence_Stack(size_t maxsize)
	{///申请空间并置为默认值
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
		top = 0;
		element = new DataType[maxsize]{};
		this->maxsize = maxsize;
	}
public:///栈操作
	//销毁栈
	void Stack_Destroy() override
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
		top = 0;
		element = nullptr;
	}
	//清空栈
	void Stack_Clear() override
	{///重置栈内存为0
		memset(element, 0, sizeof(DataType) * maxsize);
		top = 0;
	}
	//判断是否栈空
	bool Stack_CheckEmpty() { return top == 0 ? true : false; };
	//返回栈长度(元素个数)
	int Stack_GetLength() override
	{///满栈top从0开始
		return top;
	}
	//返回栈顶元素
	DataType Stack_GetTop() override
	{///读取栈顶元素
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
		return element[top - 1];//top不一定是栈顶索引,此处为满栈
	}
public:///元素操作
	//元素入栈
	void Element_Push(DataType element) override
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
		this->element[top++] = element;
	}
	//元素出栈
	DataType Element_Pop() override
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
		return this->element[--top];
	}

public:
	//输出栈所有信息
	void Stack_Show(string string) override
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










