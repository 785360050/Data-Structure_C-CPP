#pragma once

#include <iostream>

template <typename DataType>
class Tree_Binary_Heap
{///顺序数组存储，父子节点满足	[i]-[2i,2i+1]
public:
	int* data;//存放排序关键值的数组
	int length;
	int maxsize;

public:
	//初始化有maxsize个元素空间的二叉堆
	Tree_Binary_Heap(int maxsize) 
		:length(0), maxsize(maxsize + 1)
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
		data = new int[maxsize+1]{};
	}
	~Tree_Binary_Heap()
{
	if(data)
		delete[] data;
}
private:
	//交换堆中元素
	void Element_Swap(int index_x, int index_y)
	{
		try
		{
			if (index_x<1 || index_x>length)
				throw 1;
			if (index_y<1 || index_y>length)
				throw 2;
		}
		catch (short x)
		{
			if (x == 3)
			{
				std::cout << "Heap is not exist" << std::endl;
				return;
			}
			if (x == 2)
			{
				std::cout << "X illegal" << std::endl;
				return;
			}
			if (x == 1)
			{
				std::cout << "Y illegal" << std::endl;
				return;
			}
			return;
		}
		int temp = data[index_x];
		data[index_x] = data[index_y];
		data[index_y] = temp;
	}
	//元素上浮
	void Element_Upflow(int index)
	{
		try
		{
			if (index < 1 || index > length)
				throw 1;///首元素不用,根节点不上浮
		}
		catch (...)
		{
			std::cout << "index illegal" << std::endl;
			return;
		}
		while (index > 1 && data[index / 2] > data[index])
		{///若子节点比父节点小，交换父子节点
			Element_Swap( index / 2, index);
			index /= 2;
		}
	}
	//元素下潜
	void Element_Sink(int index)
	{
	#define Sort
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
			if (!heap)
				throw 0;
			if (index < 1 || index > length)
				throw 1;
		}
		catch (bool x)
		{
			if (x == 0)
			{
				std::cout << "Heap is not exist" << std::endl;
				return;
			}

			if (x == 1)
			{
				std::cout << "index illegal" << std::endl;
				return;
			}

		}
		while (2 * index <= length)
		{
			int i = 2 * index;///初始索引设为左孩子
			///定位比父节点小的索引
			if (i + 1 <= length && data[i + 1] < data[i])
				i += 1;///右孩子比父节点小
			if (data[i] >= data[index])
				break;///父节点比所有子节点小，阻止交换
			Element_Swap(heap, i, index);
			index = i;
		}
	#endif // !Sort
	}

public:
	//在二叉堆中插入元素key
	void BinaryHeap_Element_Insert(int data)
	{
		try
		{
			if (length >= maxsize - 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Insert Failed: Heap is full" << std::endl;
			return;
		}
		length++;
		this->data[length] = data;
		Element_Upflow(length);
	}
	//从二叉堆中提取堆顶元素(删除并返回)
	int BinaryHeap_Root_Extract()
	{
		try
		{
			if (length < 1)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Extract Failed: Heap is empty" << std::endl;
			return NULL;
		}
		int root = data[1];
		Element_Swap(1, length);///首位互换，再下沉
		length--;///堆长度-1代替删除
		Element_Sink(1);///被交换的根节点下沉
		return root;
	}
	void BinaryHeap_Show()
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

























