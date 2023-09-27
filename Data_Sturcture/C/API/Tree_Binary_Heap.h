#pragma once


#include <iostream>


struct BinaryHeap
{///顺序数组存储，父子节点满足	[i]-[2i,2i+1]
	int* data;//存放排序关键值的数组
	int length;
	int maxsize;
};
typedef struct BinaryHeap BinaryHeap;

//初始化有maxsize个元素空间的二叉堆
void BinaryHeap_Init(BinaryHeap* heap, int maxsize);

//销毁二叉堆
void BinaryHeap_Destroy(BinaryHeap* heap);

//在二叉堆中插入元素key
void BinaryHeap_Element_Insert(BinaryHeap* heap, int data);

//从二叉堆中提取堆顶元素
int BinaryHeap_Root_Extract(BinaryHeap* heap);

//显示二叉堆存储空间信息
void BinaryHeap_Show(BinaryHeap* heap);
















