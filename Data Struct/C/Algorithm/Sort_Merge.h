#pragma once

#include <iostream>

#include "Sort_TestCase.h"


static void Merge(SortList* list, int left, int mid, int right)
{
	///分配左右空间
	int num_left = mid - left + 1;
	int num_right = right - mid;
	Element* a1 = new Element[num_left];
	Element* a2 = new Element[num_right];

	for (int i = 0; i < num_left; i++)
		a1[i] = list->data[left];
	for (int i = 0; i < num_right; i++)
		a2[i] = list->data[mid + i];

	///合并有序数组算法合并两组数据
	int i = 0, j = 0, k = left;
	while (i < num_left && j < num_right)
	{
		if (a1[i].key <= a2[j].key)
		{
			list->data[k] = a1[i];
			i++;
		}
		else
		{
			list->data[k] = a2[j];
			j++;
		}
		k++;
	}
	while (i < num_left)
	{
		list->data[k] = a1[i];
		k++; i++;

	}
	while (i < num_right)
	{
		list->data[k] = a2[j];
		k++; i++;

	}
	delete[] a1;
	delete[] a2;

}

static void BinaryMerge(SortList* list, int index_left, int index_right)
{
	if (index_left >= index_right)
		return;
	int mid = (index_left + index_right) / 2;

	BinaryMerge(list, index_left, mid);
	BinaryMerge(list, mid + 1, index_right);
	Merge(list, index_left, mid, index_right);
}

//归并排序
void Sort_Merge(SortList* list)
{
	BinaryMerge(list, 0, list->length - 1);
}




