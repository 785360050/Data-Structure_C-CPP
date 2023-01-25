#pragma once

#include <iostream>

/*
* ///2种实现
1.Quick Find		利用顺序存储实现
	查找效率：O(1)
	合并效率：O(N)
2.Quick Union		利用链式存储实现
	查找效率：O(logN)
	合并效率：O(logN)
*/

template <typename DataType>
struct Tree_MergeFindSet
{
protected:
	DataType* element;//元素集合
	int count;//集合中元素个数

public:
	Tree_MergeFindSet() :element{ nullptr }, count(0) {};
	Tree_MergeFindSet(int maxsize) 
		:element{ new DataType[maxsize]{} }, count(0) {};
	Tree_MergeFindSet(int* element_array,int maxsize)
		:element{ element_array }, count(maxsize) {};
	virtual ~Tree_MergeFindSet()
	{
		if (element)
			delete[] element;
		std::cout << "MergeFindSet Destroyed" << std::endl;
	}
public:
	//判断查并集set中，元素x,y是否再同一个集合中
	virtual bool Find(DataType x, DataType y)=0;
	//合并查并集set中元素x,y到同一集合中(x加入y的组)
	virtual void Merge(DataType x, DataType y)=0;
	//显示整个查并集
	virtual void Show()=0;
};







