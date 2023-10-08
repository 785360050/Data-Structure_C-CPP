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
/// 以下的实现中
/// 1. 空增栈、空减栈申请maxsize个元素的栈空间，注意栈满时top=top_max,指向非法的越界空间
/// 2. 满增栈、满减栈申请maxsize+1个元素的栈空间，冗余的一个元素空间用于初始时指向top_min位置
/// ============================================================================================================

namespace Storage
{
	template <typename ElementType>
	class Sequential_Stack : public Logic::Stack<ElementType>
	{
	protected:
		size_t top{};				   // 注意是unsigned 类型
		const size_t top_min{};		   // top_min<=top
		ElementType *const storage{nullptr}; // 指向派生类的数组

	protected:
		virtual void _Top_Reset() { top = top_min; }

	public:
		Sequential_Stack(ElementType *storage, size_t top_min)
			: top{top_min}, top_min{top_min},storage{storage} {}
		Sequential_Stack(const Storage::Sequential_Stack<ElementType> &other)
			: Logic::Stack<ElementType>(other.size), top{other.top}, top_min{other.top_min} {}
		Sequential_Stack(Sequential_Stack<ElementType> &&other)
			: Logic::Stack<ElementType>(other.size), top{other.top}, top_min{other.top_min}
		{
			other.size = 0;
			other._Top_Reset();
		}
		Sequential_Stack &operator=(const Sequential_Stack<ElementType> &other)
		{
			if (this == &other)
				throw std::logic_error("Self Copied");
			this->size = other.size;
			top = other.top;
			top_min = other.top_min;
			return *this;
		}
		Sequential_Stack &operator=(Sequential_Stack<ElementType> &&other)
		{
			if (this == &other)
				throw std::logic_error("Self Copied");
			this->size = other.size;
			other.size = 0;
			top = other.top;
			top_min = other.top_min;
			other._Top_Reset();
			return *this;
		}

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
		virtual void Element_Push(const ElementType &element) = 0;
		virtual void Element_Push(ElementType &&element) = 0;
		// 元素出栈
		virtual void Element_Pop() = 0;

	public:
		// 输出栈所有信息
		virtual void Stack_Show(const std::string &string = "") = 0;
	};
}

/// ============================================================================================================
/// 		以下不同的实现仅区别于top处理、内存分配大小和拷贝控制
/// 以下4种都使用栈数组，由于Storage::storage使用指针，所以也可以将数组空间分配在堆上
/// 拷贝控制部分的实现都是相同的，这些冗余的重复代码是由于数组的声明和定义分开导致的，基类声明，派生类定义(栈上分配)
/// ============================================================================================================

