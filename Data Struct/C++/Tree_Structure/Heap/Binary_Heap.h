#pragma once

#include <iostream>
//enum direction { left = 1, right = 2 };


/// <summary>
/// https://www.cnblogs.com/sybil-hxl/p/15088324.html
/// 二叉堆父子下标关系推导(0开始)
/// </summary>
/// <typeparam name="DataType"></typeparam>

enum Property { large = 1, small };

template <typename DataType>
class Binary_Heap
{///顺序数组存储，父子节点满足	child:[i]->[2i+1,2i+2],parent:[i]->[(i-1)/2]
protected:
	enum Direction { left = 1, right = 2 };
public:
	int* data;//存放排序关键值的数组
	int length;
	int maxsize;
	Property property;	///[大/小]根堆
public:
	//初始化有maxsize个元素空间的二叉堆
	Binary_Heap(int maxsize, Property property = small)
		:length(0), maxsize(maxsize), data{ nullptr },property{property}
	{///顺序数组的首个元素留空不使用,申请固定的maxsize+1容量大小的数组
		try
		{
			if (maxsize < 1)
				throw std::exception("Maxsize must be greater than 0");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		data = new int[maxsize]{};
	}
	~Binary_Heap()
{
	if(data)
		delete[] data;
}
private:
	//下标转位序
	int Position(int index) const
	{return index + 1;}
	int Index(int index) const
	{return index - 1;}
	//交换堆中元素
	void Element_Swap(int index_x, int index_y)
	{
		try
		{
			if (index_x < 0 || index_x >= length)
				throw std::exception("X illegal");
			if (index_y < 0 || index_y >= length)
				throw std::exception("Y illegal");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		int temp = data[index_x];
		data[index_x] = data[index_y];
		data[index_y] = temp;
	}
	//元素上浮
	void Element_Upflow(int index)
	{
		if (index == 0)
			return;
		try
		{
			if (index < 0 || index >= length)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Element_Upflow Failed: index illegal" << std::endl;
			return;
		}
		int index_parent = Index_Parent(index);
		if (property == small)
		{///小根堆
			while (index > 0 && data[index_parent] > data[index])
			{///若子节点比父节点小，交换父子节点
				Element_Swap(index_parent, index);
				index = index_parent;
				index_parent = index_parent == 0 ? 0 : Index_Parent(index);		///循环到index为根节点时，避免抛出异常
			}
		}
		else
		{///大根堆
			while (index > 0 && data[index_parent] < data[index])
			{///若子节点比父节点小，交换父子节点
				Element_Swap(index_parent, index);
				index = index_parent;
				index_parent = index_parent == 0 ? 0 : Index_Parent(index);		///循环到index为根节点时，避免抛出异常
			}
		}
	}
	//元素下潜
	void Element_Sink(int index)
	{
	//#define Sort
	#ifdef Sort///用于排序时不抛出异常
		if (index < 1 || index > length)
			return;
		while (2 * index <= length)
		{
			int i = 2 * index;///初始索引设为左孩子
			///定位比父节点小的索引
			if (i + 1 <= length && data[i + 1] < data[i])
				i += 1;///右孩子比父节点小
			if (data[i] >= data[index])
				break;///父节点比所有子节点小，阻止交换
			Element_Swap(i, index);
			index = i;
		}
	#endif // Sort
	#ifndef Sort
		try
		{
			if (index < 0 || index >= length)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Element_Sink Failed: index illegal" << std::endl;
			return;
		}
		while (index < length)
		{
			int index_child = Index_Child(index,left);///先假设索引设为左孩子

			///定位与父节点替换的索引
			if (property == small)
			{///小根堆
				if (index_child + 1 < length && data[index_child + 1] < data[index_child])
					++index_child;///右孩子比父节点小,且比左孩子小
				if (data[index_child] >= data[index])
					break;///父节点比所有子节点小，阻止交换

			}
			else
			{///大根堆
				if (index_child + 1 < length && data[index_child + 1] > data[index_child])
					index_child += 1;///右孩子比父节点大
				if (data[index_child] <= data[index])
					break;///父节点比所有子节点大，阻止交换
			}
			Element_Swap(index_child, index);
			index = index_child;
		}
	#endif // !Sort
	}

	int Index_Parent(int index)
	{
		try
		{
			if (index < 1)	
				throw std::exception("Parent is not exsist");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return NULL;
		}
		return (index - 1) / 2;
	}
	int Index_Child(int index,Direction direction)
	{
		try
		{
			if (index < 0)
				throw std::exception("Illegal index");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return NULL;
		}
		return (direction == left) ? index * 2 + 1 : index * 2 + 2;
	}

public:
	//返回堆顶元素
	DataType Heap_Top()
	{return data[0]; }
	//在二叉堆中插入元素key
	void Heap_Push(int data)
	{
		try
		{
			if (length >= maxsize)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Insert Failed: Heap is full" << std::endl;
			return;
		}
		length++;
		this->data[Index(length)] = data;
		Element_Upflow(Index(length));
	}
	//删除堆顶元素
	void Heap_Pop()
	{
		try
		{
			if (length < 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Extract Failed: Heap is empty" << std::endl;
			return;
		}
		DataType root = Heap_Top();
		Element_Swap(0, Index(length));///首位互换，再下沉
		data[Index(length)] = NULL;
		--length;///堆长度-1代替删除
		Element_Sink(0);///被交换的根节点下沉
		return ;
	}
	void Heap_Show()
	{
		std::cout
			<< "Length:" << length << std::endl
			<< "index end:" << length << std::endl
			<< "Maxsize:" << maxsize << std::endl;
		for (int i = 0; i < maxsize; i++)
			std::cout << "[" << i << ':' << data[i] << "] ";
		std::cout << std::endl;
	}
};

























