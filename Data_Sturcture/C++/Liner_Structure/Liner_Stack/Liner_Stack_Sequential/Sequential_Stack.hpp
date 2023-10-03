#pragma once


#include <iostream>
#include <cstring> //memset

#include "../Liner_Stack.hpp"

/// ============================================================================================================
/// 		 四种类型：满增栈、满减栈、空增栈、空减栈。
/// ============================================================================================================
/// 满、空栈区别：根据当前指针所在位置是否有东西。
/// 满栈（Full stack）：栈指针指向最后压入栈的数据，数据入栈时，sp先减一（或加一）再入栈。
/// 空栈（Empty stack）：栈指针指向下一个将要放入数据的位置，数据入栈时，先入栈sp再减一（或加一）。
///
/// 增、减栈区别：根据堆栈的生成方向不同。
/// 递增堆栈(Ascending stack)：堆栈由低地址向高地址生长。
/// 递减堆栈(Decending stack)：堆栈由高地址向低地址生长。
/// ============================================================================================================

///Sequence_Stack_Empty_Ascending
template <typename DataType,size_t capcity>
class Sequence_Stack:public Logic::Stack<DataType>
{///默认为空增栈：top=0,Push=top++
protected:
	int top{};			
	DataType element[capcity]{};
protected:
	virtual void Top_Reset()
	{top=0;}
public:
	Sequence_Stack() = default;
		:Logic::Stack(capcity)
	{
		Top_Reset();
	}

	//销毁栈
	~Sequence_Stack() override
	{
		// if (element)
		// {
		// 	delete[] element;
		// 	Top_Reset();
		// 	element = nullptr;
		// }
		Top_Reset();
		std::cout << "Sequence_Stack Destroyed" << std::endl;
	}
public:///栈操作
	//清空栈
	void Stack_Clear() override
	{///重置栈内存为0
		// memset(element, 0, sizeof(DataType) * this->maxsize);
		while(!Is_Empty())
			this->Element_Pop();
		this->Top_Reset();
	}
	//判断是否栈空
	virtual bool Is_Empty() { return top == 0 ? true : false; };
	//返回栈长度(元素个数)
	virtual size_t Get_Size() override const { return top; }
	size_t Get_Capcity() const { return capcity; }
	// 返回栈顶元素
	virtual DataType& Get_Top() override
	{///读取栈顶元素
		if (Stack_CheckEmpty())
			throw std::out_of_range("Stack is Empty");
		return element[top - 1];//top不一定是栈顶索引,此处为满栈
	}
public:///元素操作
	//元素入栈
	virtual void Element_Push(DataType element) override
	{
		if (top >= this->maxsize + 1)
			throw std::runtime_error("Stack is full");
		this->element[top++] = element;
	}
	//元素出栈
	virtual void Element_Pop() override
	{
		if (top <1 )
			throw std::runtime_error("Stack is Empty");
		--top;
	}

public:
	//输出栈所有信息
	virtual void Stack_Show(const std::string& string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:\n"
			<< " [" << Get_Size() << '/' << this->maxsize << ']' << std::endl
			<< "Bottom-";
		for (int index = 0; index < this->maxsize; index++)
			std::cout << '[' << index << ':' << element[index] << "]-";
		std::cout << "TOP[" << top << ']' << std::endl;
	}
};

template <typename DataType>
class Sequence_Stack_Full_Ascending :public Sequence_Stack<DataType>
{
protected:
	void Top_Reset() override final
	{this->top=-1;}
public:
	Sequence_Stack_Full_Ascending(int maxsize)
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
		Top_Reset();
		this->element = new DataType[maxsize]{};
		this->maxsize = maxsize;
	}
	bool Stack_CheckEmpty() override { return this->top == -1 ? true : false; };
	//返回栈长度(元素个数)
	int Stack_GetLength() override final
	{///满栈top从0开始
		return this->top + 1;
	}
//	//返回栈顶元素
	DataType Stack_GetTop() override final
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
		return this->element[this->top];
	}
