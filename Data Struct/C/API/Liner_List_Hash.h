#pragma once

#include <iostream>






struct HashList
{
	int* data;
	int length;
	int maxsize;
};


void HashList_Init(HashList* list, int maxsize)
{
	list->length = 0;
	list->maxsize = maxsize;
	list->data = new int[maxsize];
	memset(list->data, NULL, sizeof(int) * maxsize);
}

//哈希函数：除留余数法
int HashFunction_Remain(int size,int key)
{
	return key % size;
}

//冲突函数：开放定址法-线性探测法
int CollisionFuction_OpenAddressing_LinerProbing(HashList* list, int index, int key)
{
	return (index + 1)%list->maxsize;
}

void HashList_Insert(HashList* list, int key)
{
	try
	{
		if (list->length >= list->maxsize)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Insert Failed: Hash List is Full" << std::endl;
		return;
	}
	int index = HashFunction_Remain(list->maxsize, key);
	while (list->data[index] != NULL)
	{
		index = CollisionFuction_OpenAddressing_LinerProbing(list, index, key);
	}
	list->data[index] = key;
	list->length++;
}

void HashList_Destroy(HashList* list)
{
	delete[] list->data;
	delete list;
}

void HashList_Show(const HashList* const list)
{
	try
	{
		if (!list)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Hash List is not exist" << std::endl;
		return;
	}
	std::cout
		<< "Length:" << list->length << std::endl
		<< "Maxsize:" << list->maxsize << std::endl;
	for (int i = 0; i < list->maxsize; i++)
		std::cout << list->data[i] << ' ';
	std::cout << std::endl;
}

