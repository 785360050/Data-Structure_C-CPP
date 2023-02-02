#pragma once

#include <string>
using std::string;

template <typename DataType>
struct Stack_ADT
{///Interface
	virtual ~Stack_ADT() = default;
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
	virtual void Stack_Show(const std::string& string = "") = 0;
};





