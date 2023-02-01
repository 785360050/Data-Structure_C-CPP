#pragma once

#include "../../List_Node.h"
#include "../Liner_List.h"

//链式存储结构模板
template <typename NodeType, typename DataType>
class Link_List:public Liner_List<NodeType,DataType>
{
public:
	Link_List() :Liner_List<NodeType, DataType>(){};
	virtual ~Link_List() = default;
public:
	//清空线性表(删除所有节点)
	virtual void List_Clear() = 0;
	DataType List_GetData(size_t pos)
	{
		try
		{
			if (pos<1 || pos>this->length)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Position is not exist" << std::endl;
			return NULL;
		}
		return Element_Locate(pos)->element;
	}
	//显示线性表所有内容
	virtual void List_Show(const string& string) = 0;

	//定位节点
	virtual NodeType* Element_Locate(size_t pos) = 0;
	virtual NodeType* Element_Prior(const NodeType* const node) = 0;
	virtual NodeType* Element_Next(const NodeType* const node) const = 0;
	virtual void Element_Insert(size_t pos, DataType element) = 0;
	virtual DataType Element_Delete(size_t pos) = 0;
	virtual void Element_Update(size_t pos, DataType elem)
	{Element_Locate(pos)->element = elem;}


};
///precursor node == prior node


