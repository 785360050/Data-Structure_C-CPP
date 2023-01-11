#pragma once




#include <iostream>
#include "Liner_Queue_ADT.h"

template <typename DataType>
struct QueueNode
{
	DataType element;
	QueueNode* next;
public:
	void Node_Init(DataType element = 0, QueueNode<DataType>* next = nullptr)
	{
		this->element = element;
		this->next = next;
	}
};

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
	{
		length = maxsize = 0;
		front = rear = nullptr;
	}
	
public:///链表操作
	//初始化队列
	void Queue_Init(int maxsize)
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
	void Queue_Destroy()
	{
		try
		{
			if (!front)
				throw 1;
		}
		catch (const std::exception&)
		{
			std::cout << "Queue Destroy Faild: Queue is not exist" << std::endl;
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
	}
	//清空队列(等价于销毁队列)，链式队列不需要空节点
	void Queue_Clear()
	{
		Queue_Destroy();
	}
	//判断是否队空
	bool Queue_CheckEmpty()
	{
		if (front == NULL && rear == NULL)
			return true;
		return false;
	}
	//返回队列长度(元素个数)
	int Queue_Length()
	{
		return length;
	}
	//返回队头
	DataType Queue_GetHead()
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
	void Queue_Show(const char* string)
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
	void Element_Enqueue(DataType element)
	{
		try
		{
			if (length == maxsize)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Enqueue Faild: Queue is full" << std::endl;
			return;
		}
		QueueNode<DataType>* node = new QueueNode<DataType>;
		node->Node_Init(element);
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
	DataType Element_Dequeue()
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












