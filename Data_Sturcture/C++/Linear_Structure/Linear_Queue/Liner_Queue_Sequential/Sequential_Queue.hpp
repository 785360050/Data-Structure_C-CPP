#pragma once

#include <iostream>

#include "../Linear_Queue.hpp"

/// ============================================================================================================
/// 		由于队列通常用作为缓冲，所以顺序队列仅实现栈分配。要动态内存请使用链式队列,使ElementType为一块数组以实现
/// ============================================================================================================
namespace Storage
{
	/// @brief
	/// @tparam ElementType
	/// @tparam capcity 等价于Logic::Queue::maxsize
	template <typename ElementType, size_t maxsize>
	struct Sequential_Queue : public Logic::Queue<ElementType>
	{ /// 使用少存一个元素空间实现队列判断满
	protected:
		size_t front{}; /// 队头下标索引
		size_t rear{};	/// 队尾下标索引(队尾的后一个元素位置，即待插入位置索引)
		 size_t capcity{};

		//由于不同方式实现不同，所以用指针而不是直接分配在此处
		ElementType *storage{nullptr}; // 队列数组

		// ElementType storage[capcity]{}; /// 队列数组
	protected:
		size_t Index(size_t x) const
		{
			if (x == 0)
				throw std::underflow_error("Index:x == 0");
			return x - 1;
		}
		virtual ElementType &Get_Rear() = 0;
		virtual ElementType &Get_Front() = 0;
		

	public: /// Redundancy
		// Sequential_Queue()
		Sequential_Queue(size_t capcity, ElementType *storage,size_t size=0)
		 : Logic::Queue<ElementType>(size),capcity{capcity}, storage{storage}
		{
			static_assert(maxsize > 0, "Queue Init Failed: maxsize must be greater than 0");
		}

		virtual ~Sequential_Queue(){};

	public:
		virtual bool Is_Full() const = 0;
		constexpr size_t Get_Capcity() const { return capcity; }
		virtual void Clear()
		{
			if (std::is_pointer<ElementType>::value)
			{
				std::cout << " pointer elements' clear not implemented yet ." << std::endl;
				return;
			}
			for (size_t i = 0; i < this->size; i++)
			{
				std::destroy(this->storage, this->storage + this->size);
				this->storage[i] = ElementType();
			}

			this->size = front = rear = size_t{};
		}

		virtual void Queue_Show(const std::string &string = "") = 0;

	public:
		virtual void Element_Enqueue(ElementType &&element) = 0;
		virtual void Element_Enqueue(const ElementType &element) = 0;
		virtual void Element_Dequeue() = 0;
	};
}

/// @brief 少存一个元素空间实现队列判断满
/// @tparam capcity 实际可用的元素
template <typename ElementType, size_t maxsize>
struct Sequential_Queue_Redundancy : public Storage::Sequential_Queue<ElementType, maxsize>
{
private:
	ElementType array[maxsize+1]{};

public:
	Sequential_Queue_Redundancy() 
	: Storage::Sequential_Queue<ElementType, maxsize>(maxsize+1, array)
	{
		static_assert(maxsize > 0, "Queue Init Failed: maxsize must be greater than 0");
	}
	Sequential_Queue_Redundancy(const Sequential_Queue_Redundancy<ElementType, maxsize> &other)
		: Storage::Sequential_Queue<ElementType, maxsize>(other.capcity, array, other.size)
	{
		this->front = other.front;
		this->rear = other.rear;
		for (size_t i = 0; i < maxsize; i++)
			array[i] = other.array[i];
	}
	Sequential_Queue_Redundancy(Sequential_Queue_Redundancy<ElementType, maxsize> &&other)
		: Storage::Sequential_Queue<ElementType, maxsize>(other.capcity, array, other.size)
	{
		this->front = other.front;
		this->rear = other.rear;
		other.front = size_t{};
		other.rear = size_t{};
		other.size = size_t{};
		for (size_t i = 0; i < maxsize; i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}
	}
	Sequential_Queue_Redundancy<ElementType, maxsize> &operator=(const Sequential_Queue_Redundancy<ElementType, maxsize> &other)
	{
		this->front = other.front;
		this->rear = other.rear;
		for (size_t i = 0; i < maxsize; i++)
			array[i] = other.array[i];
		return *this;
	}

