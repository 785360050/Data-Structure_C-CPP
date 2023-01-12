#pragma once


#include <iostream>

#include "../Liner_Queue_ADT.h"

template<typename DataType>
struct Sequence_Queue :public Queue<DataType>
{///使用少存一个元素空间实现队列判断满
protected:
	int front;
	int rear;
	int length;
	int maxsize;
	DataType* element;
protected:
	virtual bool Queue_CheckFull()
	{return (rear + 1) % (maxsize + 1) == front ? true : false; }
	int Index(int x) const
	{return x - 1;}
public:///Redundancy
	Sequence_Queue()
		:front{ 0 }, rear{ 0 }, length{ 0 }, maxsize{ 0 }, element{ nullptr } {};
	Sequence_Queue(int maxsize)
		:Sequence_Queue()
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
		element = new DataType[maxsize + 1]{};//初始化为0
		this->maxsize = maxsize;
	}
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
	//清空队列
	void Queue_Clear() override
	{
		memset(element, 0, sizeof(DataType) * (maxsize));
		length = front = rear = 0;
	}
	//判断是否队空
	bool Queue_CheckEmpty() override
	{return length == 0 ? true : false;}
	//返回队列长度(元素个数)
	int Queue_Length() override
	{return length;}
	//返回队头
	DataType Queue_GetHead() override
	{
		try
		{
			if (Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Queue is Empty" << std::endl;
			return NULL;
		}
		return element[front];
	}
	//显示整个队列信息
	virtual void Queue_Show(const char* string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:" << " [" << length << '/' << maxsize << ']' << std::endl
			<< "[Front/Rear/Redundancy]: [" << front << '/' << rear << '/' << rear + maxsize << ']' << std::endl
			<< "Queue-";
		for (int index = 0; index < maxsize + 1; index++)
			std::cout << '[' << index << ':' << element[index] << "]-";
		std::cout << "End" << std::endl;
	}
public:
	//元素入队
	virtual void Element_Enqueue(DataType element) override
	{
		try
		{
			if (this->element==nullptr)
				throw std::exception("SeqQueue is not exist");
			if (Queue_CheckFull())
				throw std::exception("Enqueue Failed: Queue is Full");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		this->element[rear] = element;
		rear = (rear + 1) % maxsize;
		length++;
	}
	//元素出队
	virtual DataType Element_Dequeue() override
	{
		try
		{
			if (Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Dequeue Faild: Queue is empty" << std::endl;
			return NULL;
		}
		DataType x = element[front];
		element[front] = 0;
		front = (front + 1) % Index(maxsize);
		--length;
		return x;
	}

};


template<typename DataType>
struct Sequence_Queue_Tag :public Sequence_Queue<DataType>
{///使用少存一个元素空间实现队列判断满
private:
	bool full;
private:
	bool Queue_CheckFull() override final
	{return full;}
public:
	Sequence_Queue_Tag()
		:Sequence_Queue<DataType>(), full{false} {};
	Sequence_Queue_Tag(int maxsize)
		:Sequence_Queue<DataType>()
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
	void Queue_Show(const char* string) override
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
				throw std::exception("SeqQueue is not exist");
			if (Queue_CheckFull())
				throw std::exception("Enqueue Failed: Queue is Full");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		this->element[this->rear] = element;
		this->rear = (this->rear + 1) % this->maxsize;
		this->length++;

		if (Queue_CheckFull())
			full = true;
	}
	DataType Element_Dequeue() override
	{
		try
		{
			if (this->Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "Dequeue Faild: Queue is empty" << std::endl;
			return NULL;
		}
		DataType x = this->element[this->front];
		this->element[this->front] = 0;
		this->front = (this->front + 1) % this->maxsize;
		this->length--;
		
		if (!Queue_CheckFull())
			full = false;
		return x;
	}
};




