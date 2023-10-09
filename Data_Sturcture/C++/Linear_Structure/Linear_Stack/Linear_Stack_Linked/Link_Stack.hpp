#pragma once

#include <iostream>

#include "../Stack.hpp"
#include "../../List_Node.hpp"

namespace Storage
{
	/// @brief 头插法实现的链栈，top指向首元节点
	template <typename ElementType, typename NodeType = List_Node_SingleWay<ElementType>>
	class Link_Stack : public Logic::Stack<ElementType>
	{
	protected:
		NodeType *top{nullptr};

	public: /// 对象维护头节点，存放栈信息
		Link_Stack() = default;
		// 销毁栈
		virtual ~Link_Stack()
		{
			Clear();
			// std::cout << "Link_Stack Destroyed" << std::endl;
		}

	public: /// 栈操作
		// 清空栈(等价于销毁栈空间)
		/// 由于链栈空间利用率高，不存在空节点，所以清空链表元素==销毁所有链表节点
		void Clear() override
		{
			while (top)
			{
				NodeType *del = top;
				top = top->next;
				delete del;
			}
		}
		// 返回栈顶元素
		ElementType &Get_Top() override
		{
			return top->element;
		}
		// 输出栈所有信息
		void Stack_Show(const std::string &string="") override
		{
			NodeType *node = top;
			std::cout << string << std::endl
					  << "[Size]:"<<this->size << std::endl
					  << "Top=>";
			for (size_t index = 1; index <= this->size; index++, node = node->next)
				std::cout << '[' << index << ':' << node->element << "]->";
			std::cout << "Bottom(NULL)" << std::endl;
		}

	public: /// 元素操作
		// 元素入栈
		virtual void Element_Push(const ElementType &element) override
		{
			top = new NodeType(element, top);
			++this->size;
		}
		virtual void Element_Push(ElementType &&element) override
		{
			top = new NodeType(std::move(element), top);
			++this->size;
		}
		// 元素出栈
		void Element_Pop() override
		{
			if (this->Is_Empty())
				throw std::runtime_error("Stack is empty");
			NodeType *node = top;
			top = top->next;
			delete node;
			--this->size;
		}
		// 更新节点元素值
	};
}

/// @brief 同Storage::Link_Stack的实现，此处仅添加拷贝控制
/// @tparam ElementType
/// @tparam NodeType
template <typename ElementType, typename NodeType = List_Node_SingleWay<ElementType>>
class Link_Stack : public Storage::Link_Stack<ElementType, NodeType>
{
private:
public:
	Link_Stack() = default;

	Link_Stack(const Link_Stack &other)
	{
		if (this == &other)
			throw std::logic_error("Self Coppied");
		if (other.size == 0)
			return;
		else if (other.size == 1)
			this->Element_Push(other.top->element);
		else
		{
			//处理首元节点
			this->top = new NodeType(other.top->element);
			++this->size;
			NodeType *node = other.top, *self = this->top;
			//统一处理后续节点
			while (node->next)
			{
				self->next = new NodeType(node->next->element);
				self = self->next;
				node = node->next;
				++this->size;
			}

		}
	}
	Link_Stack &operator=(const Link_Stack &other)
	{
		this->size = 0;
		if (this == &other)
			throw std::logic_error("Self Coppied");
		if (other.size == 0)
			return Link_Stack{};
		else if (other.size == 1)
			Element_Push(other.top->element);
		else
		{
			// 处理首元节点
			this->top = new NodeType(other.top->element);
			++this->size;
			NodeType *node = other.top, *self = this->top;
			// 统一处理后续节点
			while (node->next)
			{
				self->next = new NodeType(node->next->element);
				self = self->next;
				node = node->next;
				++this->size;
			}
		}
		
		return *this;
	}

	Link_Stack(Link_Stack &&other)
	{
		this->top = other.top;
		other.top = nullptr;
		other.size = 0;
		auto node = this->top;
		while (node)
		{
			++this->size;
			node = node->next;
		}
	}
	Link_Stack &operator=(Link_Stack &&other)
	{
		this->top = other.top;
		other.top = nullptr;
		other.size = 0;
		auto node = this->top;
		while (node)
		{
			++this->size;
			node = node->next;
		}
		return *this;
	}

};