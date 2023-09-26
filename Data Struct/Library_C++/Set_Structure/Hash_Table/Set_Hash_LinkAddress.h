#pragma once


#include <iostream>
template <typename DataType>
struct HashNode
{
	DataType key;
	void* data;
	HashNode<DataType>* next;
public:
	HashNode(int key=NULL)
		:key{ key }, data{ nullptr }, next{ nullptr } {};
};


//链地址法解决冲突
template <typename DataType>
struct HashList_Link
{
private:
	HashNode<DataType>* data;
	int length;//记录哈希表长度
	int count;//记录元素个数
	
public:
	HashList_Link(int maxsize)
		:length{ maxsize }, count{ 0 }, data{ new HashNode<DataType>[maxsize] } {};
	~HashList_Link()
	{
		HashNode<DataType>* n;
		for (int i = 0; i < length; i++)
		{
			while (data[i].next)
			{
				n = data[i].next;
				data[i].next = n->next;
				delete n;
			}
		}
		delete[] data;
	}

private:
	//链地址法解决冲突
	//本质为头插哈希节点
	//哈希函数：除留余数法
	int HashFunction_Remain(int size, int key) const
	{
		return key % size;
	}

	void CollisionFuction_OpenAddressing_LinkAddress(int index, int key)
	{
		HashNode<DataType>* n = new HashNode<DataType>(key);
		n->next = data[index].next;
		data[index].next = n;
	}

public:
	void HashList_Insert(int key)
	{
		int index = HashFunction_Remain(length,key);///
		if (data[index].key == NULL)
			data[index].key = key;
		else
			CollisionFuction_OpenAddressing_LinkAddress(index, key);
		count++;
	}

	int HashList_Locate(int key)
	{
		int index = HashFunction_Remain(length, key);
		int t = 1;
		HashNode<DataType>* n;
		if (data[index].key != key)
		{
			n = data[index].next;
			while (n && n->key != key)
				n = n->next;
			return (n && n->key == key) ? index : NULL;
		}
		else
			return NULL;
	}

	void HashList_Show()
	{
		HashNode<DataType>* n;
		std::cout
			<< "Length:" << length << std::endl
			<< "Count:" << count << std::endl
			<< "[Index:Key]->[HashNode...]" << std::endl;
		for (int i = 0; i < length; i++)
		{
			std::cout << i << ':' << data[i].key << "->";
			n = data[i].next;
			while (n)
			{
				std::cout << n->key << "->";
				n = n->next;
			}
			std::cout << "NULL" << std::endl;
		}
		std::cout << std::endl;
	}
};





