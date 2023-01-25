#pragma once

#include <iostream>

#include "MergeFindSet_ADT.h"

template <typename DataType>
struct MergeFindSet_QuickFind:public Tree_MergeFindSet<DataType>
{
private:
	DataType* group_id;//集合中元素对应的组ID

public:
	MergeFindSet_QuickFind(int maxsize)
		:Tree_MergeFindSet<DataType>(maxsize), group_id{ new int[maxsize] {} } {};
	MergeFindSet_QuickFind(int* element_array, int maxsize)
		:Tree_MergeFindSet<DataType>(element_array, maxsize)
	{///group_id初始group_id为自己
		group_id = new int[maxsize] {};
		memcpy(group_id, element_array, sizeof(DataType) * maxsize);
	}

	~MergeFindSet_QuickFind()
	{
		if (group_id)
			delete[] group_id;
		std::cout << "MergeFindSet_QuickFind Destroyed" << std::endl;
	}
private:
	//获取元素对应的索引(组ID)
	int Index(DataType x)
	{
		for (int i = 0; i < this->count; ++i)
			if (this->element[i] == x)
				return i;
		return -1;///找不到则返回失败
	}
public:
	//获取元素对应的索引(组ID)
	bool Find(DataType x, DataType y) override
	{
		int Index_X = Index(x);
		int Index_Y = Index(y);
		if (Index_X == -1 || Index_Y == -1)
			return false;//任意查找索引失败返回失败
		return (group_id[Index_X] == group_id[Index_Y]) ? true : false;
	}

	void Merge(DataType x, DataType y) override
	{
		int Index_X = Index(x);
		int Index_Y = Index(y);
		int ID_X = group_id[Index_X];
		int ID_Y = group_id[Index_Y];
		for (int i = 0; i < this->count; ++i)
		{
			if (group_id[i] == ID_X)///遍历寻找x的组ID，设置为Y的组ID，完成合并
				group_id[i] = ID_Y;
		} 

	}

	void Show() override
	{
		std::cout << "[data : group_id]" << std::endl;
		for (int i = 0; i < this->count; i++)
			std::cout << '[' << this->element[i] << ':' << group_id[i] << "],";
		std::cout << std::endl;
	}
};




