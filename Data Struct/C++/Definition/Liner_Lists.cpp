#include <iostream>

#include "../API/Object.h"
#include "../API/Liner_Lists.h"

///静态顺序空间，不扩容
template<typename DataType>
SeqList<DataType>::SeqList(int maxsize)
{
	SeqList* L = new SeqList;
	L->element = new DataType[maxsize * sizeof(DataType)];///new 的单位不确定，是否为字节
	L->length = 0;
	L->size = maxsize;
	return L;
}

template<typename DataType>
SeqList<DataType>::~SeqList()
{
	try
	{
		if (!this)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Delete Failed: List is not exist" << std::endl;
		exit(0);
	}
	Delete;
}

template<typename DataType>
void SeqList<DataType>::InsertElement(SeqList* List, int pos, DataType elem)
{

}


template<typename DataType>
DataType SeqList<DataType>::Delete(SeqList* List, int pos);

template<typename DataType>
void SeqList<DataType>::Update(SeqList* List, int pos, DataType elem);

template<typename DataType>
void SeqList<DataType>::Show(SeqList* List);