/// @brief 空增栈：Push=top++
/// @note top∈[0,maxsize-1]
template <typename ElementType, size_t maxsize>
class Sequential_Stack_Empty_Ascending : public Storage::Sequential_Stack<ElementType>
{
protected:
	ElementType array[maxsize]{};

public:
	Sequential_Stack_Empty_Ascending()
		: Storage::Sequential_Stack<ElementType>(array, 0) {}
	Sequential_Stack_Empty_Ascending(const Sequential_Stack_Empty_Ascending<ElementType, maxsize> &other)
		: Storage::Sequential_Stack<ElementType>(other)
	{
		this->storage = array;
		for (size_t i = 0; i < Get_Capcity(); i++)
			array[i] = other.array[i];
	}
	Sequential_Stack_Empty_Ascending(Sequential_Stack_Empty_Ascending<ElementType, maxsize> &&other)
		: Storage::Sequential_Stack<ElementType>(std::forward<Sequential_Stack_Empty_Ascending<ElementType, maxsize> &&>(other))
	{
		this->storage = array;
		for (size_t i = 0; i < Get_Capcity(); i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}
	}
	Sequential_Stack_Empty_Ascending &
	operator=(const Sequential_Stack_Empty_Ascending<ElementType, maxsize> &other)
	{
		if (this == &other)
			throw std::logic_error("Self Copied");

		this->storage = array;
		Storage::Sequential_Stack<ElementType>::operator=(other);

		for (size_t i = 0; i < Get_Capcity(); i++)
			array[i] = other.array[i];

		return *this;
	}
	Sequential_Stack_Empty_Ascending &
	operator=(Sequential_Stack_Empty_Ascending<ElementType, maxsize> &&other)
	{
		if (this == &other)
			throw std::logic_error("Self Copied");

		this->storage = array;
		Storage::Sequential_Stack<ElementType>::operator=(other);

		for (size_t i = 0; i < Get_Capcity(); i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}

		return *this;
	}

public: /// 栈操作
	constexpr size_t Get_Capcity() const override { return maxsize; }
	// 返回栈顶元素
	virtual ElementType &Get_Top() override
	{ /// 读取栈顶元素
		if (this->Is_Empty())
			throw std::out_of_range("Stack is Empty");
		return array[this->top - 1];
	}

public: /// 元素操作
	// 元素入栈
	virtual void Element_Push(const ElementType &element) override
	{
		if (this->size >= maxsize)
			throw std::out_of_range("Stack is full");
		this->array[this->top++] = element;
		++this->size;
	}
	virtual void Element_Push(ElementType &&element) override
	{
		if (this->size >= maxsize)
			throw std::out_of_range("Stack is full");
		this->array[this->top++] = std::move(element);
		++this->size;
	}
	// 元素出栈
	virtual void Element_Pop() override
	{
		if (this->Is_Empty())
			throw std::out_of_range("Stack is Empty");
		array[--this->top] = ElementType{};
		--this->size;
	}

public:
	// 输出栈所有信息
	virtual void Stack_Show(const std::string &string = "") override
	{
		std::cout << string << std::endl
				  << "[Size/Maxsize]:\n"
				  << " [" << this->Get_Size() << '/' << maxsize << ']' << std::endl
				  << "Bottom-";
		for (size_t index = 0; index < maxsize; index++)
			std::cout << '[' << index << ':' << array[index] << "]-";
		std::cout << "TOP[" << this->top << ']' << std::endl;
	}
};

/// @brief 满增栈：top=0,Push=++top
/// @note top∈[0,maxsize],有效区间=[1,maxsize]
template <typename ElementType, size_t maxsize>
class Sequential_Stack_Full_Ascending : public Storage::Sequential_Stack<ElementType>
{
protected:
	ElementType array[maxsize + 1]{};

public:
	Sequential_Stack_Full_Ascending()
		: Storage::Sequential_Stack<ElementType>(array, 0) {}
	Sequential_Stack_Full_Ascending(const Sequential_Stack_Full_Ascending<ElementType, maxsize> &other)
		: Storage::Sequential_Stack<ElementType>(other)
	{
		this->storage = array;
		for (size_t i = 0; i < Get_Capcity(); i++)
			array[i] = other.array[i];
	}
	Sequential_Stack_Full_Ascending(Sequential_Stack_Full_Ascending<ElementType, maxsize> &&other)
		: Storage::Sequential_Stack<ElementType>(std::forward<Sequential_Stack_Full_Ascending<ElementType, maxsize> &&>(other))
	{
		this->storage = array;
		for (size_t i = 0; i < Get_Capcity(); i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}
	}
	Sequential_Stack_Full_Ascending &
	operator=(const Sequential_Stack_Full_Ascending<ElementType, maxsize> &other)
	{
		if (this == &other)
			throw std::logic_error("Self Copied");

		this->storage = array;
		Storage::Sequential_Stack<ElementType>::operator=(other);

		for (size_t i = 0; i < Get_Capcity(); i++)
			array[i] = other.array[i];

		return *this;
	}
	Sequential_Stack_Full_Ascending &
	operator=(Sequential_Stack_Full_Ascending<ElementType, maxsize> &&other)
	{
		if (this == &other)
			throw std::logic_error("Self Copied");

		this->storage = array;
		Storage::Sequential_Stack<ElementType>::operator=(other);

		for (size_t i = 0; i < Get_Capcity(); i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}

		return *this;
	}

public: /// 栈操作
	constexpr size_t Get_Capcity() const override { return maxsize + 1; }
	// 返回栈顶元素
	virtual ElementType &Get_Top() override
	{ /// 读取栈顶元素
		if (this->Is_Empty())
			throw std::out_of_range("Stack is Empty");
		return array[this->top];
	}

public: /// 元素操作
	// 元素入栈
	virtual void Element_Push(const ElementType &element) override
	{
		if (this->size >= maxsize)
			throw std::out_of_range("Stack is full");
		this->array[++this->top] = element;
		++this->size;
	}
	virtual void Element_Push(ElementType &&element) override
	{
		if (this->size >= maxsize)
			throw std::out_of_range("Stack is full");
		this->array[++this->top] = std::move(element);
		++this->size;
	}
	// 元素出栈
	virtual void Element_Pop() override
	{
		if (this->Is_Empty())
			throw std::out_of_range("Stack is Empty");
		array[this->top--] = ElementType{};
		--this->size;
	}

public:
	// 输出栈所有信息
	virtual void Stack_Show(const std::string &string = "") override
	{
		std::cout << string << std::endl
				  << "[Size/Maxsize]:\n"
				  << " [" << this->Get_Size() << '/' << maxsize << ']' << std::endl
				  << "Bottom-";
		for (int index = 0; index < this->Get_Capcity(); index++)
			std::cout << '[' << index << ':' << array[index] << "]-";
		std::cout << "TOP[" << this->top << ']' << std::endl;
	}
};

