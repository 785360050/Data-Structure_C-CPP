#pragma once
#include "Object.h"


template <typename DataType>
class SeqList:public Liner_Structure
{
public:
	//创建有maxsize个元素空间的顺序表，返回表首地址
	//所有元素值初始化为0
	SeqList();
	//在顺序表List的第pos个位置上插入数据元素data
	void InsertElement(SeqList* List, int pos, DataType elem);
	//删除链表List第pos个位置上的元素，返回元素值
	DataType Delete(SeqList* List, int pos);
	//修改链表List第pos个位置上的元素值为data
	void Update(SeqList* List, int pos, DataType elem);
	//显示顺序表List元素空间上的所有元素
	void Show(SeqList* List);
	//销毁线性顺序表
	~SeqList();

private:
	int* element;//元素值
	int length;	//当前表长
	int maxsize;//最大容量
};





void test()
{
	SeqList<int> a;
	a.
}


