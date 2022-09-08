#pragma once

template <class DataType>
class LinerLists_SequentialList
{
public:
	//创建有maxsize个元素空间的顺序表，返回表首地址
	//所有元素值初始化为0
	LinerLists_SequentialList();
	//在顺序表List的第pos个位置上插入数据元素data
	void Insert(SeqList* List, int pos, DataType data);
	//删除链表List第pos个位置上的元素，返回元素值
	DataType Delete(SeqList* List, int pos);
	//修改链表List第pos个位置上的元素值为data
	void Update(SeqList* List, int pos, DataType data);
	//显示顺序表List元素空间上的所有元素
	void Show(SeqList* List);
	//销毁线性顺序表
	~LinerLists_SequentialList();

	int* data;	//元素值
	int length;	//当前表长
	int MAXSIZE;//最大容量
};


typedef LinerLists_SequentialList<void*> SeqList;//类模板重命名



void test()
{
	LinerLists_SequentialList<int> a;
	a.data
}