/// @brief 空减栈：top=maxsize,Push=top
/// @note top∈[0,maxsize]
template <typename ElementType, size_t maxsize>
class Sequential_Stack_Empty_Descending : public Storage::Sequential_Stack<ElementType>
{
protected:
	ElementType array[maxsize]{};

private:
	void _Top_Reset() override { this->top = maxsize - 1; }

public:
	Sequential_Stack_Empty_Descending()
		: Storage::Sequential_Stack<ElementType>(array, maxsize - 1) {}
	Sequential_Stack_Empty_Descending(const Sequential_Stack_Empty_Descending<ElementType, maxsize> &other)
		: Storage::Sequential_Stack<ElementType>(other)
	{
		this->storage = array;
		for (size_t i = 0; i < Get_Capcity(); i++)
			array[i] = other.array[i];
	}
	Sequential_Stack_Empty_Descending(Sequential_Stack_Empty_Descending<ElementType, maxsize> &&other)
		: Storage::Sequential_Stack<ElementType>(std::forward<Sequential_Stack_Empty_Descending<ElementType, maxsize> &&>(other))
	{
		this->storage = array;
		for (size_t i = 0; i < Get_Capcity(); i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}
	}
	Sequential_Stack_Empty_Descending &
	operator=(const Sequential_Stack_Empty_Descending<ElementType, maxsize> &other)
	{
		if (this == &other)
			throw std::logic_error("Self Copied");

		this->storage = array;
		Storage::Sequential_Stack<ElementType>::operator=(other);

		for (size_t i = 0; i < Get_Capcity(); i++)
			array[i] = other.array[i];

		return *this;
	}
	Sequential_Stack_Empty_Descending &
	operator=(Sequential_Stack_Empty_Descending<ElementType, maxsize> &&other)
	{
		if (this == &other)
			throw std::logic_error("Self Copied");

		this->storage = array;
		Storage::Sequential_Stack<ElementType>::operator=(other);

		for (size_t i = 0; i < Get_Capcity(); i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}

		return *this;
	}

public: /// 栈操作
	constexpr size_t Get_Capcity() const override { return maxsize; }
	// 返回栈顶元素
	virtual ElementType &Get_Top() override
	{ /// 读取栈顶元素
		if (this->Is_Empty())
			throw std::out_of_range("Stack is Empty");
		return array[this->top + 1];
	}

public: /// 元素操作
	// 元素入栈
	virtual void Element_Push(const ElementType &element) override
	{
		if (this->size >= maxsize)
			throw std::out_of_range("Stack is full");
		this->array[this->top--] = element;
		++this->size;
	}
	virtual void Element_Push(ElementType &&element) override
	{
		if (this->size >= maxsize)
			throw std::out_of_range("Stack is full");
		this->array[this->top--] = std::move(element);
		++this->size;
	}
	// 元素出栈
	virtual void Element_Pop() override
	{
		if (this->Is_Empty())
			throw std::out_of_range("Stack is Empty");
		array[++this->top] = ElementType{};
		--this->size;
	}

public:
	// 输出栈所有信息
	virtual void Stack_Show(const std::string &string = "") override
	{
		std::cout << string << std::endl
				  << "[Size/Maxsize]:\n"
				  << " [" << this->Get_Size() << '/' << maxsize << ']' << std::endl
				  << "Bottom-";
		for (int index = 0; index < this->Get_Capcity(); index++)
			std::cout << '[' << index << ':' << array[index] << "]-";
		std::cout << "TOP[" << this->top << ']' << std::endl;
	}
};

