#pragma once




#include <iostream>
#include "../Liner_Queue.hpp"
#include "../../List_Node.hpp"

namespace Storage 
{
	/// @tparam NodeType 默认使用单链节点
	template <typename ElementType, typename NodeType = List_Node_SingleWay<ElementType>>
	class Link_Queue : public Logic::Queue<ElementType>
	{ /// 循环队列
	protected:
		NodeType *front{};//指向首元节点
		NodeType *rear{}; // 指向尾元节点

	public:
		Link_Queue() = default;
		Link_Queue(size_t size) : Logic::Queue<ElementType>(size){};
		~Link_Queue()
		{
			Clear();
			// std::cout << "Link_Queue Destroyed" << std::endl;
		}

	public: /// 链表操作
		// 清空队列(等价于销毁队列)，链式队列不需要空节点
		virtual void Clear() override
		{
			if (front)
			{
				rear = nullptr;
				NodeType *del;
				while (!front)
				{
					del = front;
					front = front->next;
					delete del;
				}
				this->size = 0;
			}
			front = nullptr;
		}
		ElementType& Get_Front() override
		{
			if (this->Is_Empty())
				throw std::runtime_error("Queue is not exist");
			return front->element;
		}
		ElementType& Get_Rear() override
		{
			if (this->Is_Empty())
				throw std::runtime_error("Queue is not exist");
			return rear->element;
		}
		virtual void Queue_Show(const std::string &string="") override
		{
			std::cout << string << std::endl
					  << "[Size]:"<< this->size << std::endl
					  << "[Front/Rear]: [" << front << '/' << rear << ']' << std::endl
					  << "Queue: Front=》";
			NodeType *node = front;
			for (int index = 1; index <= this->size; index++, node = node->next)
			{
				std::cout << '[' << index << ':' << node->element << ']';
				if(node->next)
					std::cout << "->";
			}
			std::cout << "《=Rear" << std::endl;
		}

	public: /// 元素操作
		virtual void Element_Enqueue(const ElementType& element) override
		{
			NodeType *node = new NodeType(element);
			if (this->Is_Empty())
				front = rear = node;
			else
			{
				rear->next = node;
				rear = rear->next;
			}
			++this->size;
		}
		virtual void Element_Enqueue(ElementType &&element) override
		{
			NodeType *node = new NodeType(std::move(element));
			if (this->Is_Empty())
				front = rear = node;
			else
			{
				rear->next = node;
				rear = rear->next;
			}
			++this->size;
		}
		virtual void Element_Dequeue() override
		{
			if (this->Is_Empty())
				throw std::runtime_error("Pop faild , LinkQueue is empty");
			if (this->size == 1)
			{
				delete front;
				front = nullptr;
				rear = nullptr;
			}
			else
			{
				NodeType *del = front;
				front = front->next;
				delete del;
			}
			--this->size;
		}
	};
}
/// @tparam NodeType 默认使用单链节点
/// @note 似乎链式队列实现没有什么变数，该类仅加入拷贝控制
template <typename ElementType, typename NodeType = List_Node_SingleWay<ElementType>>
class Link_Queue : public Storage::Link_Queue<ElementType,NodeType>
{
public:
	Link_Queue() = default;
	Link_Queue(const Link_Queue &other)
		: Storage::Link_Queue<ElementType, NodeType>(other.size)
	{
		if(this==&other)
			throw std::logic_error("Self Coppied");
		if (other.size == 0)
			return ;
		else if (other.size == 1)
			this->front=this->rear = new NodeType(other.front->element);
		else
		{
			NodeType *node = other.front,*self{};
			this->front = new NodeType(node->element);
			self = this->front;
			node = node->next;
			while (node)
			{
				self->next = new NodeType(node->element);
				self = self->next;
				node = node->next;
			}
			this->rear = self;
		}
	}
	Link_Queue(Link_Queue &&other)
	: Storage::Link_Queue<ElementType, NodeType>(other.size)
	{
		this->front = other.front;
		this->rear = other.rear;
		other.size = 0;
	}
	Link_Queue<ElementType, NodeType>& operator=(const Link_Queue &other)
	{
		this->size = other.size;

		if (this == &other)
			throw std::logic_error("Self Coppied");
		if (other.size == 0)
			return Link_Queue<ElementType, NodeType>();
		else if (other.size == 1)
			this->front = this->rear = new NodeType(other.front->element);
		else
		{
			NodeType *node = other.front, *self{};
			this->front = new NodeType(node->element);
			self = this->front;
			node = node->next;
			while (node)
			{
				self->next = new NodeType(node->element);
				self = self->next;
				node = node->next;
			}
			this->rear = self;
		}
		return *this;
	}
	Link_Queue<ElementType, NodeType>& operator=(Link_Queue &&other)
	{
		this->front = other.front;
		this->rear = other.rear;
		this->size = other.size;
		other.size = 0;
		return *this;
	}
};

#if __cplusplus >= 202002L
static_assert(ADT::Liner_Queue<Link_Queue<int>, int>);
#endif
