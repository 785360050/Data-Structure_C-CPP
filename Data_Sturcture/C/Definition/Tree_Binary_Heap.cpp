///小根堆实现

#include "../API/Tree_Binary_Heap.h"

#include <cstring>

//交换堆中元素
static void Element_Swap(BinaryHeap* heap, int index_x, int index_y)
{
	try
	{
		if (index_x<1 || index_x>heap->length)
			throw 1;
		if (index_y<1 || index_y>heap->length)
			throw 2;
		if (!heap)
			throw 3;
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
	int temp = heap->data[index_x];
	heap->data[index_x] = heap->data[index_y];
	heap->data[index_y] = temp;
}

//元素上浮
static void Element_Upflow(BinaryHeap* heap, int index)
{
	try
	{
		if (!heap)
			throw 0;
		if (index < 1 || index > heap->length)
			throw 1;///首元素不用,根节点不上浮
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
	while (index > 1 && heap->data[index / 2] > heap->data[index])
	{///若子节点比父节点小，交换父子节点
		Element_Swap(heap, index / 2, index);
		index /= 2;
	}
}

//元素下潜
static void Element_Sink(BinaryHeap* heap, int index)
{
#define Sort
#ifdef Sort///用于排序时不抛出异常
	if (!heap)
		return;
	if (index < 1 || index > heap->length)
		return;
	while (2 * index <= heap->length)
	{
		int i = 2 * index;///初始索引设为左孩子
		///定位比父节点小的索引
		if (i + 1 <= heap->length && heap->data[i + 1] < heap->data[i])
			i += 1;///右孩子比父节点小
		if (heap->data[i] >= heap->data[index])
			break;///父节点比所有子节点小，阻止交换
		Element_Swap(heap, i, index);
		index = i;
	}
#endif // Sort
#ifndef Sort
	try
	{
		if (!heap)
			throw 0;
		if (index < 1 || index > heap->length)
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
	while (2 * index <= heap->length)
	{
		int i = 2 * index;///初始索引设为左孩子
		///定位比父节点小的索引
		if (i + 1 <= heap->length && heap->data[i + 1] < heap->data[i])
			i += 1;///右孩子比父节点小
		if (heap->data[i] >= heap->data[index])
			break;///父节点比所有子节点小，阻止交换
		Element_Swap(heap, i, index);
		index = i;
	}
#endif // !Sort
}

//初始化有maxsize个元素空间的二叉堆
void BinaryHeap_Init(BinaryHeap* heap, int maxsize)
{///顺序数组的首个元素留空不使用,申请固定的maxsize+1容量大小的数组
	heap->length = 0;
	heap->maxsize = maxsize + 1;
	heap->data = new int[heap->maxsize];
	memset(heap->data, 0, sizeof(int) * heap->maxsize);
}

//销毁二叉堆
void BinaryHeap_Destroy(BinaryHeap* heap)
{
	try
	{
		if (!heap)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Heap Destroy Failed:Heap is not exisit" << std::endl;
		return;
	}
	delete[] heap->data;
	delete heap;
}

//在二叉堆中插入元素key
void BinaryHeap_Element_Insert(BinaryHeap* heap, int data)
{
	try
	{
		if (heap->length >= heap->maxsize - 1)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Insert Failed: Heap is full" << std::endl;
		return;
	}
	heap->length++;
	heap->data[heap->length] = data;
	Element_Upflow(heap, heap->length );
}

//从二叉堆中删除并返回堆顶元素
int BinaryHeap_Root_Extract(BinaryHeap* heap)
{
	try
	{
		if (heap->length < 1)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Extract Failed: Heap is empty" << std::endl;
		return NULL;
	}
	int root = heap->data[1];
	Element_Swap(heap, 1, heap->length);///首位互换，再下沉
	heap->length--;///堆长度-1代替删除
	Element_Sink(heap, 1);///被交换的根节点下沉
	return root;
}

void BinaryHeap_Show(BinaryHeap* heap)
{
	std::cout 
		<< "Length:" << heap->length << std::endl
		<< "index end:" << heap->length << std::endl
		<< "Maxsize:" << heap->maxsize << std::endl;
	for (int i=0; i<heap->maxsize; i++)
		std::cout << "[" << i << ':' << heap->data[i] << "] ";
	std::cout << std::endl;
}












