#pragma once



template <typename DataType>
class Liner_List
{///ADT 
	//初始化线性表
	virtual void List_Init(int maxsize) = 0;
	//销毁线性表
	virtual void List_Destroy() = 0;
	//清空线性表
	virtual void List_Clear() = 0;
	//判断是否表空
	virtual bool List_CheckEmpty() = 0;
	//返回表长(元素个数)
	virtual int List_GetLenghth() = 0;
	//返回第pos个元素的元素值
	virtual DataType List_GetElement(int pos) = 0;
	//显示线性表所有信息
	virtual void List_Show(const char* string) = 0;

	//插入元素
	virtual void Element_Insert(int pos, DataType elem) = 0;
	//删除元素
	virtual void Element_Delete(int pos, DataType& elem) = 0;

	/*
	//定位并返回元素值为element的元素
	virtual void Element_Locate() = 0;//链表
	//返回目标元素的前驱
	virtual void Element_Prior() = 0;//链表
	//返回目标元素的后继
	virtual void Element_Next() = 0;//链表
	*/
};
















