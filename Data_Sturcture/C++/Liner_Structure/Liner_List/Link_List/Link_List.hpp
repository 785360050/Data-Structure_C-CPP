#pragma once

#include <mutex>

#include "../../List_Node.hpp"
#include "../Liner_List.hpp"

// 链式存储结构模板
template <typename NodeType, typename ElementType>
class Link_List : public Logic::Liner_List<ElementType>
{
protected:
	NodeType *front{}; // 直接指向首元节点，没有头结点

public:
	virtual ~Link_List() = default;

public:
	// 清空线性表(删除所有节点)
	virtual void List_Clear() = 0;
	// 显示线性表所有内容
	virtual void List_Show(const string &string) = 0;
	size_t Get_Capcity() const { return this->Get_Size(); }

	// 定位节点
	virtual ElementType &operator[](size_t pos) override
	{
		if (pos < 1 || pos > this->size)
			throw std::out_of_range("Position is not exist");
		return Element_Locate(pos)->element;
	}
	virtual NodeType *Element_Locate(size_t pos) = 0;
	virtual NodeType *Element_Prior(const NodeType *const node) = 0;
	virtual NodeType *Element_Next(const NodeType *const node) const = 0;
	virtual void Element_Insert(size_t pos, ElementType element) = 0;
	virtual void Element_Delete(size_t pos) = 0;
	virtual void Element_Update(size_t pos, ElementType elem) { Element_Locate(pos)->element = elem; }
};
/// precursor node == prior node

/// ——————————————————————————————————————————————————
///  模板特例
/// ——————————————————————————————————————————————————
// 单链表(头节点)
template <typename ElementType>
class Link_List_Forward : public Link_List<List_Node_SingleWay<ElementType>, ElementType>
{
	using NodeType = List_Node_SingleWay<ElementType>;

public: /// 链表操作
	Link_List_Forward() : Link_List<NodeType, ElementType>(){};
	~Link_List_Forward()
	{
		this->List_Clear();
	}

public:
	void List_Clear() override
	{
		if (!this->Is_Empty())
		{
			NodeType *del;
			while (this->front)
			{
				del = this->front;
				this->front = this->front->next;
				delete del;
				--this->size;
			}
		}
	}
	void List_Show(const string &string) override
	{
		std::cout << string << std::endl
				  << "[front]: " << this->front << std::endl
				  << "[size]: " << this->size << std::endl
				  << "front->";
		NodeType *node = this->front;
		while (node && node->next)
		{
			size_t pos{};
			std::cout << '[' << ++pos << ':' << node->element << "]->";
			node = node->next;
		}
		std::cout << "nullptr\n";

		static std::once_flag show_node_format;
		std::call_once(show_node_format, []()
					   { std::cout << "Node format=[position:element]" << std::endl; });
	}
	// 定位并返回单链表第pos个元素节点
public: /// 元素操作
	NodeType *Element_Locate(size_t pos) override
	{
		// 判断非空且不超过l->size
		if (pos < 1)
			throw std::out_of_range("LocateNode Faild: Position < 1");
		if (pos > this->size)
			throw std::out_of_range("LocateNode Faild: Position > List size");

		NodeType *p = this->front;
		for (int i = 1; i < pos; i++)
		{ // 遍历定位到第pos个元素节点
			p = p->next;
		}
		if (!p)
			throw std::runtime_error("Element_Locate Failed: Node Unexist");
		return p;
	}
	// 定位并返回node节点的前驱节点(遍历链表)
	NodeType *Element_Prior(const NodeType *const node) override
	{
		if (this->size <= 1 || !this->front)
			throw std::out_of_range("前驱节点不存在");
		if (node == this->front)
			return nullptr;
		NodeType *t = this->front;
		while (t && t->next != node)
		{ /// 定位前驱节点
			t = t->next;
		}
		if (!t)
			throw std::runtime_error("Prior Node Unexists: Can't Locate current Node");
		return t;
	}
	// 定位并返回node节点的后继节点
	NodeType *Element_Next(const NodeType *const node) const override
	{
		return node->next;
	}

