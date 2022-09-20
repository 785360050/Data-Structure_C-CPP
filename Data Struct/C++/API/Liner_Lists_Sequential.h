#pragma once


//#include "Object.h"

static int Index(int num)
{
	return num - 1;
}

template <typename DataType>
class Sequential_List//:public Liner_Structure
{
private:///头节点
	DataType* head;//元素值
	int length;	//当前表长
	int maxsize;//最大容量

private:
	//扩展空间为2倍
	void Expand()
	{///重新申请2倍的空间，移动原有数据至该空间
		DataType* temp = (DataType*)malloc(sizeof(DataType) * maxsize);
		if (temp)
			memcpy(temp, head, sizeof(DataType) * maxsize);
		Destory();///释放空间
		maxsize *= 2;
		Init(maxsize);///申请2倍空间
		memcpy(head, temp, sizeof(DataType) * maxsize/2);
	}
public:
	//初始化表头
	Sequential_List()
	{
		this->head = nullptr;
		this->length = 0;
		this->maxsize = 0;
	}
	//创建有maxsize个元素空间的顺序表，返回表首地址
	void Init(int maxsize)
	{
		head = new DataType[maxsize];
		memset(this->head, 0, maxsize * sizeof(DataType));
		this->maxsize = maxsize;
	}

	//在顺序表的第pos个位置上插入数据元素elem
	void InsertElement(int pos, DataType elem)
	{///n个元素有n+1个可插入位置,存储空间不足时扩展为两倍，位置pos非法时候抛出异常并终止插入元素
		try
		{
			if (pos<0 || pos>length + 1)
				throw 2;
		}
		catch (...)
		{
			std::cout << "List insert failed: Position out of range" << std::endl;
			return;
		}
		if (length >= maxsize)
			Expand();///空间扩展为2倍
		/// 从后往前，把当前索引向后搬
		for (int index = Index(length); Index(pos) <= index; index--)
			head[index + 1] = head[index];
		head[Index(pos)] = elem;
		length++;
	}
	//删除链表List第pos个位置上的元素，返回元素值
	DataType Delete(Sequential_List* List, int pos);
	//修改链表List第pos个位置上的元素为elem
	void Update(int pos, DataType elem)
	{
		head[Index(pos)] = elem;
	}
	//显示顺序表List元素空间上的所有元素
	void Show(const char* string)
	{
		std::cout << string << std::endl
			<< "[Length/Maxsize]:\n"
			<< " [" << length << '/' << maxsize << ']' << std::endl
			<< "Head->";
		for (int index = 0; index < maxsize; index++)
			std::cout << '[' << index << ':' << head[index] << "]-";
		std::cout << "End\n";
	}
	//销毁线性顺序表
	void Destory()
	{
		delete[] head;
	}
	///析构函数释默认自带delete this，所以不能再用delete this释放头节点
	//~Sequential_List()
	//{
	//	Delete this;
	//}
};






