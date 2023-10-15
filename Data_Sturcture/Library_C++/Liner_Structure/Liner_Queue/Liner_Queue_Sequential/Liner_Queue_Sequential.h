#pragma once


#include <iostream>

#include "../Liner_Queue.h"

template<typename DataType>
struct Sequence_Queue :public Queue<DataType>
{///使用少存一个元素空间实现队列判断满
protected:
	int front;			///队头下标索引
	int rear;			///队尾下标索引(队尾的后一个元素位置，即待插入位置索引)
	DataType* element;	///队列数组
protected:
	int Index(int x) const
	{return x - 1;}
public:///Redundancy
	Sequence_Queue()
		:Queue< DataType>(),front{ 0 }, rear{ 0 }, element{ nullptr } {};
	Sequence_Queue(int maxsize)
		:Queue<DataType>(maxsize),
		front{ 0 }, rear{ 0 },
		element{ new DataType[maxsize + 1]{} }{};

	virtual ~Sequence_Queue()
	{
		if (element)
		{
			delete[] element;
			element = nullptr;
			std::cout << "Sequence_Queue Destroyed" << std::endl;
		}
	}
public:
	virtual bool Queue_CheckFull() override
	{
		return (rear + 1) % (this->maxsize + 1) == front ? true : false;
	}
	void Queue_Clear() override
	{
		memset(element, 0, sizeof(DataType) * (this->maxsize));
		this->length = front = rear = 0;
	}
	DataType Queue_GetFront() override
	{
		try
		{
			if (this->Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is Empty" << std::endl;
			return NULL;
		}
		return element[front];
	}
	virtual DataType Queue_GetRear() override
	{
		try
		{
			if (this->Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is Empty" << std::endl;
			return NULL;
		}
		/// rear指向待插入位置索引，返回前一个元素索引
		return element[(rear + this->maxsize) % (this->maxsize + 1)];	
	}
	virtual void Queue_Show(const std::string& string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:" << " [" << this->length << '/' << this->maxsize << ']' << std::endl
			<< "[Front/Rear/Redundancy]: [" << front << '/' << rear << '/' << this->maxsize << ']' << std::endl
			<< "Queue-";
		for (int index = 0; index < this->maxsize + 1; index++)
			std::cout << '[' << index << ':' << element[index] << "]-";
		std::cout << "End" << std::endl;
	}
public:
	virtual void Element_Enqueue(DataType element) override
	{
		try
		{
			if (this->element==nullptr)
				throw std::runtime_error("SeqQueue is not exist");
			if (Queue_CheckFull())
				throw std::runtime_error("Enqueue Failed: Queue is Full");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		this->element[rear] = element;
		rear = (rear + 1) % (this->maxsize + 1);
		this->length++;
	}
	virtual void Element_Dequeue() override
	{
		try
		{
			if (this->Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Dequeue Faild: Queue is empty" << std::endl;
			return ;
		}
		DataType x = element[front];
		element[front] = 0;
		front = (front + 1) % (this->maxsize + 1);
		--this->length;
	}
};


template<typename DataType>
struct Sequence_Queue_Tag :public Sequence_Queue<DataType>
{///使用bool标志实现队列判断满
private:
	bool full;
private:
	bool Queue_CheckFull() override final
	{return full;}
public:
	Sequence_Queue_Tag()
		:Sequence_Queue<DataType>(), full{false} {};
	Sequence_Queue_Tag(int maxsize)
		:Sequence_Queue_Tag()
	{
		try
		{
			if (maxsize < 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue Init Failed: maxsize must be greater than 1" << std::endl;
			return;
		}
		this->element = new DataType[maxsize]{};//初始化为0
		this->maxsize = maxsize;
		full = false;
	}
	~Sequence_Queue_Tag() override
	{
		try
		{
			if (!this->element)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is not exsist" << std::endl;
			return;
		}
		delete[] this->element;
		this->element = nullptr;
		std::cout << "Sequence_Queue_Tag Destroyed" << std::endl;
	}
public:
	void Queue_Show(const std::string& string) override final
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]=" << "[" << this->length << '/' << this->maxsize << ']' << std::endl
			<< "[Front/Rear]=[" << this->front << '/' << this->rear << ']' << std::endl
			<< "Queue-";
		for (int index = 0; index < this->maxsize; index++)
			std::cout << '[' << index << ':' << this->element[index] << "]-";
		std::cout << "End" << std::endl;
	}
public:
	void Element_Enqueue(DataType element) override
	{
		try
		{
			if (this->element == nullptr)
				throw std::runtime_error("SeqQueue is not exist");
			if (Queue_CheckFull())
				throw std::runtime_error("Enqueue Failed: Queue is Full");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		this->element[this->rear] = element;
		this->rear = (this->rear + 1) % this->maxsize;
		this->length++;

		if (this->front == this->rear)
			full = true;
	}
	void Element_Dequeue() override
	{
		try
		{
			if (this->Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Dequeue Faild: Queue is empty" << std::endl;
			return ;
		}
		DataType x = this->element[this->front];
		this->element[this->front] = NULL;
		this->front = (this->front + 1) % this->maxsize;
		this->length--;
		
		if (this->front == this->rear)
			full = false;
	}
	virtual DataType Queue_GetRear() override
	{
		try
		{
			if (this->Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is Empty" << std::endl;
			return NULL;
		}
		/// rear指向待插入位置索引，返回前一个元素索引
		return this->element[this->rear];
	}
};




