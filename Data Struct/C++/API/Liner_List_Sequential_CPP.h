#pragma once


//#include "Object.h"
#include "Liner_List_ADT.h"

//序号转为下标索引
static int Index(int num);


template <typename DataType>
class Sequential_List:public Liner_List<DataType>
{
private:///头节点
	DataType* head;//元素值
	int length;	//当前表长
	int maxsize;//最大容量

private:
	//扩展空间为2倍
	void Expand();
public:///表操作
	//初始化表头
	Sequential_List();
	//创建有maxsize个元素空间的顺序表，返回表首地址
	void List_Init(int maxsize) override;
	//清空线性表
	void List_Clear() override;
	//判断是否表空
	bool List_CheckEmpty() override;
	//返回表长(元素个数)
	int List_GetLenghth() override;
	//返回第pos个元素的元素值
	DataType List_GetElement(int pos) override;
	//显示顺序表List元素空间上的所有元素
	void List_Show(const char* string) override;
	//销毁线性顺序表
	void List_Destroy() override;
	///析构函数释默认自带delete this，所以不能再用delete this释放头节点
	//~Sequential_List()
	//{
	//	Delete this;
	//}
public:///元素操作
	//在顺序表的第pos个位置上插入数据元素elem
	void Element_Insert(int pos, DataType elem);
	//删除链表List第pos个位置上的元素，返回给元素elem
	void Element_Delete(int pos, DataType& elem);
	//修改链表List第pos个位置上的元素为elem
	void Element_Update(int pos, DataType elem);
};












