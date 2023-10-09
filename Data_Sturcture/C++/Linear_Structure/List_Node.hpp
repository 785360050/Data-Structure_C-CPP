#pragma once
#include <iostream>
#include "../Node.hpp"


/// ============================================================================================================
/// 		所有的节点拷贝和移动时，对节点指针都仅做浅拷贝。
/// 		因为拷贝和移动，逻辑上都只针对当前节点本身而不是所有
/// ============================================================================================================


// 单链节点
template <typename ElementType>
class List_Node_SingleWay : public Node<ElementType>
{
public:
	List_Node_SingleWay<ElementType> *next = nullptr;

public:
	List_Node_SingleWay() = default;
	List_Node_SingleWay(const ElementType& element, List_Node_SingleWay<ElementType> *next = nullptr)
		: Node<ElementType>(element), next{next} {};
	List_Node_SingleWay(ElementType &&element, List_Node_SingleWay<ElementType> *next = nullptr)
		: Node<ElementType>(std::move(element)), next{next} {};

public: //Copy Conrtol
	List_Node_SingleWay(const List_Node_SingleWay<ElementType> &other)
		: Node<ElementType>(other)
	{
		if (this == &other)
			throw std::logic_error("Self assignment");
		if (next)
			delete next;
		next = other.next;
	}
	List_Node_SingleWay(List_Node_SingleWay<ElementType> &&other)
		: Node<ElementType>(other)
	{
		if(next)
			delete next;
		next = other.next;
		other.next = nullptr;
	}
	List_Node_SingleWay<ElementType> &operator=(const List_Node_SingleWay<ElementType> &other)
	{
		if (this == &other)
			throw std::logic_error("Self assignment");
		Node<ElementType>::operator=(other);
		if (next)
			delete next;
		next = other.next;
		return *this;
	}
	List_Node_SingleWay<ElementType> &operator=(List_Node_SingleWay<ElementType> &&other)
	{
		Node<ElementType>::operator=(std::move(other));
		if (next)
			delete next;
		next = other.next;
		return *this;
	}

};

// 双链节点
template <typename ElementType>
class List_Node_DoubleWay : public Node<ElementType>
{
public:
	List_Node_DoubleWay<ElementType> *pre{nullptr};
	List_Node_DoubleWay<ElementType> *next{nullptr};

public:
	List_Node_DoubleWay() = default;
	List_Node_DoubleWay(const ElementType& element, List_Node_DoubleWay<ElementType> *pre = nullptr, List_Node_DoubleWay<ElementType> *next = nullptr)
		: Node<ElementType>(element), pre{pre}, next{next} {};
	List_Node_DoubleWay(ElementType &&element, List_Node_DoubleWay<ElementType> *pre = nullptr, List_Node_DoubleWay<ElementType> *next = nullptr)
		: Node<ElementType>(element), pre{pre}, next{next} {};

public: // Copy Conrtol
	List_Node_DoubleWay(const List_Node_DoubleWay<ElementType> &other)
		: Node<ElementType>(other)
	{
		if (this == &other)
			throw std::logic_error("Self assignment");
		if (pre)
			delete pre;
		pre = other.pre;

		if (next)
			delete next;
		next = other.next;
		pre = other.pre;
	}
	List_Node_DoubleWay(List_Node_DoubleWay<ElementType> &&other)
		: Node<ElementType>(other)
	{
		if (next)
			delete next;
		next = other.next;
		other.pre = nullptr;

		if (pre)
			delete pre;
		pre = other.pre;
		other.next = nullptr;
	}
	List_Node_DoubleWay<ElementType> &operator=(const List_Node_DoubleWay<ElementType> &other)
	{
		if (this == &other)
			throw std::logic_error("Self assignment");
		Node<ElementType>::operator=(other);
		if (pre)
			delete pre;
		pre = other.pre;

		if (next)
			delete next;
		next = other.next;
		return *this;
	}
	List_Node_DoubleWay<ElementType> &operator=(List_Node_DoubleWay<ElementType> &&other)
	{
		Node<ElementType>::operator=(std::move(other));
		if (next)
			delete next;
		next = other.next;
		other.pre = nullptr;

		if (pre)
			delete pre;
		pre = other.pre;
		other.next = nullptr;
		return *this;
	}
};