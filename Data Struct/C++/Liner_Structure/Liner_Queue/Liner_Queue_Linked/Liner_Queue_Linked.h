#pragma once




#include <iostream>
#include "../Liner_Queue_ADT.h"
#include "../../List_Node.h"

template <typename DataType>
using QueueNode = List_Node_SingleWay<DataType>;

template<typename DataType>
class Link_Queue:public Queue<DataType>
{///循环队列
private:
	int length;	
	int maxsize;
	QueueNode<DataType>* front;
	QueueNode<DataType>* rear;
public:
	Link_Queue()
		:length{ 0 }, maxsize{ 0 }, front{ nullptr }, rear{ 0 } {};
	//初始化队列
	Link_Queue(int maxsize)
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
	//销毁队列
	~Link_Queue()
	{
		try
		{
			if (!front)
				throw std::exception("Queue Destroy Faild: Queue is not exist");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		rear = nullptr;
		QueueNode<DataType>* del;
		while (!front)
		{
			del = front;
			front = front->next;
			delete del;
		}
		length = 0;
		std::cout << "Link_Queue Destroyed" << std::endl;
	}
public:///链表操作
	//清空队列(等价于销毁队列)，链式队列不需要空节点
	void Queue_Clear() override
	{
		if (front)
		{
			rear = nullptr;
			QueueNode<DataType>* del;
			while (!front)
			{
				del = front;
				front = front->next;
				delete del;
			}
			length = 0;
		}
	}
	//判断是否队空
	bool Queue_CheckEmpty() override
	{return (front == nullptr && rear == nullptr) ? true : false;}
	//返回队列长度(元素个数)
	int Queue_Length() override
	{
		return length;
	}
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
			std::cout << "GetHead Failed: Queue is not exist" << std::endl;
			return NULL;
		}
		return front->element;
	}
	//显示整个队列信息
	void Queue_Show(string string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:" << " [" << length << '/' << maxsize << ']' << std::endl
			<< "[Front/Rear]: [" << front << '/' << rear << ']' << std::endl
			<< "Queue: Front->";
		QueueNode<DataType>* node = front;
		for (int index = 1; index <= length; index++,node=node->next)
			std::cout << '[' << index << ':' << node->element << "]-";
		std::cout << "<-Rear" << std::endl;
	}
public:///元素操作
	//元素入队
	void Element_Enqueue(DataType element) override
	{
		try
		{
			if (length >= maxsize)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Enqueue Faild: Queue is full" << std::endl;
			return;
		}
		QueueNode<DataType>* node = new QueueNode<DataType>(element);
		if (length == 0)
			front = rear = node;
		else
		{
			rear->next = node;
			rear = rear->next;
		}
		length++;
	}
	//元素出队
	DataType Element_Dequeue() override
	{
		try
		{
			if (length <= 0)
			{
				throw 1;
			}
		}
		catch (...)
		{
			std::cout << "Pop faild , LinkQueue is empty" << std::endl;
			return NULL;
		}
		if (length == 1)
		{
			return front->element;
			length--;
		}
		else
		{
			QueueNode<DataType>* del = front;
			front = front->next;
			DataType x = del->element;
			delete del;
			length--;
			return x;
		}
	}
};












