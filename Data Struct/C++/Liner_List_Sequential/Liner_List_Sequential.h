#pragma once


//#include "Object.h"
#include "Liner_List_ADT.h"

template <typename DataType>
class Sequential_List
{///ADT 
protected:
	DataType* head;		///数组入口
	size_t length = 0;	///当前元素个数
	size_t maxsize;		///当前最大容量
public:
	//初始化表头
	Sequential_List() :head{ nullptr }, length{ 0 }, maxsize{ 0 } {};
	//创建有maxsize个元素空间的顺序表，返回表首地址
	Sequential_List(size_t maxsize)
	{//maxsize必须>0
		try
		{
			if (maxsize < 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "List Init Failed: maxsize must be greater than 1" << std::endl;
			return;
		}
		head = new DataType[maxsize]{};///每个元素初始化为DataType默认初始值
		this->maxsize = maxsize;
	}
	virtual ~Sequential_List() { List_Destroy(); }
public:///链表操作
	//销毁线性表
	void List_Destroy()
	{
		if (head)
		{
			delete[] head;
			head = nullptr;
			this->length = 0;
		}
	}
	//重置线性表所有元素为0
	void List_Clear()
	{
		try
		{
			if (!head)
				throw 1;
		}
		catch (...)
		{
			std::cout << "List is not exist" << std::endl;
			return;
		}
		memset(this->head, 0, maxsize * sizeof(DataType));
		this->length = 0;
	}
	//判断是否表空
	bool List_CheckEmpty() const { return length == 0; }
	//返回表长(元素个数)
	size_t List_GetLength() const { return length; }
	//返回第pos个元素的元素值
	DataType List_GetElement(size_t pos)
	{return head[Index(pos)];}
public:///元素操作
	//插入元素
	virtual void Element_Insert(size_t pos, DataType elem) = 0;
	//删除元素
	virtual DataType Element_Delete(size_t pos) = 0;
	//修改顺序表List第pos个位置上的元素为elem
	void Element_Update(int pos, DataType elem)
	{head[Index(pos)] = elem;}
public:
	//显示线性表所有信息
	virtual void List_Show(const char* string)
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:\n"
			<< " [" << this->length << '/' << maxsize << ']' << std::endl
			<< "Head->";
		for (int index = 0; index < maxsize; index++)
			std::cout << '[' << index << ':' << head[index] << "]-";
		std::cout << "End\n";
	}
};

template <typename DataType>
class Sequential_List_Array :public Sequential_List<DataType>
{
public:
	//Sequential_List_Array() 
	//	:Sequential_List<DataType>();
	//Sequential_List_Array(size_t maxsize) 
	//	:Sequential_List<DataType>(maxsize) {};
	Sequential_List_Array()
	{
		this->head = nullptr;
		this->length = 0;
		this->maxsize = 0;
	}
	Sequential_List_Array(size_t maxsize)
	{
		this->head = new DataType[maxsize]{};
		this->length = 0;
		this->maxsize = maxsize;
	}
	//~Sequential_List_Array(){};
public:
	void Element_Insert(size_t pos, DataType elem)
	{///n个元素有n+1个可插入位置,存储空间不足时不扩展并报错，位置pos非法时候抛出异常并终止插入元素
		try
		{
			if (pos<0 || pos>this->length + 1)
				throw std::exception("List insert failed: Position out of range");
			if (this->length>=this->maxsize)
				throw std::exception("List insert failed: List is full");
		}
		catch (const std::exception& exception)
		{
			std::cout << exception.what()<<std::endl;
			return;
		}

		if (this->length == 0)
			this->head[0] = elem;
		else
		{/// 从后往前，把当前索引向后搬
			for (size_t index = Index(this->length); Index(pos) <= index; index--)
				this->head[index + 1] = this->head[index];
			this->head[Index(pos)] = elem;
		}
		++this->length;
	}
	DataType Element_Delete(size_t pos)
	{
		DataType elem = this->head[Index(pos)];
		for (size_t i = Index(pos); i <= Index(this->length) - 1; i++)
			this->head[i] = this->head[i + 1];
		this->head[this->length - 1] = 0;///末尾补0
		--this->length;
		return elem;
	}
};


//template <typename DataType>
//class Sequential_List_Vector :public Sequential_List<DataType>
//{
//public:
//	Sequential_List_Vector()
//		:Sequential_List<DataType>();
//	Sequential_List_Vector(size_t maxsize)
//		:Sequential_List<DataType>(maxsize) {};
//private:
//	//以2倍为单位扩展收缩空间
//	void Expand()
//	{///重新申请2倍的空间，移动原有数据至该空间
//		if (this->head)
//		{
//			auto expand = new DataType[this->maxsize * 2]{};
//			memcpy(expand, this->head, sizeof(DataType) * this->maxsize);
//			this->List_Destroy();
//			this->head = expand;
//			this->maxsize *= 2;
//		}
//	}
//	void Shrink()
//	{
//		if (this->head)
//		{
//			auto shrink = new DataType[this->maxsize / 2]{};
//			memcpy(shrink, this->head, sizeof(DataType) * this->maxsize/2);
//			this->List_Destroy();
//			this->head = shrink;
//			this->maxsize /= 2;
//		}
//	}
//public:///元素操作
//	void Element_Insert(size_t pos, DataType elem)
//	{///n个元素有n+1个可插入位置,存储空间不足时扩展为两倍，位置pos非法时候抛出异常并终止插入元素
//		try
//		{
//			if (pos<0 || pos>this->length + 1)
//				throw 2;
//		}
//		catch (...)
//		{
//			std::cout << "List insert failed: Position out of range" << std::endl;
//			return;
//		}
//		if (length >= maxsize)
//			Expand();///空间扩展为2倍
//		if (this->length == 0)
//			head[0] = elem;
//		else
//		{/// 从后往前，把当前索引向后搬
//			for (size_t index = Index(this->length); Index(pos) <= index; index--)
//				head[index + 1] = head[index];
//			head[Index(pos)] = elem;
//		}
//		++this->length;
//	}
//	DataType Element_Delete(size_t pos)
//	{
//		DataType elem{ head[Index(pos)] };
//		for (size_t i = Index(pos); i <= Index(this->length) - 1; i++)
//			head[i] = head[i + 1];
//		head[this->length] = 0;
//		--this->length;
//		///元素个数<=1/2最大容量 时收缩空间
//		if (this->length <= this->maxsize / 2)
//			Shrink();
//		return elem;
//	}
//};
//






