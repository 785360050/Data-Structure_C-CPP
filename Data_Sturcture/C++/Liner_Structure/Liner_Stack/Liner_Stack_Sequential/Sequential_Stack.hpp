#pragma once


#include <iostream>
#include <cstring> //memset

#include "../Stack.hpp"

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

namespace Storage
{
	template <typename ElementType>
	class Sequential_Stack : public Logic::Stack<ElementType>
	{ 
	protected:
		size_t top{};//注意是unsigned 类型
		const size_t top_min{}; // top_min<=top
		const size_t top_max{}; // top<=top_max
		ElementType *storage{nullptr};

	protected:
		bool _Top_In_Range() const { return top_min<=top && top <= top_max; }
		virtual void _Top_Reset() { top = top_min; }

	public:
		Sequential_Stack(ElementType *storage, size_t top_min, size_t top_max)
			: storage{storage}, top_min{top_min}, top_max{top_max}, top{top_min} {}

		// 销毁栈
		virtual ~Sequential_Stack() = default;

	public: /// 栈操作
		// 清空栈
		virtual void Clear()
		{
			while (!this->Is_Empty())
				this->Element_Pop();
		}
		constexpr virtual size_t Get_Capcity() const = 0;
		// 返回栈顶元素
		virtual ElementType &Get_Top() = 0;

	public: /// 元素操作
		// 元素入栈
		virtual void Element_Push(const ElementType& element) = 0;
		virtual void Element_Push(ElementType&& element) = 0;
		// 元素出栈
		virtual void Element_Pop() = 0;

	public:
		// 输出栈所有信息
		virtual void Stack_Show(const std::string &string ="") = 0;
	};
}

/// @brief 空增栈：top=0,Push=top++
/// @note //满时top必定越界
template <typename ElementType, size_t maxsize>
class Sequential_Stack_Empty_Ascending : public Storage::Sequential_Stack<ElementType>
{
protected:
	ElementType array[maxsize]{};

public:
	Sequential_Stack_Empty_Ascending()
		:Storage::Sequential_Stack<ElementType>(array, 0, maxsize){}

public:///栈操作

	constexpr size_t Get_Capcity() const override { return maxsize; }
	// 返回栈顶元素
	virtual ElementType& Get_Top() override
	{///读取栈顶元素
		if (this->Is_Empty())
			throw std::out_of_range("Stack is Empty");
		return array[this->top - 1];
	}
public:///元素操作
	//元素入栈
	virtual void Element_Push(const ElementType& element) override
	{
		if (!this->_Top_In_Range())
			throw std::out_of_range("Stack is full");
		this->array[this->top++] = element;
		++this->size;
	}
	virtual void Element_Push(ElementType &&element) override
	{
		if (!this->_Top_In_Range())
			throw std::out_of_range("Stack is full");
		this->array[this->top++] = std::move(element);
		++this->size;
	}
	//元素出栈
	virtual void Element_Pop() override
	{
		if (this->top < this->top_min)
			throw std::runtime_error("Stack is Empty");
		
		array[this->top--]=ElementType{};
		--this->size;
	}

public:
	//输出栈所有信息
	virtual void Stack_Show(const std::string& string="") override
	{
		std::cout << string << std::endl
				  << "[Size/Maxsize]:\n"
				  << " [" << this->Get_Size() << '/' << maxsize << ']' << std::endl
				  << "Bottom-";
		for (int index = 0; index < maxsize; index++)
			std::cout << '[' << index << ':' << array[index] << "]-";
		std::cout << "TOP[" << this->top << ']' << std::endl;
	}
};

// Sequential_Stack_Full_Ascending
// Sequential_Stack_Empty_Decending
// Sequential_Stack_Full_Decending

/// @brief 默认使用空增栈实现
template <typename ElementType, size_t maxsize>
using Sequential_Stack = Sequential_Stack_Empty_Ascending<ElementType, maxsize>;

// template <typename ElementType>
// class Sequential_Stack_Full_Ascending :public Sequential_Stack<ElementType>
// {

// protected:
// 	void _Top_Reset() override final
// 	{this->top=-1;}
// public:
// 	Sequential_Stack_Full_Ascending(int maxsize)
// 	{///申请空间并置为默认值
// 		try
// 		{
// 			if (maxsize < 1)
// 				throw 1;
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack Init Failed: maxsize must be greater than 1" << std::endl;
// 			return;
// 		}
// 		_Top_Reset();
// 		this->element = new ElementType[maxsize]{};
// 		this->maxsize = maxsize;
// 	}
// 	bool Stack_CheckEmpty() override { return this->top == -1 ? true : false; };
// 	//返回栈长度(元素个数)
// 	int Stack_GetLength() override final
// 	{///满栈top从0开始
// 		return this->top + 1;
// 	}
// //	//返回栈顶元素
// 	ElementType Stack_GetTop() override final
// 	{///读取栈顶元素
// 		try
// 		{
// 			if (Stack_CheckEmpty())
// 				throw 1;
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack is Empty" << std::endl;
// 			return NULL;
// 		}
// 		return this->element[this->top];
// 	}
// public:///元素操作
// 	//元素入栈
// 	void Element_Push(ElementType element) override final
// 	{
// 		try
// 		{
// 			if (this->top >= int(this->maxsize))
// 				throw 1;
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack Overflow" << std::endl;
// 			return;
// 		}
// 		this->element[++this->top] = element;
// 	}
// 	//元素出栈
// 	void Element_Pop() override final
// 	{
// 		try
// 		{
// 			if (this->top < 0)
// 			{
// 				throw 1;
// 			}
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack is Empty" << std::endl;
// 			return;
// 		}
// 		--this->top;
// 	}
// };

