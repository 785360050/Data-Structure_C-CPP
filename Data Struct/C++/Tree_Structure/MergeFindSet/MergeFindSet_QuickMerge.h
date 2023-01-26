#pragma once

#include <iostream>
#include <stack>
#include "../../Liner_Structure/Liner_Stack/Liner_Stack_ADT.h"
#include "../../Liner_Structure/Liner_Stack/Liner_Stack_Linked/Liner_Stack_Linked.h"

#include "MergeFindSet_ADT.h"

//#define Standard_Stack
#define Individual_Stack


template <typename DataType>
class MergeFindSet_QuickMerge :public Tree_MergeFindSet<DataType>
{
private:
	int* parents;	//存放双亲的ID
	int* size;		//记录所在集合的元素总数(包含的子节点个数，仅在根节点合并时使用)
public:
	MergeFindSet_QuickMerge(int maxsize)
		:Tree_MergeFindSet<DataType>(maxsize), parents{ new int[maxsize] {} }, size{ new int[maxsize] {} } {};
	//元素对应双亲的索引存放在parents数组中
	//(初始双亲为自己，即根ID=双亲ID=元素数组下标)
	MergeFindSet_QuickMerge(int* element_array, int maxsize)	
		:Tree_MergeFindSet<DataType>(element_array, maxsize), parents{ new int[maxsize] {} }, size{ new int[maxsize] {} }
	{
		memcpy(parents, element_array, sizeof(int) * maxsize);
		memcpy(size, element_array, sizeof(int) * maxsize);
	}

	~MergeFindSet_QuickMerge()
	{
		if (parents)
			delete[] parents;
		if (size)
			delete[] size;
		std::cout << "MergeFindSet_QuickMerge Destroyed" << std::endl;
	}
private:
	//寻找元素值为data的元素的下标索引
	int Index(DataType data)
	{///遍历找值为data的元素，返回该元素下标
		/// <summary>
		/// 循环遍历寻找值为data的元素的双亲parents,
		/// 直到找到双亲ID==自己ID的节点，即为data元素所在集合的RootID
		/// 返回根节点ID，失败返回-1
		/// </summary>
		/// <param name="set"></param>
		/// <param name="data"></param>
		/// <returns></returns>
		for (int i = 0; i < this->count; ++i)
		{
			if (this->element[i] == data)
				return i;
		}
		return -1;
	}

	//遍历寻找元素data所在的集合(根)ID
	int RootIndex(DataType data)
	{
		int temp = Index(data);
		if (temp == -1)
			return -1;
		///找根(双亲为自己即为根)
		while (parents[temp] != temp)
			temp = parents[temp];//向上移动
		return temp;//返回根ID
	}
	//遍历寻找元素data所在的集合(根)ID(路径压缩)
	int RootIndex_Optimized( DataType data)
	{///利用栈实现路径压缩
		int temp = Index(data);
		if (temp == -1)
			return -1;
#ifdef Standard_Stack
		std::stack<DataType> path;
		while (parents[temp] != temp)
		{
			path.push(temp);//将路径的下标索引入栈
			temp = parents[temp];
		}
		while (!path.empty())
		{
			int pos = path.top(); path.pop();
			parents[pos] = temp;
		}
#endif // Standard_Stack
#ifdef Individual_Stack
		Link_Stack<int> path(10);
		while (parents[temp] != temp)
		{
			path->Element_Push(temp);//将路径的下标索引入栈
			temp = parents[temp];
		}
		while (!path->Stack_CheckEmpty())
		{
			int pos = path->Stack_GetTop(); path->Element_Pop();
			parents[pos] = temp;
		}
#endif // Individual_Stack
		return temp;
	}

public:
	bool Find(DataType x, DataType y) override
	{
		int RootID_X = RootIndex(x);
		int RootID_Y = RootIndex(y);
		try
		{
			if (RootID_X == -1 || RootID_Y == -1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "查找失败，元素所在集合的RootID不存在" << std::endl;
			return false;
		}
		return (RootID_X == RootID_Y) ? true : false;	///所在集合的根ID一致时返回true
	}

	void Merge(DataType x, DataType y) override
	{
		/// <summary>
		/// 通过修改集合的RootID的合并两个元素
		/// 将数量小的集合的根元素的parent修改为数量多的集合的根的下标
		/// </summary>
		/// <param name="set"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		int RootID_X = RootIndex(x);
		int RootID_Y = RootIndex(y);
		if (RootID_X == -1 || RootID_Y == -1)
		{
			std::cout << "合并失败" << std::endl;
			return;
		}
		if (RootID_X != RootID_Y)
		{///不在同一个集合时才合并
			int Size_X = size[RootID_X];
			int Size_Y = size[RootID_Y];
			if (Size_X >= Size_Y)
			{///元素少的集合合并到大的集合
				parents[RootID_Y] = RootID_X;//小的集合的根节点双亲改为大集合的根节点下标
				size[RootID_X] += Size_Y;//更新大的集合子节点个数
			}
			else
			{
				parents[RootID_X] = RootID_Y;
				size[RootID_Y] += Size_X;
			}
		}
	}

	void Show() override
	{
		std::cout << "[Element data : Parent ID : Group Size]" << std::endl;
		for (int i = 0; i < this->count; i++)
		{
			std::cout << '['
				<< this->element[i] << ':'
				<< parents[i] << ':'
				<< size[i] << "],";
		}
		std::cout << std::endl;
	}

};




