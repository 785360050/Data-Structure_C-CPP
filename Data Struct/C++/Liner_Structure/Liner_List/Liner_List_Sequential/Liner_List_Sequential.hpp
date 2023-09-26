#pragma once


//#include "Object.h"
#include "../Liner_List.hpp"
#include <iostream>
#include <cstring> //memcpy



template <typename DataType>
class Sequential_List:public Liner_List<DataType,DataType>
{
protected:
	size_t maxsize;		///当前最大容量
public:
	//初始化表头
	Sequential_List() :Liner_List<DataType,DataType>(), maxsize{0} {};
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
		this->front = new DataType[maxsize]{};///每个元素初始化为DataType默认初始值
		this->maxsize = maxsize;
	}
	~Sequential_List()
	{
		if (this->front)
		{
			delete[] this->front;
			this->front = nullptr;
			this->length = 0;
		}
	}
protected:
	/// @param pos 位序从1开始
	size_t Index(size_t pos) const
	{///位序转元素索引
		if (pos == 0)
			throw std::underflow_error("size_t pos == 0");
		return --pos;
	}
public:///链表操作
	void List_Clear() override
	{
		try
		{
			if (!this->front)
				throw 1;
		}
		catch (...)
		{
			std::cout << "List is not exist" << std::endl;
			return;
		}
		memset(this->front, 0, maxsize * sizeof(DataType));
		this->length = 0;
	}
	//返回当前最大容量
	size_t List_Get_Maxsize() const { return maxsize; }
	//返回第pos个元素的元素值
	DataType List_GetData(size_t pos) override
	{return this->front[this->Index(pos)];}
public:///元素操作
	DataType* Element_Locate(size_t pos) override
	{///返回指针
		return &(this->front[this->Index(pos)]);
	}
	//插入元素
	virtual void Element_Insert(size_t pos, DataType elem) = 0;
	//删除元素
	virtual DataType Element_Delete(size_t pos) = 0;
	//修改顺序表List第pos个位置上的元素为elem
	void Element_Update(size_t pos, DataType elem) override
	{this->front[this->Index(pos)] = elem;}
public:
	//显示线性表所有信息
	virtual void List_Show(const string& string)
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:\n"
			<< " [" << this->length << '/' << maxsize << ']' << std::endl
			<< "Front->";
		for (int index = 0; index < maxsize; index++)
			std::cout << '[' << index << ':' << this->front[index] << "]-";
		std::cout << "End\n";
	}
};

/// 静态数组
template <typename DataType>
class Sequential_List_Array :public Sequential_List<DataType>
{
public:
	Sequential_List_Array() 
		:Sequential_List<DataType>() {};
	Sequential_List_Array(size_t maxsize) 
		:Sequential_List<DataType>(maxsize) {};
	
public:
	void Element_Insert(size_t pos, DataType elem)
	{///n个元素有n+1个可插入位置,存储空间不足时不扩展并报错，位置pos非法时候抛出异常并终止插入元素
		if (pos < 0 || pos > this->length + 1)
			throw std::out_of_range("List insert failed: Position out of range");
		if (this->length >= this->maxsize)
			throw std::runtime_error("List insert failed: List is full");

		if (this->length == 0)
			this->front[0] = elem;
		else
		{/// 从后往前，把当前索引向后搬
			for (size_t index = this->Index(this->length); this->Index(pos) <= index; index--)
				this->front[index + 1] = this->front[index];
			this->front[this->Index(pos)] = elem;
		}
		++this->length;
	}
	DataType Element_Delete(size_t pos)
	{
		DataType elem = this->front[this->Index(pos)];
		for (size_t i = this->Index(pos); i <= this->Index(this->length) - 1; i++)
			this->front[i] = this->front[i + 1];
		this->front[this->length - 1] = 0;///末尾补0
		--this->length;
		return elem;
	}
};

/// 动态数组
template <typename DataType>
class Sequential_List_Vector :public Sequential_List<DataType>
{
public:
	Sequential_List_Vector()
		:Sequential_List<DataType>() {};
	Sequential_List_Vector(size_t maxsize)
		:Sequential_List<DataType>(maxsize) {};
	
protected:
	//以2倍为单位扩展收缩空间
	void Expand()
	{///重新申请2倍的空间，移动原有数据至该空间
		if (this->front)
		{
			auto expand = new DataType[this->maxsize * 2]{};
			memcpy(expand, this->front, sizeof(DataType) * this->maxsize);
			delete[] this->front;
			this->front = expand;
			this->maxsize *= 2;
		}
	}
	void Shrink()
	{
		if (this->front)
		{
			auto shrink = new DataType[this->maxsize / 2]{};
			memcpy(shrink, this->front, sizeof(DataType) * this->length);
			delete[] this->front;
			this->front = shrink;
			this->maxsize /= 2;
		}
	}
public:///元素操作
	void Element_Insert(size_t pos, DataType elem)
	{///n个元素有n+1个可插入位置,存储空间不足时扩展为两倍，位置pos非法时候抛出异常并终止插入元素
		try
		{
			if (pos<0 || pos>this->length + 1)
				throw 2;
		}
		catch (...)
		{
			std::cout << "List insert failed: Position out of range" << std::endl;
			return;
		}
		if (this->length >= this->maxsize)
			Expand();///空间扩展为2倍
		//this->List_Show(" ");
		if (this->length == 0)
			this->front[0] = elem;
		else
		{/// 从后往前，把当前索引向后搬
			for (size_t index = this->Index(this->length); this->Index(pos) <= index; index--)
				this->front[index + 1] = this->front[index];
			this->front[this->Index(pos)] = elem;
		}
		++this->length;
	}
	DataType Element_Delete(size_t pos)
	{
		DataType elem{ this->front[this->Index(pos)] };
		for (size_t i = this->Index(pos); i <= this->Index(this->length) - 1; i++)
			this->front[i] = this->front[i + 1];
		this->front[this->length - 1] = 0;
		--this->length;
		///元素个数<=1/2最大容量 时收缩空间
		if (this->length <= this->maxsize / 2)
			Shrink();
		return elem;
	}
};







