#pragma once



#include <iostream>

#include "Sort_TestCase.h"
#include "../API/Tree_Binary_Heap.h"

//经典冒泡排序
void Sort_Bubble_Classic(SortList* list)
{
	for (int i = 0; i < list->length; i++)
	{
		for (int j = 0; j < list->length - i - 1; j++)
		{
			if (list->data[j].key > list->data[j + 1].key)
				Element_Swap(&list->data[j], &list->data[j + 1]);
		}
	}
}

void Sort_Bubble_Optimized_1(SortList* list)
{///排序过程中记录状态，减少排序次数(增加了if开销，特殊场景(基本有序)下才有优化效果)
	for (int i = 0; i < list->length; i++)
	{
		bool sorted = true;
		for (int j = 0; j < list->length - i - 1; j++)
		{///若当前排序轮次结束后已经排序成功，则退出排序
			if (list->data[j].key > list->data[j + 1].key)
			{
				Element_Swap(&list->data[j], &list->data[j + 1]);
				sorted = false;
			}
		}
		if (sorted)
			break;
	}
}

void Sort_Bubble_Optimized_2(SortList* list)
{
	int index;
	int num = list->length;
	do
	{///每一轮记录交换后已经有序的右边待排数据，减少排序数据集合
		index = 0;
		for (int i = 0; i < num - 1; i++)
		{
			if (list->data[i].key > list->data[i + 1].key)
			{
				Element_Swap(&list->data[i], &list->data[i + 1]);
				index = i + 1;
			}
		}
		num = index;
	} while (index>0);
}



///————————————————————————
#include <stdlib.h>
int Get_Datum_DoubleWay(SortList* list, int index_start, int index_end)
{///双向夹逼，找到第一个基准值的最终位置
	int datum = index_start;//基准值
	int left = datum;///以第一个元素作为基准值
	int right = index_end;
	//srand(time(NULL) + 1);
	//Element_Swap(&list->data[index_start], &list->data[rand() % (index_end - index_start) + index_start]);
	while (left != right)
	{
		while (left<right && list->data[right].key>list->data[datum].key)
			right--;///右边指针向左移动,定位到比基准值小的元素索引
		while (left < right && list->data[left].key <= list->data[datum].key)
			left++;///左边指针向右移动，定位到比基准值大的元素索引
		if (left < right)///每一轮交换左右
			Element_Swap(&list->data[left], &list->data[right]);
	}
	///基准值移入最终位置，完成左右两个子序列的切割
	Element_Swap(&list->data[datum], &list->data[left]);
	return left;


	//int datum = list->data[index_start].key;//基准值
	//void* datum_data = list->data[index_start].data;
	//int left = datum;///以第一个元素作为基准值
	//int right = index_end;
	//while (left < right)
	//{
	//	while (list->data[right].key < datum)
	//		right--;
	//	list->data[left] = list->data[right];
	//	while (list->data[left].key > datum)
	//		left++;
	//	list->data[right] = list->data[left];
	//}
	//list->data[left].key = datum;
	//list->data[left].data = datum_data;
	//return left;
}

static void Sort_Quick_DoubleWay(SortList* list, int index_start, int index_end)
{///切割为若干子序列，递归排序子序列，每轮排序确定子序列中基准值的最终位置
	if (index_start >= index_end)
		return;
	int datum = Get_Datum_DoubleWay(list,index_start,index_end);
	Sort_Quick_DoubleWay(list, index_start, datum - 1);
	Sort_Quick_DoubleWay(list, datum + 1, index_end);
}

void Sort_Quick_DoubleWay(SortList* list)
{
	Sort_Quick_DoubleWay(list, 0, list->length - 1);
}

///————————————————————————快排
int Get_Datum_SingleWay(SortList* list, int index_start, int index_end)
{
	int temp = list->data[index_start].key;
	int mark = index_start;

	for (int i = index_start + 1; i <= index_end; i++)
	{
		if (list->data[i].key < temp)
		{
			mark++;
			Element_Swap(&list->data[mark], &list->data[i]);
		}
	}
	Element_Swap(&list->data[mark], &list->data[index_start]);
	return mark;
}


void Sort_Quick_SingleWay(SortList* list, int index_start, int index_end)
{
	if (index_start >= index_end)
		return;
	int datum = Get_Datum_SingleWay(list, index_start, index_end);
	Sort_Quick_SingleWay(list, index_start, datum - 1);
	Sort_Quick_SingleWay(list, datum + 1, index_end);
}

void Sort_Quick_SingleWay(SortList* list)
{
	Sort_Quick_SingleWay(list, 0, list->length - 1);
}



///——————————————————————堆排序

void Sort_Heap(SortList* list)
{///堆的第一个数组存储空间不使用
	BinaryHeap* h = new BinaryHeap;
	BinaryHeap_Init(h, list->length);
	for (int i = 0; i < list->length; i++)///复制待排数据到堆中
		BinaryHeap_Element_Insert(h, list->data[i].key);///插入的同时排序
	for (int i = 0; i < list->length; i++)///复制回待排列表中
		list->data[i].key = BinaryHeap_Root_Extract(h);

	BinaryHeap_Destroy(h);
}
