#pragma once


//#include "Object.h"



template <typename DataType>
class Sequential_List//:public Liner_Structure
{
public:
	///初始化表头
	Sequential_List()
	{
		this->head = nullptr;
		this->length = 0;
		this->maxsize = 0;
	}
	///创建有maxsize个元素空间的顺序表，返回表首地址
	void Init(int maxsize)
	{
		head = new DataType[maxsize];
		memset(this->head, -1, maxsize * sizeof(DataType));
		this->maxsize = maxsize;
	}
	
	//在顺序表List的第pos个位置上插入数据元素data
	void InsertElement(Sequential_List* List, int pos, DataType elem);
	//删除链表List第pos个位置上的元素，返回元素值
	DataType Delete(Sequential_List* List, int pos);
	//修改链表List第pos个位置上的元素值为data
	void Update(Sequential_List* List, int pos, DataType elem);
	//显示顺序表List元素空间上的所有元素
	void Show()
	{
		std::cout 
			<< "Length: " << length <<std::endl
			<< "Maxsize: " << maxsize << std::endl;
		for (int i = 0; i < maxsize; i++)
			std::cout << head[i] << " ";
	}
	//销毁线性顺序表
	void Destory()
	{
		delete[] this->head;
	}
	///析构函数释默认自带delete this，所以不能再用delete this释放头节点
	//~Sequential_List()
	//{
	//	Delete this;
	//}

private:
	DataType* head;//元素值
	int length;	//当前表长
	int maxsize;//最大容量
};