/// @brief 满减栈：top=0,Push=++top
/// @note top∈[0,maxsize]
template <typename ElementType, size_t maxsize>
class Sequential_Stack_Full_Descending : public Storage::Sequential_Stack<ElementType>
{
protected:
	ElementType array[maxsize + 1]{};

private:
	void _Top_Reset() override { this->top = maxsize; }

public:
	Sequential_Stack_Full_Descending()
		: Storage::Sequential_Stack<ElementType>(array, maxsize) {}
	Sequential_Stack_Full_Descending(const Sequential_Stack_Full_Descending<ElementType, maxsize> &other)
		: Storage::Sequential_Stack<ElementType>(other)
	{
		this->storage = array;
		for (size_t i = 0; i < Get_Capcity(); i++)
			array[i] = other.array[i];
	}
	Sequential_Stack_Full_Descending(Sequential_Stack_Full_Descending<ElementType, maxsize> &&other)
		: Storage::Sequential_Stack<ElementType>(std::forward<Sequential_Stack_Full_Descending<ElementType, maxsize> &&>(other))
	{
		this->storage = array;
		for (size_t i = 0; i < Get_Capcity(); i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}
	}
	Sequential_Stack_Full_Descending &
	operator=(const Sequential_Stack_Full_Descending<ElementType, maxsize> &other)
	{
		if (this == &other)
			throw std::logic_error("Self Copied");

		this->storage = array;
		Storage::Sequential_Stack<ElementType>::operator=(other);

		for (size_t i = 0; i < Get_Capcity(); i++)
			array[i] = other.array[i];

		return *this;
	}
	Sequential_Stack_Full_Descending &
	operator=(Sequential_Stack_Full_Descending<ElementType, maxsize> &&other)
	{
		if (this == &other)
			throw std::logic_error("Self Copied");

		this->storage = array;
		Storage::Sequential_Stack<ElementType>::operator=(other);

		for (size_t i = 0; i < Get_Capcity(); i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}

		return *this;
	}

public: /// 栈操作
	constexpr size_t Get_Capcity() const override { return maxsize + 1; }
	// 返回栈顶元素
	virtual ElementType &Get_Top() override
	{ /// 读取栈顶元素
		if (this->Is_Empty())
			throw std::out_of_range("Stack is Empty");
		return array[this->top];
	}

public: /// 元素操作
	// 元素入栈
	virtual void Element_Push(const ElementType &element) override
	{
		if (this->size >= maxsize)
			throw std::out_of_range("Stack is full");
		this->array[--this->top] = element;
		++this->size;
	}
	virtual void Element_Push(ElementType &&element) override
	{
		if (this->size >= maxsize)
			throw std::out_of_range("Stack is full");
		this->array[--this->top] = std::move(element);
		++this->size;
	}
	// 元素出栈
	virtual void Element_Pop() override
	{
		if (this->Is_Empty())
			throw std::out_of_range("Stack is Empty");
		array[this->top++] = ElementType{};
		--this->size;
	}

public:
	// 输出栈所有信息
	virtual void Stack_Show(const std::string &string = "") override
	{
		std::cout << string << std::endl
				  << "[Size/Maxsize]:\n"
				  << " [" << this->Get_Size() << '/' << maxsize << ']' << std::endl
				  << "Bottom-";
		for (int index = 0; index < this->Get_Capcity(); index++)
			std::cout << '[' << index << ':' << array[index] << "]-";
		std::cout << "TOP[" << this->top << ']' << std::endl;
	}
};

/// @brief 默认使用空增栈实现
template <typename ElementType, size_t maxsize>
using Sequential_Stack = Sequential_Stack_Empty_Ascending<ElementType, maxsize>;
