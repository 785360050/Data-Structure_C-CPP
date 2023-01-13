#pragma once

#include "string"
using std::string;

//线性表
template <typename DataType>
class Liner_List
{///ADT 
protected:
	virtual ~Liner_List() {} = default;
public:///链表操作
	//重置线性表所有元素
	virtual void List_Clear() = 0;
	//判断是否表空
	virtual bool List_CheckEmpty() const = 0;
	//返回表长(元素个数)
	virtual int List_GetLength() const = 0;
	//返回第pos个元素的元素值
	virtual DataType List_GetElement(int pos) const = 0;
public:///元素操作
	//插入元素
	virtual void Element_Insert(int pos, DataType elem) = 0;
	//删除元素
	virtual DataType Element_Delete(int pos) = 0;
	//更新元素
	virtual void Element_Update(size_t pos, DataType elem) = 0;
public:
	//显示线性表所有信息
	virtual void List_Show( string) = 0;
};
















