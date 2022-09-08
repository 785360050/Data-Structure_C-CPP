#include <iostream>

#include "../API/Liner_Lists.h"


LinerLists_SequentialList<void*>::LinerLists_SequentialList(int maxsize)
{
	this->length = 0;
	this->MAXSIZE = maxsize;
	this->data=new 

	L->data = (DataType*)malloc(sizeof(DataType) * maxsize);
	memset(L->data, 0, sizeof(DataType) * maxsize);//ȫ��Ԫ�ؿռ��ʼ��Ϊ0
	L->length = 0;
	L->maxsize = maxsize;
	return L;
}

LinerLists_SequentialList<void*>::~LinerLists_SequentialList()
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


void LinerLists_SequentialList<void*>::Insert<void*>(SeqList* List, int pos, DataType data)
{
	try
	{
		if (List->length >= List->maxsize - 1)
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
	for (int i = List->maxsize - 1; pos <= i; i--)
	{
		List->data[i - 1] = List->data[i];
	}
	List->data[pos - 1] = data;
	List->length++;
}
//ɾ������List��pos��λ���ϵ�Ԫ�أ�����Ԫ��ֵ
DataType LinerLists_SequentialList<void*>::Delete(SeqList* List, int pos)
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
//�޸�����List��pos��λ���ϵ�Ԫ��ֵΪdata
void LinerLists_SequentialList<void*>::Update(SeqList* List, int pos, DataType data)
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
//��ʾ˳���ListԪ�ؿռ��ϵ�����Ԫ��
void LinerLists_SequentialList<void*>::Show(SeqList* List)
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
	for (int i = 0; i < List->maxsize; i++)
	{
		std::cout << List->data[i] << " ";
	}
	std::cout << std::endl;
}