///——————————————————————————————————————————————————
/// 模板特例
///——————————————————————————————————————————————————
//单链表(头节点)
template<typename DataType>
class Link_List_Forward 
	:public Link_List<List_Node_SingleWay<DataType>, DataType>
{
public:///链表操作
	Link_List_Forward() :Link_List<List_Node_SingleWay<DataType>,DataType>(){};
	~Link_List_Forward()
	{List_Clear(); }
public:
	void List_Clear() override
	{
		if (this->length > 0)
		{
			List_Node_SingleWay<DataType>* del;
			while (this->front)
			{
				del = this->front;
				this->front = this->front->next;
				delete del;
				--this->length;
			}
		}
	}
	void List_Show(const string& string) override
	{
		std::cout << string << std::endl
			<< "[front]: " << this->front << std::endl
			<< "[length]: " << this->length << std::endl
			<< "Front->";
		for (int index = 1; index <= this->length; index++)
			std::cout << '[' << index << ':' << this->List_GetData(index) << "]->";
		std::cout << "NULL\n";
	}
	//定位并返回单链表第pos个元素节点
public:///元素操作
	List_Node_SingleWay<DataType>* Element_Locate(size_t pos) override
	{
		try
		{//判断非空且不超过l->length
			if (pos <= 0)
				throw std::out_of_range("LocateNode Faild: Position < 0");
			if (pos > this->length)
				throw std::out_of_range("LocateNode Faild: Position > List Length");
		}
		catch (const std::exception e)
		{
			std::cout << e.what() << std::endl;
			return nullptr;
		}

		List_Node_SingleWay<DataType>* p = this->front;
		for (int i = 1; i < pos; i++)
		{//遍历定位到第pos个元素节点
			p = p->next;
		}
		return p;
	}
	//定位并返回node节点的前驱节点(遍历链表)
	List_Node_SingleWay<DataType>* Element_Prior(const List_Node_SingleWay<DataType>* const node) override
	{
		try
		{
			if (this->length <= 1 || !this->front)
				throw 1;
		}
		catch (...)
		{
			std::cout << "前驱节点不存在" << std::endl;
			exit(0);
		}
		List_Node_SingleWay<DataType>* t = this->front;
		while (t->next != node)
		{///定位前驱节点
			t = t->next;
		}
		return t;
	}
	//定位并返回node节点的后继节点
	List_Node_SingleWay<DataType>* Element_Next(const List_Node_SingleWay<DataType>* const node) const override
	{return node->next;}

	//在单链表第pos位置插入新建的元素element
	void Element_Insert(size_t pos, DataType element) override
	{
		try
		{
			if (pos< 1 || pos>this->length + 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Insert Faild: Illegal position" << std::endl;
			return;
		}
		List_Node_SingleWay<DataType>* p = new List_Node_SingleWay<DataType>(element);
		if (pos == 1)
		{
			p->next = this->front;
			this->front = p;
			++this->length;
		}
		else
		{
			List_Node_SingleWay<DataType>* p_pri;
			p_pri = Element_Locate(pos - 1);
			p->next = p_pri->next;
			p_pri->next = p;
			++this->length;
		}
	}
	//删除链表L的第pos个元素节点
	DataType Element_Delete(size_t pos) override
	{
		List_Node_SingleWay<DataType>* node = Element_Locate(pos - 1);
		List_Node_SingleWay<DataType>* del = node->next;
		node->next = del->next;
		DataType temp = del->element;
		delete del;
		--this->length;
		return temp;
	}

};

//双向链表(头节点)
template<typename DataType>
class Link_List_Double
	:public Link_List<List_Node_DoubleWay<DataType>, DataType>
{
public:
	Link_List_Double() :Link_List<List_Node_DoubleWay<DataType>, DataType>() {};
	~Link_List_Double()
	{
		List_Clear();
	}
public:///链表操作
	void List_Clear() override
	{
		if (this->length > 0)
		{
			List_Node_DoubleWay<DataType>* del;
			while (this->front)
			{
				del = this->front;
				this->front = this->front->next;
				delete del;
				--this->length;
			}
		}
	}
	void List_Show(const string& string) override
	{
		std::cout << string << std::endl
			<< "[front]: " << this->front << std::endl
			<< "[length]: " << this->length << std::endl
			<< "Front->";
		for (int index = 1; index <= this->length; index++)
			std::cout << '[' << index << ':' << this->List_GetData(index) << "]<->";
		std::cout << "NULL\n";
	}
	//定位并返回单链表第pos个元素节点
public:///元素操作
	List_Node_DoubleWay<DataType>* Element_Locate(size_t pos) override
	{
		try
		{//判断非空且不超过l->length
			if (pos <= 0)
				throw std::out_of_range("LocateNode Faild: Position < 0");
			if (pos > this->length + 1)
				throw std::out_of_range("LocateNode Faild: Position > List Length");
		}
		catch (const std::exception e)
		{
			std::cout << e.what() << std::endl;
			return nullptr;
		}

		List_Node_DoubleWay<DataType>* p = this->front;
		for (int i = 1; i < pos; i++)
		{//遍历定位到第pos个元素节点
			p = p->next;
		}
		return p;
	}
	//定位并返回node节点的前驱节点(遍历链表)
	List_Node_DoubleWay<DataType>* Element_Prior(const List_Node_DoubleWay<DataType>* const node) override
	{
		try
		{
			if (this->length <= 1 || !this->front)
				throw 1;
		}
		catch (...)
		{
			std::cout << "前驱节点不存在" << std::endl;
			exit(0);
		}
		return node->pre;
	}
	//定位并返回node节点的后继节点
	List_Node_DoubleWay<DataType>* Element_Next(const List_Node_DoubleWay<DataType>* const node) const override
	{
		return node->next;
	}

	//在单链表第pos位置插入新建的元素element
	void Element_Insert(size_t pos, DataType element) override
	{
		try
		{
			if (pos< 1 || pos>this->length + 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Insert Faild: Illegal position" << std::endl;
			return;
		}
		if (pos == 1)
		{///头插
			List_Node_DoubleWay<DataType>* p = new List_Node_DoubleWay<DataType>(element, nullptr, this->front);
			if (this->front)
				this->front->pre = p;
			this->front = p;
		}
		else if (pos == this->length + 1)
		{///尾插
			List_Node_DoubleWay<DataType>* pre = this->front;
			while (pre->next)
				pre = pre->next;
			List_Node_DoubleWay<DataType>* node = new List_Node_DoubleWay<DataType>(element, pre, nullptr);
			pre->next = node;
		}
		else
		{///中间插入
			List_Node_DoubleWay<DataType>* node = Element_Locate(pos);
			List_Node_DoubleWay<DataType>* p = new List_Node_DoubleWay<DataType>(element, node->pre, node);
			p->pre->next = p;
			p->next->pre = p;
		}
		++this->length;
	}
	//删除链表L的第pos个元素节点
	DataType Element_Delete(size_t pos) override
	{
		List_Node_DoubleWay<DataType>* node = Element_Locate(pos);
		node->next->pre = node->pre;
		node->pre->next = node->next;
		DataType value = node->element;
		delete node;
		--this->length;
		return value;
	}

};