	Sequential_Queue_Redundancy<ElementType, maxsize> &operator=(Sequential_Queue_Redundancy<ElementType, maxsize> &&other)
	{
		this->front = other.front;
		this->rear = other.rear;
		other.front = size_t{};
		other.rear = size_t{};
		other.size = size_t{};
		for (size_t i = 0; i < maxsize; i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}
		return *this;
	}

		virtual ~Sequential_Queue_Redundancy()
	{
		// std::cout << "Sequential_Queue Destroyed" << std::endl;
	}

public:
	virtual bool Is_Full() const override { return (this->rear + 1) % (maxsize + 1) == this->front; }
	void Clear() override
	{
		for (size_t i = 0; i < this->capcity; i++) // 冗余的元素也要重置
			this->storage[i] = std::move(ElementType()); // 使用 std::move 移动构造重置元素

		this->size = this->front = this->rear = 0;
	}

	ElementType &Get_Rear() override
	{
		if (this->Is_Empty())
			throw std::runtime_error("Queue is Empty");
		/// rear指向待插入位置索引，返回前一个元素索引
		return this->storage[(this->rear + maxsize) % (maxsize + 1)];
	}
	ElementType &Get_Front() override
	{
		if (this->Is_Empty())
			throw std::runtime_error("Queue is Empty");
		/// rear指向待插入位置索引，返回前一个元素索引
		return this->storage[this->front];
	}

	virtual void Queue_Show(const std::string &string) override
	{
		std::cout << string << std::endl
				  << "[Length/Maxsize]:"
				  << " [" << this->size << '/' << maxsize << ']' << std::endl
				  << "[Front/Rear/Redundancy]: [" << this->front << '/' << this->rear << '/' << maxsize << ']' << std::endl
				  << "Queue-";
		for (size_t index = 0; index < maxsize + 1; index++)
			std::cout << '[' << index << ':' << this->storage[index] << "]-";
		std::cout << "End" << std::endl;
	}

public:
	void Element_Enqueue(const ElementType &element) override
	{
		if (this->storage == nullptr)
			throw std::runtime_error("SeqQueue is not exist");
		if (Is_Full())
			throw std::runtime_error("Enqueue Failed: Queue is Full");

		this->storage[this->rear] = element;
		this->rear = (this->rear + 1) % (maxsize + 1);
		this->size++;
	}
	void Element_Enqueue(ElementType &&element) override
	{
		if (this->storage == nullptr)
			throw std::runtime_error("SeqQueue is not exist");
		if (Is_Full())
			throw std::runtime_error("Enqueue Failed: Queue is Full");

		this->storage[this->rear] = element;
		this->rear = (this->rear + 1) % (maxsize + 1);
		this->size++;
	}
	void Element_Dequeue() override
	{
		if (this->Is_Empty())
			throw std::runtime_error("Dequeue Failed: Queue is Empty");
		this->storage[this->front] = ElementType{};
		this->front = (this->front + 1) % (maxsize + 1);
		--this->size;
	}
};

/// @brief 使用bool标志实现队列判断满
template <typename ElementType, size_t maxsize>
struct Sequential_Queue_Tag : public Storage::Sequential_Queue<ElementType, maxsize>
{
private:
	bool full{false};
	ElementType array[maxsize]{};

