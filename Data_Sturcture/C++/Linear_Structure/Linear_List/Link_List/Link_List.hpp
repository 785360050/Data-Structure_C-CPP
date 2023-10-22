#pragma once

#include <mutex> //call_once
#include <bitset>
#include <set>

#include "../../List_Node.hpp"
#include "../Linear_List.hpp"





namespace Storage
{

	// 链式存储结构模板
	template <typename NodeType, typename ElementType>
	class Link_List : public Logic::Linear_List<ElementType>
	{
	protected:
		NodeType *front{}; // 直接指向首元节点，没有头结点

	public:
		Link_List() = default;
		Link_List(size_t size) : Logic::Linear_List<ElementType>(size){};
		Link_List(const Storage::Link_List<NodeType, ElementType> &other)
			: Logic::Linear_List<ElementType>(other.size)
		{
			if(this==&other)
				throw std::logic_error("Self Copied");
			NodeType *node = other.front, *self = front;
			for (size_t i = 0; i < other.size; i++)
			{
				if (!node)
					throw std::logic_error("Copy Node Failed:size dose not match storage");
				if (!self)
				{
					front = new NodeType(node->element, nullptr);
					self = front; // node=nullptr时需要重新赋值，不然无效
					continue;
				}
				self->next = new NodeType(node->element, nullptr);
				self = self->next;
				node = node->next;
			}
		}
		Link_List(Storage::Link_List<NodeType, ElementType> &&other)
			: Logic::Linear_List<ElementType>(other.size)
		{
			front = other.front;
			other.front = nullptr;
			other.size = 0;
		}
		Link_List<NodeType, ElementType> &operator=(const Storage::Link_List<NodeType, ElementType> &other)
		{
			if (this == &other)
				throw std::logic_error("Self assignment");
			NodeType *node = other.front, *self = front;
			for (size_t i = 0; i < other.size; i++)
			{
				if (!node)
					throw std::logic_error("Copy Node Failed:size dose not match storage");
				if (!self)
				{
					front = new NodeType(node->element, nullptr);
					self = front; // node=nullptr时需要重新赋值，不然无效
					continue;
				}
				self->next = new NodeType(node->element, nullptr);
				self = self->next;
				node = node->next;
			}
			return *this;
		}
		Link_List<NodeType, ElementType> &operator=(Storage::Link_List<NodeType, ElementType> &&other)
		{
			front = other.front;
			other.front = nullptr;
			other.size = 0;
			return *this;
		}
		Link_List(std::initializer_list<ElementType> list)
			: Logic::Linear_List<ElementType>(list.size())
		{
			NodeType *node = front;
			for (const auto &element : list)
			{
				if (!node)
				{
					front = new NodeType(std::move(element), nullptr);
					node = front; // node=nullptr时需要重新赋值，不然无效
					continue;
				}
				node->next = new NodeType(std::move(element), nullptr);
				node = node->next;
			}
		}

		virtual ~Link_List() = default;

	private:
		virtual NodeType *_Element_Locate(size_t pos) = 0;

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
			return _Element_Locate(pos)->element;
		}

