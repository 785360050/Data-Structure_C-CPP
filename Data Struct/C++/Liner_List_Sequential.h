#pragma once


//#include "Object.h"
#include "Liner_List_ADT.h"



template <typename DataType>
class Sequential_List:public Liner_List<DataType>
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
		List_Destroy();///释放空间
		maxsize *= 2;
		List_Init(maxsize);///申请2倍空间
		memcpy(head, temp, sizeof(DataType) * maxsize / 2);
	}
public:///表操作
	//初始化表头
	Sequential_List()
	{///用对象维护顺序表头节点，保存顺序表信息
		this->head = nullptr;
		this->length = 0;
		this->maxsize = 0;
	}
	//创建有maxsize个元素空间的顺序表，返回表首地址
	void List_Init(int maxsize) override
	{
		try
		{
			if (maxsize < 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "List Init Failed: maxsize must be greater than 1" << std::endl;
			return;
		}
		head = new DataType[maxsize];
		memset(this->head, 0, maxsize * sizeof(DataType));
		this->maxsize = maxsize;
	}
	//清空线性表(置0)
	void List_Clear() override
	{
		try
		{
			if (!head)
				throw 1;
		}
		catch (...)
		{
			std::cout << "List is not exist" << std::endl;
			return;
		}
		memset(this->head, 0, maxsize * sizeof(DataType));
		this->length = 0;
	}
	//判断是否表空
	bool List_CheckEmpty() override
	{
		if (length == 0)
			return true;
		return false;
	}
	//返回表长(元素个数)
	int List_GetLength() override
	{
		return length;
	}
	//返回第pos个元素的元素值
	DataType List_GetElement(int pos) override
	{
		return head[Index(pos)];
	}
	//显示顺序表List元素空间上的所有元素
	void List_Show(const char* string) override
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
	void List_Destroy() override
	{
		delete[] head;
	}
	///析构函数释默认自带delete this，所以不能再用delete this释放头节点
	//~Sequential_List()
	//{
	//	Delete this;
	//}
public:///元素操作
	//在顺序表的第pos个位置上插入数据元素elem
	void Element_Insert(int pos, DataType elem)
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
	//删除链表List第pos个位置上的元素，返回给元素elem
	DataType Element_Delete(int pos)
	{
		DataType elem = head[Index(pos)];
		for (int i = Index(pos); i <= Index(length) - 1; i++)
			head[i] = head[i + 1];
		head[length] = 0;
		length--;
		return elem;
	}
	//修改链表List第pos个位置上的元素为elem
	void Element_Update(int pos, DataType elem)
	{
		head[Index(pos)] = elem;
	}
};









