#pragma once

#include <string>
using std::string;


//线性表
template <typename ElementType,typename DataType>
class Liner_List
{///ADT 
public:
	virtual ~Liner_List() = default;
public:///链表操作
	//销毁线性表
	virtual void List_Destroy() = 0;
	//重置线性表所有元素为0
	virtual void List_Clear() = 0;
	//判断是否表空
	virtual bool List_CheckEmpty() const = 0;
	//返回表长(元素个数)
	virtual size_t List_GetLength() const = 0;
	//返回第pos个元素的元素值
	virtual DataType List_GetElement(size_t pos) = 0;
public:///元素操作
	//插入元素
	virtual void Element_Insert(size_t pos, DataType elem) = 0;
	//删除元素
	virtual DataType Element_Delete(size_t pos) = 0;
	//更新元素
	virtual void Element_Update(size_t pos, DataType elem) = 0;
public:
	//显示线性表所有信息
	virtual void List_Show(const string& string) = 0;
};
