		virtual NodeType *Element_Prior(const NodeType *const node) = 0;
		virtual NodeType *Element_Next(const NodeType *const node) = 0;
		virtual void Element_Insert(size_t pos, const ElementType &element) = 0;
		virtual void Element_Insert(size_t pos, ElementType &&element) = 0;
		virtual void Element_Delete(size_t pos) = 0;
		virtual void Element_Update(size_t pos, ElementType &&elem) { _Element_Locate(pos)->element = std::forward<ElementType>(elem); }
	};

	/// ============================================================================================================
	/// 		静态链表，顺序实现
	/// ============================================================================================================
	template <typename NodeType, typename ElementType, size_t maxsize>
	class Link_List_Static : public Logic::Linear_List<ElementType>
	{
	public:
		static constexpr size_t npos = maxsize;//无效index，类似nullptr,std::string::npos
	protected:
		// using Record = NodeType;
		size_t front{npos}; // 首元素的下标,初始化为index_end+1,表示npos
		NodeType storage[maxsize]{};
		// 空闲列表，记录当前可用的数据
		struct Free_List
		{
		private:
			std::bitset<maxsize> free_list{}; // 0表示空闲，1表示已分配
			size_t index{};
			void Increase() { index = (++index) % maxsize; }
			// void Decrease() { index = (--index) % maxsize; }
		public:
			// 获取一个空闲的位置
			size_t Allocate()
			{ // 循环遍历查找空闲的位置
				if (free_list.all())
					throw std::runtime_error("No Free Space");
				while (free_list[index])
					Increase();
				free_list.set(index);
				return index;
			}
			// 归还一个位置
			void Deallocate(size_t pos)
			{
				if (!free_list[pos])
					std::logic_error("Insert Failed:Already Free before Insert");
				free_list.reset(pos);
			}
		};
		Free_List free_list{};

	public:
		Link_List_Static() = default;
		Link_List_Static(size_t size) : Logic::Linear_List<ElementType>(size){};
		Link_List_Static(const Storage::Link_List_Static<NodeType, ElementType,maxsize> &other)
			: Logic::Linear_List<ElementType>(other.size)
		{
			for (size_t i = 0; i < maxsize; i++)
				storage[i] = other.storage[i];
		}
		Link_List_Static(Storage::Link_List_Static<NodeType, ElementType, maxsize> &&other)
			: Logic::Linear_List<ElementType>(other.size)
		{
			for (size_t i = 0; i < maxsize; i++)
			{
				storage[i] = std::move(other.storage[i]);
				other.storage[i] = NodeType{};
			}
			other.size = 0;
		}

		Link_List_Static<NodeType, ElementType, maxsize> &
		operator=(const Storage::Link_List_Static<NodeType, ElementType, maxsize> &other)
		{
			if(this==&other)
				throw std::logic_error("Self Copied");

			this->size = other.size;
			for (size_t i = 0; i < this->size; i++)
				storage[i] = other.storage[i];
			return *this;
		}

		Link_List_Static<NodeType, ElementType, maxsize> &
		operator=(Storage::Link_List_Static<NodeType, ElementType, maxsize> &&other)
		{
			this->size = other.size;
			for (size_t i = 0; i < this->size; i++)
			{
				storage[i] = std::move(other.storage[i]);
				other.storage[i] = NodeType{};
			}
			other.size = 0;
			return *this;
		}
		
		Link_List_Static(std::initializer_list<ElementType> list)
			: Logic::Linear_List<ElementType>(list.size())
		{
			if (list.size() > maxsize)
				throw std::runtime_error("initializer_list Constructed Failed: no enough capcity");
			this->size = list.size();
			size_t i{};
			for (const auto &element : list)
				storage[i++] = std::move(element);
		}


	protected:
		static size_t Index(size_t pos)
		{
			if (pos == 0)
				throw std::out_of_range("size_t pos == 0");
			return --pos;
		}
		void _Reset_Front() { front = npos; }
		// 返回单链表第pos个元素节点的下标
		size_t _Element_Locate(size_t pos)
		{
			// 判断非空且不超过l->size
			if (pos < 1)
				throw std::out_of_range("LocateNode Faild: Position < 1");
			if (pos > this->size)
				throw std::out_of_range("LocateNode Faild: Position > List size");

			NodeType &node = storage[front];
			size_t index = front;
			for (size_t i{}; i < pos; ++i, index = node.next)
				;
			return index;
		}

	public:
		// 清空线性表(删除所有节点)
		virtual void List_Clear() override
		{
			for (size_t i = 0; i < maxsize; i++)
				storage[i]=NodeType{};
			this->size = 0;
			_Reset_Front();
		}
		// 显示线性表所有内容
		virtual void List_Show(const string &string="")
		{
			std::cout << string << std::endl
					  << "[front]: " << front << std::endl
					  << "[size]: " << this->size << std::endl
					  << "front->";
			const NodeType *node = &storage[front];
			size_t index{front};//记录当前节点的下标
			for (size_t i = 1; i <= this->size; i++)
			{
				std::cout << '[' << i << ':' <<index<<':'<< node->element << "]->";
				index = node->next;
				node = &storage[node->next];
			}

			std::cout << "npos\n";

			static std::once_flag show_node_format;
			std::call_once(show_node_format, []()
						   { std::cout << "Node format=[position:index:element]" << std::endl; });
		}
		constexpr size_t Get_Capcity() const { return maxsize; }

		// 定位节点
		virtual ElementType &operator[](size_t pos) override
		{
			if (pos > this->size)
				throw std::out_of_range("Position is not exist");
			size_t index{front};
			for (size_t i = 0; i < pos; ++i)
				index = storage[index].next;
			return storage[index].element;
		}

		// virtual NodeType *Element_Prior(const NodeType *const node)
		// {return storage[node.pre].element;}
		// virtual NodeType *Element_Next(const NodeType *const node)
		// {return storage[node.next].element;}
		virtual void Element_Insert(size_t pos, const ElementType &element)
		{
			if (pos < 1 || pos > this->size + 1)
				throw std::out_of_range("List insert failed: Position out of range");
			if (this->size >= maxsize)
				throw std::runtime_error("List insert failed: List is full");

			if (front == npos)
			{
				front = free_list.Allocate();
				this->storage[front] = NodeType(element,npos,npos);
			}
			else
			{
				size_t index_left{front}, index_right{npos}, index_allocated{free_list.Allocate()};
				// 找到pos插入位置附近的两个节点
				for (size_t i = 1; i < pos - 1; i++)
					index_left = storage[index_left].next;
				index_right = storage[index_left].next;
				storage[index_allocated] = NodeType(element, index_left, index_right);
				storage[index_left].next = index_allocated;
				if(index_right!= npos)
					storage[index_right].pre = index_allocated;
			}
			++this->size;
		}
		virtual void Element_Insert(size_t pos, ElementType &&element)
		{
			if (pos < 1 || pos > this->size + 1)
				throw std::out_of_range("List insert failed: Position out of range");
			if (this->size >= maxsize)
				throw std::runtime_error("List insert failed: List is full");

			if (front == npos)
			{
				front = free_list.Allocate();
				this->storage[front] = NodeType(std::forward<ElementType>(element), npos, npos);
			}
			else
			{
				size_t index_left{front}, index_right{npos}, index_allocated{free_list.Allocate()};
				// 找到pos插入位置附近的两个节点
				for (size_t i = 1; i < pos - 1; i++)
					index_left = storage[index_left].next;
				index_right = storage[index_left].next;
				storage[index_allocated] = NodeType(std::forward<ElementType>(element), index_left, index_right);
				storage[index_left].next = index_allocated;
				if (index_right != npos)
					storage[index_right].pre = index_allocated;
			}
			++this->size;
		}
		virtual void Element_Delete(size_t pos)
		{
			size_t index = _Element_Locate(pos);
			NodeType node = storage[index];
			storage[node.pre].next = node.next;
			storage[node.next].pre = node.pre;
			storage[index]=NodeType{};//delete node
			free_list.Deallocate(index);
			--this->size;
		}
		virtual void Element_Update(size_t pos, ElementType &&elem) { storage[_Element_Locate(pos)]= std::forward<ElementType>(elem); }
	};

	/// precursor node == prior node

}

