#pragma once



#include "Liner_Queue_ADT.h"





template<typename DataType>
struct Queue:public Queue_ADT<DataType>
{///循环队列
protected:
	int length;
	int maxsize;
public:
	Queue()
		:length{ 0 }, maxsize{ 0 } {};
	Queue(int maxsize)
		:length{ 0 }
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
		this->maxsize = maxsize;
	}
	virtual ~Queue() = default;
public:
	//清空队列
	virtual void Queue_Clear() = 0;
	//判断是否队空
	bool Queue_CheckEmpty() override
	{return this->length == 0 ? true : false;}
	bool Queue_CheckFull() override
	{
		try
		{
			if (length > maxsize)
				throw std::runtime_error("Queue Overflowed");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		return length == maxsize;
	}
	//返回队列长度(元素个数)
	int Queue_Length() override
	{return length;}
	//返回队头
	virtual DataType Queue_GetFront() = 0;
	//返回队尾
	virtual DataType Queue_GetRear() = 0;
	//元素入队
	virtual void Element_Enqueue(DataType element) = 0;
	//元素出队
	virtual void Element_Dequeue() = 0;
	//显示整个队列信息
	virtual void Queue_Show(const std::string& string) = 0;
};