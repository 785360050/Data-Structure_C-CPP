#include <iostream>

//#include "../API/Object.h"
#include "../API/Liner_List_Sequential_CPP.h"


///位置序号 转为 下标索引
static int Index(int num)
{
	return num - 1;
}

template<typename DataType>
void Sequential_List<DataType>::Expand()
{///重新申请2倍的空间，移动原有数据至该空间
	DataType* temp = (DataType*)malloc(sizeof(DataType) * maxsize);
	if (temp)
		memcpy(temp, head, sizeof(DataType) * maxsize);
	List_Destroy();///释放空间
	maxsize *= 2;
	List_Init(maxsize);///申请2倍空间
	memcpy(head, temp, sizeof(DataType) * maxsize / 2);
}

template<typename DataType>
Sequential_List<DataType>::Sequential_List()
{///用对象维护顺序表头节点，保存顺序表信息
	this->head = nullptr;
	this->length = 0;
	this->maxsize = 0;
}

template<typename DataType>
void Sequential_List<DataType>::List_Init(int maxsize)
{
	head = new DataType[maxsize];
	memset(this->head, 0, maxsize * sizeof(DataType));
	this->maxsize = maxsize;
}

template<typename DataType>
void Sequential_List<DataType>::List_Clear()
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

template<typename DataType>
bool Sequential_List<DataType>::List_CheckEmpty()
{
	if (length == 0)
		return true;
	return false;
}

template<typename DataType>
int Sequential_List<DataType>::List_GetLenghth()
{
	return length;
}

template<typename DataType>
DataType Sequential_List<DataType>::List_GetElement(int pos)
{
	return head[pos];
}

template<typename DataType>
void Sequential_List<DataType>::Element_Insert(int pos, DataType elem)
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

template<typename DataType>
void Sequential_List<DataType>::Element_Delete(int pos, DataType& elem)
{
	elem = head[Index(pos)];
	for (int i = Index(pos); i <= Index(length) - 1; i++)
		head[i] = head[i + 1];
	head[length] = 0;
	length--;
}

template<typename DataType>
void Sequential_List<DataType>::Element_Update(int pos, DataType elem)
{
	head[Index(pos)] = elem;
}

template<typename DataType>
void Sequential_List<DataType>::List_Show(const char* string)
{
	std::cout << string << std::endl
		<< "[Length/Maxsize]:\n"
		<< " [" << length << '/' << maxsize << ']' << std::endl
		<< "Head->";
	for (int index = 0; index < maxsize; index++)
		std::cout << '[' << index << ':' << head[index] << "]-";
	std::cout << "End\n";
}

template<typename DataType>
void Sequential_List<DataType>::List_Destroy()
{
	delete[] head;
}



