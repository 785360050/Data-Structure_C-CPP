#pragma once




//线性表
template <typename DataType>
class Liner_List
{///ADT 
public:///链表操作
	//初始化线性表空间
	virtual void List_Init(int maxsize) = 0;
	//销毁线性表
	virtual void List_Destroy() = 0;
	//重置线性表所有元素为0
	virtual void List_Clear() = 0;
	//判断是否表空
	virtual bool List_CheckEmpty() = 0;
	//返回表长(元素个数)
	virtual int List_GetLength() = 0;
	//返回第pos个元素的元素值
	virtual DataType List_GetElement(int pos) = 0;
public:///元素操作
	//插入元素
	virtual void Element_Insert(int pos, DataType elem) = 0;
	//删除元素
	virtual DataType Element_Delete(int pos) = 0;
public:
	//显示线性表所有信息
	virtual void List_Show(const char* string) = 0;
};
