	virtual ElementType &Get_Rear() override
	{
		if (this->Is_Empty())
			throw std::runtime_error("Queue is Empty");
		/// rear指向待插入位置索引，返回前一个元素索引
		return this->storage[this->rear];
	}

public:
	Sequential_Queue_Tag() : Storage::Sequential_Queue<ElementType, maxsize>(maxsize, array)
	{
		static_assert(maxsize > 0, "Queue Init Failed: maxsize must be greater than 0");
	}
	Sequential_Queue_Tag(const Sequential_Queue_Tag<ElementType, maxsize> &other)
		: Storage::Sequential_Queue<ElementType, maxsize>(other.capcity, array, other.size)
	{
		this->front = other.front;
		this->rear = other.rear;
		full = other.full;
		for (size_t i = 0; i < maxsize; i++)
			array[i] = other.array[i];
	}
	Sequential_Queue_Tag(Sequential_Queue_Tag<ElementType, maxsize> &&other)
		: Storage::Sequential_Queue<ElementType, maxsize>(other.capcity, array, other.size)
	{
		this->front = other.front;
		this->rear = other.rear;
		full = other.full;
		other.full = false;
		other.front = size_t{};
		other.rear = size_t{};
		other.size = size_t{};
		for (size_t i = 0; i < maxsize; i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}
	}
	Sequential_Queue_Tag<ElementType, maxsize> &operator=(const Sequential_Queue_Tag<ElementType, maxsize> &other)
	{
		this->front = other.front;
		this->rear = other.rear;
		full = other.full;
		for (size_t i = 0; i < maxsize; i++)
			array[i] = other.array[i];
		return *this;
	}

	Sequential_Queue_Tag<ElementType, maxsize> &operator=(Sequential_Queue_Tag<ElementType, maxsize> &&other)
	{
		this->front = other.front;
		this->rear = other.rear;
		full = other.full;
		other.full = false;
		other.front = size_t{};
		other.rear = size_t{};
		other.size = size_t{};
		for (size_t i = 0; i < maxsize; i++)
		{
			array[i] = std::move(other.array[i]);
			other.array[i] = ElementType{};
		}
		return *this;
	}

	~Sequential_Queue_Tag() override
	{
		// std::cout << "Sequential_Queue_Tag Destroyed" << std::endl;
	}

public:
	bool Is_Full() const override final { return full; }
	ElementType &Get_Front() override
	{
		if (this->Is_Empty())
			throw std::runtime_error("Queue is Empty");
		/// rear指向待插入位置索引，返回前一个元素索引
		return this->storage[this->front];
	}
	void Queue_Show(const std::string &string) override final
	{
		std::cout << string << std::endl
				  << "[Size/Maxsize]="
				  << "[" << this->size << '/' << maxsize << ']' << std::endl
				  << "[Front/Rear]=[" << this->front << '/' << this->rear << ']' << std::endl
				  << "Queue-";
		for (size_t index = 0; index < maxsize; index++)
			std::cout << '[' << index << ':' << this->storage[index] << "]-";
		std::cout << "End" << std::endl;
	}

public:
	void Element_Enqueue(const ElementType &element) override
	{
		if (this->storage == nullptr)
			throw std::runtime_error("SeqQueue is not exist");
		if (Is_Full())
			throw std::runtime_error("Enqueue Failed: Queue is Full");
		this->storage[this->rear] = element;
		this->rear = (this->rear + 1) % maxsize;
		this->size++;

		if (this->front == this->rear)
			full = true;
	}
	void Element_Enqueue(ElementType &&element) override
	{
		if (this->storage == nullptr)
			throw std::runtime_error("SeqQueue is not exist");
		if (Is_Full())
			throw std::runtime_error("Enqueue Failed: Queue is Full");
		this->storage[this->rear] = element;
		this->rear = (this->rear + 1) % maxsize;
		this->size++;

		if (this->front == this->rear)
			full = true;
	}
	void Element_Dequeue() override
	{
		if (this->Is_Empty())
			throw std::runtime_error("Dequeue Faild: Queue is empty");
		this->storage[this->front] = ElementType();
		this->front = (this->front + 1) % maxsize;
		this->size--;

		if (this->front == this->rear)
			full = false;
	}
};

/// @brief 顺序队列默认使用标志实现判断满的实现版本
template <typename ElementType, size_t maxsize>
using Sequential_Queue = Sequential_Queue_Tag<ElementType, maxsize>;

#if __cplusplus >= 202002L
static_assert(ADT::Linear_Queue<Sequential_Queue_Redundancy<int,5>, int>);
static_assert(ADT::Linear_Queue<Sequential_Queue_Tag<int,5>, int>);
#endif