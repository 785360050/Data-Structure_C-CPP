#pragma once

#include "Liner_Stack_ADT.hpp"

template <typename DataType>
struct Stack:public Stack_ADT<DataType>
{
protected:
	int maxsize;		///元素上限
	///注:若maxszie为size_t类时signed与unsigned类型比较会默认转为unsigned后再比较
protected:
	Stack(int maxsize = 5)
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
	virtual ~Stack() = default;
public:///栈操作
	//清空栈
	virtual void Stack_Clear() = 0;
	//判断是否栈空
	virtual bool Stack_CheckEmpty() = 0;
	//返回栈长度(元素个数)
	virtual int Stack_GetLength() = 0;
	//返回栈顶元素
	virtual DataType Stack_GetTop() = 0;
public:///元素操作
	//元素入栈
	virtual void Element_Push(DataType element) = 0;
	//元素出栈
	virtual void Element_Pop() = 0;

public:
	virtual void Stack_Show(const std::string& string) = 0;
};