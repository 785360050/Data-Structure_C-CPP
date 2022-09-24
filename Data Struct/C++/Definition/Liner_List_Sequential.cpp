#include <iostream>

//#include "../API/Object.h"
#include "../API/Liner_List_Sequential.h"



template<typename DataType>
Sequential_List<DataType>::Sequential_List()
{
	this->head = nullptr;
	this->length = 0;
	this->maxsize = 0;
}


///静态顺序空间，不扩容

template<typename DataType>
void Sequential_List<DataType>::Init(int maxsize)
{
	this->head = new DataType[maxsize];
}



template<typename DataType>
void Sequential_List<DataType>::Destory()
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
void Sequential_List<DataType>::InsertElement(Sequential_List* List, int pos, DataType elem)
{
	
}


template<typename DataType>
DataType Sequential_List<DataType>::Delete(Sequential_List* List, int pos);

template<typename DataType>
void Sequential_List<DataType>::Update(Sequential_List* List, int pos, DataType elem);

template<typename DataType>
void Sequential_List<DataType>::Show(Sequential_List* List);

