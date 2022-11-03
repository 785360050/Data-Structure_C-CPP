#include <iostream>
#include <stdlib.h>
#include "../API/Liner_List_Sequential.h"

SeqList* SeqList_Init(int maxsize)
{
	SeqList* L = new SeqList;
	L->data = (DataType* )malloc(sizeof(DataType) * maxsize);
	memset(L->data, 0, sizeof(DataType) * maxsize);//全部元素空间初始化为0
	L->length = 0;
	L->maxsize = maxsize;
	return L;
}

void SeqList_Destroy(SeqList* List)
{
	try
	{
		if (!List)
		{
			throw 1;
		}
	}
	catch (...)
	{
		std::cout << "List Unexist" << std::endl;
		exit(0);
	}
	if (List->data)
	{
		free(List->data);
	}
	free(List);

}

void SeqList_Insert(SeqList* List, int pos, DataType data)
{
	try
	{
		if (List->length >= List->maxsize-1)
		{
			throw 1;
		}
	}
	catch (...)
	{
		std::cout << "List insert failed: SeqList is Full" << std::endl;
		exit(0);
	}
	DataType* p = &(List->data[List->maxsize]);
	for (int i =List->maxsize-1;pos<=i;i--)
	{
		List->data[i-1] = List->data[i];
	}
	List->data[pos-1] = data;
	List->length++;
}

DataType SeqList_Delete(SeqList* List, int pos)
{
	try
	{
		if (pos<1||pos>=List->maxsize)
		{
			throw 1;
		}
		if (!List->data)
			throw 2;
	}
	catch (...)
	{
		std::cout << "Delete failed: invalid position" << std::endl;
		exit(0);
	}
	DataType x = List->data[pos - 1];
	for (int i = pos - 1; i < List->length; i++)
	{
		List->data[i] = List->data[i + 1];
	}
	List->length--;
	return x;
}

void SeqList_Update(SeqList* List, int pos, DataType data)
{
	try
	{
		if (pos < 1 || pos >= List->maxsize)
		{
			throw 1;
		}
		if (!List->data)
			throw 2;
	}
	catch (...)
	{
		std::cout << "Update failed: invalid position" << std::endl;
		exit(0);
	}
	List->data[pos - 1] = data;
}

int SeqList_Element_Locate(SeqList* List, DataType data)
{
	try
	{
		if (List->length == 0)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Search Failed: List is not exist" << std::endl;
		return NULL;
	}
	int index = 0;
	while (List->data[index] != data && index < List->maxsize)
		index++;
	return index;
}

void SeqList_Show(SeqList* List)
{
	try
	{
		if (!List)
			throw 1;
		if (!List->data)
			throw 2;
	}
	catch (...)
	{
		std::cout << "List(->data) Unexist" << std::endl;
		exit(0);
	}
	for (int i =0;i<List->maxsize;i++)
	{
		std::cout << List->data[i] << " ";
	}
	std::cout << std::endl;

}


//SeqList* InitialList(int x)	//创建并初始化有x个元素的线性顺序表，返回表首地址
//{
//	SeqList* L = (SeqList*)malloc(sizeof(SeqList));
//	L->data = (DataType*)malloc(sizeof(DataType)*x);
//	memset(L->data, 0, sizeof(DataType) * x);
//	L->length = 0;
//	L->maxsize = x;
//	return L;
//}
//
//void ListDestroy(SeqList* L)	//销毁线性顺序表
//{
//	if (L)
//	{
//		if (L->data)
//		{
//			free(L->data);
//			L->data = NULL;
//		}
//		free(L);
//	}
//}
//
//void ListInsert(SeqList* L, int p, DataType e)		//在线性顺序表L第p个位置插入元素e
//{
//	if (p > L->length || p < 0)
//	{
//		std::cout << "Invailad postition";
//		return;
//	}
//	if (L->length == L->maxsize-1)
//	{
//		DataType* temp = L->data;
//		L->data = (DataType*)malloc(sizeof(L->maxsize) * 2);
//		memset(L->data, 0, sizeof(DataType) * L->maxsize);
//		memcpy( L->data , temp , sizeof(DataType) * L->length);
//		L->maxsize *= 2;
//		free(temp);
//	}
//
//	for (int i = L->length - 1; p-1<=i; i--)
//	{
//		L->data[i + 1] = L->data[i];
//	}
//	L->data[p-1] = e;
//	L->length++;
//}
//
//void ListShow(const SeqList* L)
//{
//	int n = L->length-1;
//	std::cout << "L->";
//	for (int i = 0; i < n; i++)
//	{
//		std::cout << L->data[i] << "-";
//	}
//	std::cout << "NULL" << std::endl << "ListLenth：" << L->length << std::endl;
//}