/// ——————————————————————————————————————————————————
///  模板特例
/// ——————————————————————————————————————————————————
// 单链表(头节点)
template <typename ElementType>
class Link_List_Forward
	: public Storage::Link_List<List_Node_SingleWay<ElementType>, ElementType>
{
	using NodeType = List_Node_SingleWay<ElementType>;

public: /// 链表操作
	Link_List_Forward() = default;
	Link_List_Forward(std::initializer_list<ElementType> list)
		: Storage::Link_List<NodeType, ElementType>(list.size())
	{
		NodeType *node = this->front;
		for (const auto &element : list)
		{
			if (!node)
			{
				this->front = new NodeType(std::move(element), nullptr);
				node = this->front; // node=nullptr时需要重新赋值，不然无效
				continue;
			}
			node->next = new NodeType(std::move(element), nullptr);
			node = node->next;
		}
	}
	~Link_List_Forward()
	{
		this->List_Clear();
	}

private:
	// 定位并返回单链表第pos个元素节点
	NodeType *_Element_Locate(size_t pos) override
	{
		// 判断非空且不超过l->size
		if (pos < 1)
			throw std::out_of_range("LocateNode Faild: Position < 1");
		if (pos > this->size)
			throw std::out_of_range("LocateNode Faild: Position > List size");

		NodeType *p = this->front;
		for (size_t i = 1; i < pos; i++)
		{ // 遍历定位到第pos个元素节点
			p = p->next;
		}
		if (!p)
			throw std::runtime_error("Element_Locate Failed: Node Unexist");
		return p;
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

public: /// 元素操作
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
	NodeType *Element_Next(const NodeType *const node) override
	{
		return node->next;
	}

	// 在单链表第pos位置插入新建的元素element
	void Element_Insert(size_t pos, const ElementType &element) override
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
			p_pri = _Element_Locate(pos - 1);
			p->next = p_pri->next;
			p_pri->next = p;
			++this->size;
		}
	}
	void Element_Insert(size_t pos, ElementType &&element) override
	{
		if (pos < 1 || pos > this->size + 1)
			throw std::out_of_range("Insert Faild: Illegal position");
		NodeType *p = new NodeType(element); // move
		if (pos == 1)
		{
			p->next = this->front;
			this->front = p;
			++this->size;
		}
		else
		{
			NodeType *p_pri;
			p_pri = _Element_Locate(pos - 1);
			p->next = p_pri->next;
			p_pri->next = p;
			++this->size;
		}
	}
	// 删除链表L的第pos个元素节点
	void Element_Delete(size_t pos) override
	{
		// NodeType *node = Element_Locate(pos - 1);
		NodeType *node = this->Element_Prior(_Element_Locate(pos));
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
	: public Storage::Link_List<List_Node_DoubleWay<ElementType>, ElementType>
{
	using NodeType = List_Node_DoubleWay<ElementType>;

public:
	Link_List_Double() = default;
	Link_List_Double(std::initializer_list<ElementType> list)
		: Storage::Link_List<NodeType, ElementType>(list.size())
	{
		NodeType *node = this->front;
		for (const auto &element : list)
		{
			if (!node)
			{
				this->front = new NodeType(std::move(element), nullptr);
				node = this->front; // node=nullptr时需要重新赋值，不然无效
				continue;
			}
			node->next = new NodeType(std::move(element), nullptr);
			node = node->next;
		}
	}
	~Link_List_Double()
	{
		List_Clear();
	}

private:
	// 定位并返回单链表第pos个元素节点
	NodeType *_Element_Locate(size_t pos) override
	{ // 判断非空且不超过l->size
		if (pos == 0)
			throw std::out_of_range("LocateNode Faild: Position = 0");
		if (pos > this->size)
			throw std::out_of_range("LocateNode Faild: Position > List size");

		NodeType *p = this->front;
		for (size_t i = 1; i < pos; i++)
		{ // 遍历定位到第pos个元素节点
			p = p->next;
		}
		return p;
	}

public: /// 链表操作
	void List_Clear() override
	{
		if (this->size <= 0)
			return;

		NodeType *del;
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

public: /// 元素操作
	// 定位并返回node节点的前驱节点(遍历链表)
	NodeType *Element_Prior(const NodeType *const node) override
	{
		if (this->size <= 1 || !this->front)
			throw std::runtime_error("前驱节点不存在");
		return node->pre;
	}
	// 定位并返回node节点的后继节点
	NodeType *Element_Next(const NodeType *const node) override
	{
		return node->next;
	}

	// 在单链表第pos位置插入新建的元素element
	void Element_Insert(size_t pos, const ElementType &element) override
	{
		if (pos < 1 || pos > this->size + 1)
			throw std::out_of_range("Insert Faild: Illegal position");
		if (pos == 1)
		{ /// 头插
			NodeType *p = new NodeType(element, nullptr, this->front);
			if (this->front)
				this->front->pre = p;
			this->front = p;
		}
		else if (pos == this->size + 1)
		{ /// 尾插
			NodeType *pre = this->front;
			while (pre->next)
				pre = pre->next;
			NodeType *node = new NodeType(element, pre, nullptr);
			pre->next = node;
		}
		else
		{ /// 中间插入
			NodeType *node = _Element_Locate(pos);
			NodeType *p = new NodeType(element, node->pre, node);
			p->pre->next = p;
			p->next->pre = p;
		}
		++this->size;
	}
	void Element_Insert(size_t pos, ElementType &&element) override
	{
		if (pos < 1 || pos > this->size + 1)
			throw std::out_of_range("Insert Faild: Illegal position");
		if (pos == 1)
		{ /// 头插
			NodeType *p = new NodeType(element, nullptr, this->front);
			if (this->front)
				this->front->pre = p;
			this->front = p;
		}
		else if (pos == this->size + 1)
		{ /// 尾插
			NodeType *pre = this->front;
			while (pre->next)
				pre = pre->next;
			NodeType *node = new NodeType(element, pre, nullptr);
			pre->next = node;
		}
		else
		{ /// 中间插入
			NodeType *node = _Element_Locate(pos);
			NodeType *p = new NodeType(element, node->pre, node);
			p->pre->next = p;
			p->next->pre = p;
		}
		++this->size;
	}
	// 删除链表L的第pos个元素节点
	void Element_Delete(size_t pos) override
	{
		NodeType *node = _Element_Locate(pos);
		if (pos == 1) // 删首元节点
		{
			this->front = node->next;
			this->front->pre = nullptr;
		}
		else
		{
			if (!node->next) // 删尾节点
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

template <typename ElementType, size_t maxsize>
using Link_List_Static = Storage::Link_List_Static<List_Node_Record<ElementType>, ElementType, maxsize>;

#if __cplusplus >= 202002L
#include "../ADT.hpp"
static_assert(ADT::Linear_List<Link_List_Forward<int>, int>);
static_assert(ADT::Linear_List<Link_List_Double<int>, int>);
static_assert(ADT::Linear_List<Link_List_Static<int,5>, int>);
#endif