	// 在单链表第pos位置插入新建的元素element
	void Element_Insert(size_t pos, ElementType element) override
	{
		if (pos < 1 || pos > this->size + 1)
			throw std::out_of_range("Insert Faild: Illegal position");
		NodeType *p = new NodeType(element);
		if (pos == 1)
		{
			p->next = this->front;
			this->front = p;
			++this->size;
		}
		else
		{
			NodeType *p_pri;
			p_pri = Element_Locate(pos - 1);
			p->next = p_pri->next;
			p_pri->next = p;
			++this->size;
		}
	}
	// 删除链表L的第pos个元素节点
	void Element_Delete(size_t pos) override
	{
		// NodeType *node = Element_Locate(pos - 1);
		NodeType *node = this->Element_Prior(Element_Locate(pos));
		NodeType *del{};
		if (!node) // 当前节点是首元节点
		{
			del = this->front;
			this->front = del->next;
		}
		else [[likely]]
		{
			del = node->next;
			node->next = del->next;
		}
		delete del;
		--this->size;
	}
};

// 双向链表(头节点)
template <typename ElementType>
class Link_List_Double
	: public Link_List<List_Node_DoubleWay<ElementType>, ElementType>
{
public:
	Link_List_Double() : Link_List<List_Node_DoubleWay<ElementType>, ElementType>(){};
	~Link_List_Double()
	{
		List_Clear();
	}

public: /// 链表操作
	void List_Clear() override
	{
		if (this->size <= 0)
			return;

		List_Node_DoubleWay<ElementType> *del;
		while (this->front)
		{
			del = this->front;
			this->front = this->front->next;
			delete del;
			--this->size;
		}
	}
	void List_Show(const string &string) override
	{
		std::cout << string << std::endl
				  << "[front]: " << this->front << std::endl
				  << "[size]: " << this->size << std::endl
				  << "front->";
		List_Node_DoubleWay<ElementType> *node = this->front;
		while (node && node->next)
		{
			size_t pos{};
			std::cout << '[' << ++pos << ':' << node->element << "]->";
			node = node->next;
		}
		std::cout << "nullptr\n";

		static std::once_flag show_node_format;
		std::call_once(show_node_format, []()
					   { std::cout << "Node format=[position:element]" << std::endl; });
	}
	// 定位并返回单链表第pos个元素节点
public: /// 元素操作
	List_Node_DoubleWay<ElementType> *Element_Locate(size_t pos) override
	{ // 判断非空且不超过l->size
		if (pos < 0)
			throw std::out_of_range("LocateNode Faild: Position < 0");
		if (pos > this->size)
			throw std::out_of_range("LocateNode Faild: Position > List size");

		List_Node_DoubleWay<ElementType> *p = this->front;
		for (int i = 1; i < pos; i++)
		{ // 遍历定位到第pos个元素节点
			p = p->next;
		}
		return p;
	}
	// 定位并返回node节点的前驱节点(遍历链表)
	List_Node_DoubleWay<ElementType> *Element_Prior(const List_Node_DoubleWay<ElementType> *const node) override
	{
		if (this->size <= 1 || !this->front)
			throw std::runtime_error("前驱节点不存在");
		return node->pre;
	}
	// 定位并返回node节点的后继节点
	List_Node_DoubleWay<ElementType> *Element_Next(const List_Node_DoubleWay<ElementType> *const node) const override
	{
		return node->next;
	}

	// 在单链表第pos位置插入新建的元素element
	void Element_Insert(size_t pos, ElementType element) override
	{
		if (pos < 1 || pos > this->size + 1)
			throw std::out_of_range("Insert Faild: Illegal position");
		if (pos == 1)
		{ /// 头插
			List_Node_DoubleWay<ElementType> *p = new List_Node_DoubleWay<ElementType>(element, nullptr, this->front);
			if (this->front)
				this->front->pre = p;
			this->front = p;
		}
		else if (pos == this->size + 1)
		{ /// 尾插
			List_Node_DoubleWay<ElementType> *pre = this->front;
			while (pre->next)
				pre = pre->next;
			List_Node_DoubleWay<ElementType> *node = new List_Node_DoubleWay<ElementType>(element, pre, nullptr);
			pre->next = node;
		}
		else
		{ /// 中间插入
			List_Node_DoubleWay<ElementType> *node = Element_Locate(pos);
			List_Node_DoubleWay<ElementType> *p = new List_Node_DoubleWay<ElementType>(element, node->pre, node);
			p->pre->next = p;
			p->next->pre = p;
		}
		++this->size;
	}
	// 删除链表L的第pos个元素节点
	void Element_Delete(size_t pos) override
	{
		List_Node_DoubleWay<ElementType> *node = Element_Locate(pos);
		if (pos == 1) // 删首元节点
		{
			this->front = node->next;
			this->front->pre = nullptr;
		}
		else
		{
			if(!node->next) //删尾节点
				node->pre->next = nullptr;
			else
			{
				node->next->pre = node->pre;
				node->pre->next = node->next;
			}
		}
			delete node;
		--this->size;
	}
};
