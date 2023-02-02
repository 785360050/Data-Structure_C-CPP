#pragma once




#include <iostream>
#include "../Liner_Queue.h"
#include "../../List_Node.h"



template<typename DataType, typename NodeType = List_Node_SingleWay<int>>
class Link_Queue:public Queue<DataType>
{///循环队列
private:
	NodeType* front;
	NodeType* rear;
public:
	Link_Queue()
		:Queue<DataType>(), front(nullptr), rear(nullptr) {};
	Link_Queue(int maxsize)
		:Queue<DataType>(maxsize), front(nullptr), rear(nullptr) {};
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
		NodeType* del;
		while (!front)
		{
			del = front;
			front = front->next;
			delete del;
		}
		this->length = 0;
		std::cout << "Link_Queue Destroyed" << std::endl;
	}
public:///链表操作
	//清空队列(等价于销毁队列)，链式队列不需要空节点
	void Queue_Clear() override
	{
		if (front)
		{
			rear = nullptr;
			NodeType* del;
			while (!front)
			{
				del = front;
				front = front->next;
				delete del;
			}
			this->length = 0;
		}
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
			std::cout << "GetHead Failed: Queue is not exist" << std::endl;
			return NULL;
		}
		return front->element;
	}
	DataType Queue_GetRear() override
	{
		try
		{
			if (this->Queue_CheckEmpty())
				throw 1;
		}
		catch (...)
		{
			std::cout << "GetHead Failed: Queue is not exist" << std::endl;
			return NULL;
		}
		return rear->element;
	}
	void Queue_Show(const std::string& string) override
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:" << " [" << this->length << '/' << this->maxsize << ']' << std::endl
			<< "[Front/Rear]: [" << front << '/' << rear << ']' << std::endl
			<< "Queue: Front->";
		NodeType* node = front;
		for (int index = 1; index <= this->length; index++,node=node->next)
			std::cout << '[' << index << ':' << node->element << "]-";
		std::cout << "<-Rear" << std::endl;
	}
public:///元素操作
	void Element_Enqueue(DataType element) override
	{
		try
		{
			if (this->length >= this->maxsize)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Enqueue Faild: Queue is full" << std::endl;
			return;
		}
		NodeType* node = new NodeType(element);
		if (this->Queue_CheckEmpty())
			front = rear = node;
		else
		{
			rear->next = node;
			rear = rear->next;
		}
		++this->length;
	}
	void Element_Dequeue() override
	{
		try
		{
			if (this->Queue_CheckEmpty())
			{
				throw 1;
			}
		}
		catch (...)
		{
			std::cout << "Pop faild , LinkQueue is empty" << std::endl;
			return ;
		}
		if (this->length == 1)
		{
			delete front;
			front = nullptr;
			rear = nullptr;
		}
		else
		{
			NodeType* del = front;
			front = front->next;
			delete del;
		}
		--this->length;
	}
};












