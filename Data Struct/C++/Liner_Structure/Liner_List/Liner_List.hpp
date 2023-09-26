#pragma once

#include <iostream>
#include "Liner_List_ADT.h"

template <typename ElementType, typename DataType>
class Liner_List :public Liner_List_ADT<ElementType, DataType>
{
protected:
	ElementType* front;		///指向存储结构
	size_t length = 0;	///当前元素个数
public:
	Liner_List() :front{ nullptr }, length{ 0 } {};
	virtual ~Liner_List() = default;

public:///表操作
	//清空所有元素
	virtual void List_Clear() = 0;
	//判断是否表空
	bool List_CheckEmpty() const { return length == 0; }
	//返回当前表长(元素个数)
	size_t List_GetLength() const { return length; }
	//返回第pos个元素的元素值
	virtual DataType List_GetData(size_t pos) = 0;

public:///元素操作
	virtual ElementType* Element_Locate(size_t pos) = 0;
	//插入元素
	virtual void Element_Insert(size_t pos, DataType elem) = 0;
	//删除元素
	virtual DataType Element_Delete(size_t pos) = 0;
	//更新元素
	virtual void Element_Update(size_t pos, DataType elem) = 0;
public:
	//显示线性表所有信息
	virtual void List_Show(const string& string = "") = 0;
};