// template <typename ElementType>
// class Sequential_Stack_Empty_Decending :public Sequential_Stack<ElementType>
// {
// protected:
// 	void _Top_Reset() override final
// 	{this->top = this->maxsize-1;}
// public:
// 	Sequential_Stack_Empty_Decending(int maxsize)
// 	{///申请空间并置为默认值
// 		try
// 		{
// 			if (maxsize < 1)
// 				throw 1;
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack Init Failed: maxsize must be greater than 1" << std::endl;
// 			return;
// 		}
// 		this->maxsize = maxsize;
// 		_Top_Reset();
// 		this->element = new ElementType[maxsize]{};
// 	}
// 	bool Stack_CheckEmpty() override { return this->top +1 == this->maxsize ? true : false; };
// 	//返回栈长度(元素个数)
// 	int Stack_GetLength() override final
// 	{return this->maxsize - this->top-1;}
// 	//	//返回栈顶元素
// 	ElementType Stack_GetTop() override final
// 	{///读取栈顶元素
// 		try
// 		{
// 			if (Stack_CheckEmpty())
// 				throw 1;
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack is Empty" << std::endl;
// 			return NULL;
// 		}
// 		return this->element[this->top + 1];
// 	}
// public:///元素操作
// 	//元素入栈
// 	void Element_Push(ElementType element) override final
// 	{
// 		try
// 		{
// 			int top = this->top, maxsize = this->maxsize;
// 			if (top < 0)
// 				throw 1;
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack Overflow" << std::endl;
// 			return;
// 		}
// 		this->element[this->top--] = element;
// 	}
// 	//元素出栈
// 	void Element_Pop() override final
// 	{
// 		try
// 		{
// 			int top = this->top, maxsize = this->maxsize;
// 			if (top >= maxsize)
// 			{
// 				throw 1;
// 			}
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack is Empty" << std::endl;
// 			return;
// 		}
// 		++this->top;
// 	}

// 	void Stack_Show(const std::string& string) override
// 	{
// 		std::cout << string << std::endl
// 			<< "[Length/Maxsize]:\n"
// 			<< " [" << Stack_GetLength() << '/' << this->maxsize << ']' << std::endl
// 			<< "TOP[" << this->top << "]-";
// 		for (int index = 0; index < this->maxsize; ++index)
// 			std::cout << '[' << index << ':' << this->element[index] << "]-";
// 		std::cout << "Bottom" << std::endl;
// 	}
// };

// template <typename ElementType>
// class Sequential_Stack_Full_Decending :public Sequential_Stack<ElementType>
// {
// protected:
// 	void _Top_Reset() override final
// 	{this->top = this->maxsize;}
// public:
// 	Sequential_Stack_Full_Decending(int maxsize)
// 	{///申请空间并置为默认值
// 		try
// 		{
// 			if (maxsize < 1)
// 				throw 1;
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack Init Failed: maxsize must be greater than 1" << std::endl;
// 			return;
// 		}
// 		this->maxsize = maxsize;
// 		_Top_Reset();
// 		this->element = new ElementType[maxsize]{};
// 	}
// 	bool Stack_CheckEmpty() override { return this->top == this->maxsize ? true : false; };
// 	//返回栈长度(元素个数)
// 	int Stack_GetLength() override final
// 	{///满栈top从0开始
// 		return this->maxsize - this->top;
// 	}
// 	//	//返回栈顶元素
// 	ElementType Stack_GetTop() override final
// 	{///读取栈顶元素
// 		try
// 		{
// 			if (Stack_CheckEmpty())
// 				throw 1;
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack is Empty" << std::endl;
// 			return NULL;
// 		}
// 		return this->element[this->top];
// 	}
// public:///元素操作
// 	//元素入栈
// 	void Element_Push(ElementType element) override final
// 	{
// 		try
// 		{
// 			if (this->top <= 0)
// 				throw 1;
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack Overflow" << std::endl;
// 			return;
// 		}
// 		this->element[--this->top] = element;
// 	}
// 	//元素出栈
// 	void Element_Pop() override final
// 	{
// 		try
// 		{
// 			if (this->top >=int(this->maxsize))
// 			{
// 				throw 1;
// 			}
// 		}
// 		catch (...)
// 		{
// 			std::cout << "Stack is Empty" << std::endl;
// 			return;
// 		}
// 		++this->top;
// 	}

// 	void Stack_Show(const std::string& string) override
// 	{
// 		std::cout << string << std::endl
// 			<< "[Length/Maxsize]:\n"
// 			<< " [" << Stack_GetLength() << '/' << this->maxsize << ']' << std::endl
// 			<< "TOP[" << this->top << "]-";
// 		for (int index = 0; index < this->maxsize; ++index)
// 			std::cout << '[' << index << ':' << this->element[index] << "]-";
// 		std::cout << "Bottom" << std::endl;
// 	}
// };
