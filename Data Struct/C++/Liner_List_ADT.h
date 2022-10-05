#pragma once


///线性表全局函数
//位置序号 转为 下标索引
static int Index(int num)
{
	return num - 1;
}

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
	/*			链表派生
	virtual NodeType* Element_Locate(int pos) = 0;
	virtual NodeType* Element_Prior(const NodeType* const node) = 0;
	virtual NodeType* Element_Next(const NodeType* const node) = 0;
	virtual void Element_Insert(int pos, DataType element) = 0;
	virtual DataType Element_Delete(int pos) = 0;
	*/
};
















