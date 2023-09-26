#pragma once

#include <exception>
#include <iostream>
#include "../Liner_List_ADT.hpp"
#include <cstring> //memset
namespace Implement
{

	/// @brief 顺序表 = 数组实现的线性表
	/// @tparam ElementType 元素类型 
	template <typename ElementType>
	class Sequential_List
	{
	protected:
		ElementType *storage{}; /// 指向存储结构
		size_t size{};			/// 当前元素个数
		size_t capcity{};		/// 当前最大容量
	public:
		// 初始化
		Sequential_List()
		{
			static_assert(ADT::Liner_Sequential_List<Implement::Sequential_List<ElementType>, ElementType>);
		}

		// 创建有maxsize个元素空间的顺序表，返回表首地址
		Sequential_List(size_t maxsize) : capcity{maxsize}
		{
			static_assert(ADT::Liner_Sequential_List<Implement::Sequential_List<ElementType>, ElementType>);
		};

		virtual ~Sequential_List() = default;
		// {
		// 	if (this->storage)
		// 		delete[] this->storage;
		// 	else
		// 		throw std::runtime_error("RAII Failed, Memeory Missing");
		// }

		// protected:
		// 	size_t Index(size_t pos) const
		// 	{ /// 位序转元素索引
		// 		try
		// 		{
		// 			if (pos == 0)
		// 				throw std::logic_error("size_t pos == 0");
		// 			if (pos == 0 - 1)
		// 				throw std::logic_error("size_t pos == max");
		// 		}
		// 		catch (const std::exception &e)
		// 		{
		// 			std::cout << e.what() << std::endl;
		// 			return {};
		// 		}
		// 		return --pos;
		// 	}

	public: /// 链表操作
		bool Is_Empty() const { return size; }
		virtual void Clear() 
		{
			if (!this->storage)
				throw std::runtime_error("List is not exist");

			// if (std::is_pointer<ElementType>::value)
			// {

			// 	for (size_t i = 0; i < size; i++)
			// 		delete storage[i];
			// }

			std::memset(this->storage, ElementType(), size * sizeof(ElementType));
			this->size = 0;
		}
		// 返回当前最大容量
		size_t Size() const { return size; }
		size_t Capcity() const { return capcity; }

		/// @brief 返回index位置上的元素引用
		/// @param index 从0开始
		/// @note 越界会抛出异常
		ElementType &operator[](std::size_t index)
		{
			if (index < 0 || index >= capcity)
				throw std::out_of_range("");
			return storage[index];
		}

	public: /// 元素操作
		// 插入元素
		virtual void Element_Insert(size_t pos, ElementType elem) = 0;
		// 删除元素
		virtual void Element_Delete(size_t pos) = 0;

		void Element_Update(size_t pos,ElementType elem)
		{}

	public:
		// 显示线性表所有信息
		virtual void List_Show(const std::string &string)
		{
			std::cout << string << std::endl
					  << "[Size/Maxsize]:\n"
					  << " [" << size << '/' << capcity << ']' << std::endl
					  << "Storage->";
			for (int index = 0; index < capcity; index++)
				std::cout << '[' << index << ':' << this->storage[index] << "]-";
			std::cout << "End\n";
		}
	};

};

/// 静态数组
template <typename DataType, size_t Capcity>
class Sequential_List_Static : public Implement::Sequential_List<DataType>
{
	

public:
	Sequential_List_Static()
		: Implement::Sequential_List<DataType>(Capcity)
	{
		// static_assert(Capcity == 0, "List Init Failed: maxsize must be greater than 1");
		// this->storage = DataType[Capcity]{}; /// 每个元素初始化为DataType默认初始值
		
		// DataType arr[Capcity]={}; /// 每个元素初始化为DataType默认初始值
		// this->storage = arr;
		this->storage = new DataType[Capcity]{};
	}

public:
	void Element_Insert(size_t pos, DataType elem)
	{ /// n个元素有n+1个可插入位置,存储空间不足时不扩展并报错，位置pos非法时候抛出异常并终止插入元素

		if (pos < 0 || pos > this->size + 1)
			throw std::out_of_range("List insert failed: Position out of range");
		if (this->size >= this->capcity)
			throw std::runtime_error("List insert failed: List is full");

		if (this->size == 0)
			this->storage[0] = elem;
		else
		{ /// 从后往前，把当前索引向后搬
			for (size_t index = this->size; pos <= index; index--)
				this->storage[index] = this->storage[index-1];
			this->storage[pos] = elem;
		}
		++this->size;
	}
	void Element_Delete(size_t pos)
	{
		DataType elem = this->storage[pos];
		for (size_t i = pos; i < this->size ; i++)
			this->storage[i] = this->storage[i + 1];
		this->storage[this->size - 1] = DataType{}; /// 末尾格式化
		--this->size;
	}
};

// /// 动态数组
// template <typename DataType>
// class Sequential_List_Vector : public Sequential_List<DataType>
// {
// public:
// 	Sequential_List_Vector()
// 		: Sequential_List<DataType>(){};
// 	Sequential_List_Vector(size_t maxsize)
// 		: Sequential_List<DataType>(maxsize){};

// protected:
// 	// 以2倍为单位扩展收缩空间
// 	void Expand()
// 	{ /// 重新申请2倍的空间，移动原有数据至该空间
// 		if (this->storage)
// 		{
// 			auto expand = new DataType[this->maxsize * 2]{};
// 			memcpy(expand, this->storage, sizeof(DataType) * this->maxsize);
// 			delete[] this->storage;
// 			this->storage = expand;
// 			this->maxsize *= 2;
// 		}
// 	}
// 	void Shrink()
// 	{
// 		if (this->storage)
// 		{
// 			auto shrink = new DataType[this->maxsize / 2]{};
// 			memcpy(shrink, this->storage, sizeof(DataType) * this->size);
// 			delete[] this->storage;
// 			this->storage = shrink;
// 			this->maxsize /= 2;
// 		}
// 	}

// public: /// 元素操作
// 	void Element_Insert(size_t pos, DataType elem)
// 	{ /// n个元素有n+1个可插入位置,存储空间不足时扩展为两倍，位置pos非法时候抛出异常并终止插入元素
// 		try
// 		{
// 			if (pos < 0 || pos > this->size + 1)
// 				throw 2;
// 		}
// 		catch (...)
// 		{
// 			std::cout << "List insert failed: Position out of range" << std::endl;
// 			return;
// 		}
// 		if (this->size >= this->maxsize)
// 			Expand(); /// 空间扩展为2倍
// 		// this->List_Show(" ");
// 		if (this->size == 0)
// 			this->storage[0] = elem;
// 		else
// 		{ /// 从后往前，把当前索引向后搬
// 			for (size_t index = this->Index(this->size); this->Index(pos) <= index; index--)
// 				this->storage[index + 1] = this->storage[index];
// 			this->storage[this->Index(pos)] = elem;
// 		}
// 		++this->size;
// 	}
// 	DataType Element_Delete(size_t pos)
// 	{
// 		DataType elem{this->storage[this->Index(pos)]};
// 		for (size_t i = this->Index(pos); i <= this->Index(this->size) - 1; i++)
// 			this->storage[i] = this->storage[i + 1];
// 		this->storage[this->size - 1] = 0;
// 		--this->size;
// 		/// 元素个数<=1/2最大容量 时收缩空间
// 		if (this->size <= this->maxsize / 2)
// 			Shrink();
// 		return elem;
// 	}
// };
