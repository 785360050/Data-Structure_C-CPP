#pragma once
#include <iostream>
#include "../Node.hpp"


/// ============================================================================================================
/// 关于链式节点的拷贝控制：
/// 		1. 所有的节点拷贝和移动，仅对节点指针做浅拷贝。
/// 		因为拷贝和移动，逻辑上都只针对当前节点本身而不是所有
/// 		2. 对一个已经存在前驱或后继的节点做移动时，会导致当前节点所在的链前后断开
/// 		在移动时，请确保被移动的节点已经从链中删除
/// 		
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

/// @brief 静态链表的节点
/// 	没有想到什么好名字，可能非常不直观，
/// 	叫Record仅因为mysql的innodb也使用了静态链表实现
template <typename ElementType>
class List_Node_Record : public Node<ElementType>
{
public:
	size_t pre{};//上个节点的下标
	size_t next{};//下个节点的下标
	

public:
	List_Node_Record() = default;
	List_Node_Record(const ElementType &element, size_t index_pre = 0, size_t index_next = 0)
		: Node<ElementType>(element), pre{index_pre}, next{index_next} {};
	List_Node_Record(ElementType &&element, size_t index_pre=0, size_t index_next=0)
		: Node<ElementType>(std::forward<ElementType>(element)), pre{index_pre}, next{index_next} {};

public: // Copy Conrtol
	List_Node_Record(const List_Node_Record<ElementType> &other)
		: Node<ElementType>(other),pre{other.pre}, next{other.next}
	{
		if (this == &other)
			throw std::logic_error("Self assignment");
	}
	List_Node_Record(List_Node_Record<ElementType> &&other)
		: Node<ElementType>(std::move(other)), pre{other.pre}, next{other.next}
	{
		other.pre = size_t{};
		other.next = size_t{};
	}
	List_Node_Record<ElementType> &operator=(const List_Node_Record<ElementType> &other)
	{
		if (this == &other)
			throw std::logic_error("Self assignment");
		Node<ElementType>::operator=(other);
		pre = other.pre;
		next = other.next;
		return *this;
	}

	/// @brief 仅移动元素值，指针仅拷贝。会导致当前的前后继节点断开
	/// @note 在移动时，请确保被移动的节点已经从链中删除。见当前文件的开头注释
	List_Node_Record<ElementType> &operator=(List_Node_Record<ElementType> &&other)
	{
		Node<ElementType>::operator=(std::move(other));
		// if (next)
		// 	throw std::logic_error("Danger: Causing all next nodes to be destructed");
		next = other.next;
		other.next = size_t{};

		// if (pre)
		// 	throw std::logic_error("Danger: Causing all precursor nodes to be destructed");
		pre = other.pre;
		other.pre = size_t{};
		return *this;
	}
};

/// @brief 跳表的结点
/// @tparam ElementType
/// @tparam size
/// @note 由于一个节点在创建之后的高度不会变动，但是每个节点的高度不一定相同，所以只能在堆上申请指针数组
template <typename ElementType>
struct List_Node_Skiplist
{
	using Node = List_Node_Skiplist<ElementType> ;
	ElementType element{};
	Node** next{}; // 指针数组。node->next[level]
	Node* prev{}; // 指针数组。node->next[level]
	size_t level{}; // 当前节点的最高层数

	// 构造函数
	List_Node_Skiplist() = default;
	// List_Node_Skiplist(const ElementType &element) : element(element) {}
	List_Node_Skiplist(size_t level) 
	: level{level}, next(new List_Node_Skiplist<ElementType> *[level] {}) {}
	List_Node_Skiplist(const ElementType &element, size_t level)//0层的元素next为1个空间，不可能new Node[0]
		: element(element),level{level}, next(new List_Node_Skiplist<ElementType>*[level+1]{}) {}
	~List_Node_Skiplist()
	{
		delete[] next;
	}
};