public:///元素操作
	//元素入栈
	void Element_Push(DataType element) override final
	{
		try
		{
			if (this->top >= int(this->maxsize))
				throw 1;
		}
		catch (...)
		{
			std::cout << "Stack Overflow" << std::endl;
			return;
		}
		this->element[++this->top] = element;
	}
	//元素出栈
	void Element_Pop() override final
	{
		try
		{
			if (this->top < 0)
			{
				throw 1;
			}
		}
		catch (...)
		{
			std::cout << "Stack is Empty" << std::endl;
			return;
		}
		--this->top;
	}
};

template <typename DataType>
class Sequence_Stack_Empty_Decending :public Sequence_Stack<DataType>
{
protected:
	void Top_Reset() override final
	{this->top = this->maxsize-1;}
public:
	Sequence_Stack_Empty_Decending(int maxsize)
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
		this->maxsize = maxsize;
		Top_Reset();
		this->element = new DataType[maxsize]{};
	}
	bool Stack_CheckEmpty() override { return this->top +1 == this->maxsize ? true : false; };
	//返回栈长度(元素个数)
	int Stack_GetLength() override final
	{return this->maxsize - this->top-1;}
	//	//返回栈顶元素
	DataType Stack_GetTop() override final
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
		return this->element[this->top + 1];
	}
public:///元素操作
	//元素入栈
	void Element_Push(DataType element) override final
	{
		try
		{
			int top = this->top, maxsize = this->maxsize;
			if (top < 0)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Stack Overflow" << std::endl;
			return;
		}
		this->element[this->top--] = element;
	}
	//元素出栈
	void Element_Pop() override final
	{
		try
		{
			int top = this->top, maxsize = this->maxsize;
			if (top >= maxsize)
			{
				throw 1;
			}
		}
		catch (...)
		{
			std::cout << "Stack is Empty" << std::endl;
			return;
		}
		++this->top;
	}

	void Stack_Show(const std::string& string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:\n"
			<< " [" << Stack_GetLength() << '/' << this->maxsize << ']' << std::endl
			<< "TOP[" << this->top << "]-";
		for (int index = 0; index < this->maxsize; ++index)
			std::cout << '[' << index << ':' << this->element[index] << "]-";
		std::cout << "Bottom" << std::endl;
	}
};

template <typename DataType>
class Sequence_Stack_Full_Decending :public Sequence_Stack<DataType>
{
protected:
	void Top_Reset() override final
	{this->top = this->maxsize;}
public:
	Sequence_Stack_Full_Decending(int maxsize)
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
		this->maxsize = maxsize;
		Top_Reset();
		this->element = new DataType[maxsize]{};
	}
	bool Stack_CheckEmpty() override { return this->top == this->maxsize ? true : false; };
	//返回栈长度(元素个数)
	int Stack_GetLength() override final
	{///满栈top从0开始
		return this->maxsize - this->top;
	}
	//	//返回栈顶元素
	DataType Stack_GetTop() override final
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
		return this->element[this->top];
	}
public:///元素操作
	//元素入栈
	void Element_Push(DataType element) override final
	{
		try
		{
			if (this->top <= 0)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Stack Overflow" << std::endl;
			return;
		}
		this->element[--this->top] = element;
	}
	//元素出栈
	void Element_Pop() override final
	{
		try
		{
			if (this->top >=int(this->maxsize))
			{
				throw 1;
			}
		}
		catch (...)
		{
			std::cout << "Stack is Empty" << std::endl;
			return;
		}
		++this->top;
	}

	void Stack_Show(const std::string& string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:\n"
			<< " [" << Stack_GetLength() << '/' << this->maxsize << ']' << std::endl
			<< "TOP[" << this->top << "]-";
		for (int index = 0; index < this->maxsize; ++index)
			std::cout << '[' << index << ':' << this->element[index] << "]-";
		std::cout << "Bottom" << std::endl;
	}
};


