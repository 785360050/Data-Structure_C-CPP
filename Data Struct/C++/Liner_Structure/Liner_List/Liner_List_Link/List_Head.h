#pragma once

#include "../../List_Node.h"
#include "../Liner_List_ADT.h"


//链式存储结构模板
template <typename NodeType, typename DataType>
class Link_List:public Liner_List<NodeType,DataType>
{
public:
	size_t length = 0;
public:
	Link_List() :length{ 0 } {};
public:
	//清空线性表
	virtual void List_Clear() = 0;
	//销毁线性表
	virtual void List_Destroy() = 0;
	//判断线性表是否为空
	constexpr bool List_CheckEmpty() const { return length == 0; }
	//求当前表长度
	constexpr size_t List_GetLength() const { return length; }
	//返回第pos个元素的元素值
	virtual DataType List_GetElement(size_t pos) = 0;
	//显示线性表所有内容
	virtual void List_Show(const string& string) = 0;

	//定位节点
	virtual NodeType* Element_Locate(size_t pos) = 0;
	virtual NodeType* Element_Prior(const NodeType* const node) = 0;
	virtual NodeType* Element_Next(const NodeType* const node) const = 0;
	virtual void Element_Insert(size_t pos, DataType element) = 0;
	virtual DataType Element_Delete(size_t pos) = 0;
	virtual void Element_Update(size_t pos, DataType elem)
	{
		
		NodeType* node = Element_Locate(pos);
		node->element = elem;
	}


};
///precursor node == prior node



//单链表(头节点)
template<typename DataType>
class Link_List_Forward 
	:public Link_List<List_Node_SingleWay<DataType>, DataType>
{
public:
	List_Node_SingleWay<DataType>* front;///模板型成员变量
public:///链表操作
	Link_List_Forward() :front{ nullptr } {};
	~Link_List_Forward()
	{
		List_Destroy();
		front = nullptr;
	}
public:
	//重置所有元素值为0
	void List_Clear() override 
	{
		//while (front)
		//{
		//	Node_SingleLinked<DataType>* temp = front;
		//	front = front->next;
		//	delete temp;
		//}
		try
		{
			if (!front)
				throw 1;
		}
		catch (...)
		{
			std::cout << "List is not exist" << std::endl;
			return;
		}
		List_Node_SingleWay<DataType>* node = front;
		for (int i = 1; i <= this->length; i++)
		{
			node->element = 0;
			node = node->next;
		}
	}
	//释放整个表
	void List_Destroy() override
	{
		if (this->length > 0)
		{
			List_Node_SingleWay<DataType>* list = front;
			List_Node_SingleWay<DataType>* del;
			while (list->next != nullptr)
			{
				del = list;
				list = list->next;
				delete del;
			}
			this->length = 0;
		}
	}
	//返回第pos个元素的元素值
	DataType List_GetElement(size_t pos) override
	{
		try
		{
			if (pos<1 || pos>this->length)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Position is not exist" << std::endl;
			exit(0);
		}
		List_Node_SingleWay<DataType>* node = this->front;
		for (int i = 1; i <= Index(pos); i++)
			node = node->next;
		return node->element;
	}
	//显示整个链表
	void List_Show(const string& string) override
	{
		//List_Node_SingleWay<DataType>* node{ front };
		std::cout << string << std::endl
			<< "[front]: " << front << std::endl
			<< "[length]: " << this->length << std::endl
			<< "Head->";
		for (int index = 1; index <= this->length; index++)
			std::cout << '[' << index << ':' << List_GetElement(index) << "]->";
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
			if (this->length <= 1 || !front)
				throw 1;
		}
		catch (...)
		{
			std::cout << "前驱节点不存在" << std::endl;
			exit(0);
		}
		List_Node_SingleWay<DataType>* t = front;
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
			p->next = front;
			front = p;
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

public:
	//单链表头插法
	void Insert_Front(DataType element)
	{
		List_Node_SingleWay<DataType>* node = new List_Node_SingleWay<DataType>(element);
		if (front)
		{
			node->next = front;
			front = node;
		}
		else
			front = node;
		++this->length;
	}
	size_t Index(size_t pos) const
	{return --pos;}

};

//双向链表(头节点)
template<typename DataType>
class Link_List_Double
	:public Link_List<List_Node_DoubleWay<DataType>, DataType>
{
public:
	List_Node_DoubleWay<DataType>* front;
public:///链表操作
	Link_List_Double() :front{ nullptr } {};
	~Link_List_Double()
	{
		List_Destroy();
		front = nullptr;
	}
public:
	//重置所有元素值为0
	void List_Clear() override
	{
		try
		{
			if (!front)
				throw 1;
		}
		catch (...)
		{
			std::cout << "List is not exist" << std::endl;
			return;
		}
		List_Node_DoubleWay<DataType>* node = front;
		for (int i = 1; i <= this->length; i++)
		{
			node->element = 0;
			node = node->next;
		}
	}
	//释放整个表
	void List_Destroy() override
	{
		if (this->length > 0)
		{
			List_Node_DoubleWay<DataType>* del;
			while (front)
			{
				del = front;
				front = front->next;
				//front->pre = nullptr;
				delete del;
				--this->length;
			}
		}
	}

	//返回第pos个元素的元素值
	DataType List_GetElement(size_t pos) override
	{
		try
		{
			if (pos<1 || pos>this->length)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Position is not exist" << std::endl;
			exit(0);
		}
		List_Node_DoubleWay<DataType>* node = this->front;
		for (int i = 1; i <= Index(pos); i++)
			node = node->next;
		return node->element;
	}
	//显示整个链表
	void List_Show(const string& string) override
	{
		//List_Node_SingleWay<DataType>* node{ front };
		std::cout << string << std::endl
			<< "[front]: " << front << std::endl
			<< "[length]: " << this->length << std::endl
			<< "Head->";
		for (int index = 1; index <= this->length; index++)
			std::cout << '[' << index << ':' << List_GetElement(index) << "]<->";
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
			if (pos > this->length)
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
	//定位并返回node节点的前驱节点
	//(遍历链表)
	List_Node_DoubleWay<DataType>* Element_Prior(const List_Node_DoubleWay<DataType>* const node) override
	{
		try
		{
			if (this->length <= 1 || !front)
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
		{
			List_Node_DoubleWay<DataType>* p = new List_Node_DoubleWay<DataType>(element, nullptr, front);
			if (front)
				front->pre = p;
			front = p;
			++this->length;
		}
		else
		{
			List_Node_DoubleWay<DataType>* node = Element_Locate(pos);
			List_Node_DoubleWay<DataType>* p = new List_Node_DoubleWay<DataType>(element, node->pre, node);
			p->pre->next = p;
			p->next->pre = p;
			++this->length;
		}
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

public:
	size_t Index(size_t pos) const
	{return --pos;}
};
