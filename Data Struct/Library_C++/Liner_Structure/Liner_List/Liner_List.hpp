// #pragma once

// #include <exception>
// #include <iostream>
// #include "Liner_List_ADT.hpp"

// namespace Implement
// {

// 	// template <typename ElementType>
// 	template <typename ElementType>
// 	class Sequential_List
// 	{
// 	protected:
// 		ElementType *storage{}; /// 指向存储结构
// 		size_t size{};	  /// 当前元素个数
// 		size_t capcity{};	  /// 当前最大容量
// 	public:
// 		// 初始化表头
// 		Sequential_List() 
// 		{ static_assert(ADT::Liner_Sequential_List<Base::Sequential_List<ElementType>,ElementType>); }

// 		// 创建有maxsize个元素空间的顺序表，返回表首地址
// 		Sequential_List(size_t maxsize) : capcity{capcity}
// 		{ static_assert(ADT::Liner_Sequential_List<Base::Sequential_List<ElementType>, ElementType>); };

// 		virtual ~Sequential_List() = default;
// 		// {
// 		// 	if (this->front)
// 		// 		delete[] this->front;
// 		// 	else
// 		// 		throw std::runtime_error("RAII Failed, Memeory Missing");
// 		// }

// 	// protected:
// 	// 	size_t Index(size_t pos) const
// 	// 	{ /// 位序转元素索引
// 	// 		try
// 	// 		{
// 	// 			if (pos == 0)
// 	// 				throw std::logic_error("size_t pos == 0");
// 	// 			if (pos == 0 - 1)
// 	// 				throw std::logic_error("size_t pos == max");
// 	// 		}
// 	// 		catch (const std::exception &e)
// 	// 		{
// 	// 			std::cout << e.what() << std::endl;
// 	// 			return {};
// 	// 		}
// 	// 		return --pos;
// 	// 	}

// 	public: /// 链表操作
// 		virtual void Clear() = 0;
// 		// {
// 		// 	try
// 		// 	{
// 		// 		if (!this->front)
// 		// 			throw 1;
// 		// 	}
// 		// 	catch (...)
// 		// 	{
// 		// 		std::cout << "List is not exist" << std::endl;
// 		// 		return;
// 		// 	}
// 		// 	memset(this->front, 0, maxsize * sizeof(ElementType));
// 		// 	this->length = 0;
// 		// }
// 		// 返回当前最大容量
// 		size_t Size() const { return size; }

// 		/// @brief 返回index位置上的元素引用
// 		/// @param index 从0开始
// 		/// @note 越界会抛出异常
// 		ElementType& operator[](std::size_t index)
// 		{
// 			if (index < 0 || index >= size)
// 				throw std::out_of_range();
// 			return storage[index];
// 		}

// 	public: /// 元素操作

// 		// 插入元素
// 		virtual void Element_Insert(size_t pos, ElementType elem) = 0;
// 		// 删除元素
// 		virtual ElementType Element_Delete(size_t pos) = 0;

// 	public:
// 		// 显示线性表所有信息
// 		virtual void List_Show(const string &string)
// 		{
// 			std::cout << string << std::endl
// 					  << "[Length/Maxsize]:\n"
// 					  << " [" << size << '/' << capcity << ']' << std::endl
// 					  << "Storage->";
// 			for (int index = 0; index < capcity; index++)
// 				std::cout << '[' << index << ':' << this->storage[index] << "]-";
// 			std::cout << "End\n";
// 		}
// 	};

	
// };