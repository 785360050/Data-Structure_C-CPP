#pragma once

#include "Sort_TestCase.h"

void Sort_Insert_Direct(SortList* list)
{
	for (int i = 1; i < list->length; i++)
		for (int n = i ; n > 0 ; n--)
			if(list->data[n-1].key > list->data[n].key)
				Element_Swap(&list->data[n], &list->data[n - 1]);
}

void Sort_Insert_Direct_Optimized(SortList* list)
{
	for (int i = 0; i < list->length; i++)
	{
		Element e = list->data[i];
		int j = i;
		for ( j ; j > 0 && list->data[j - 1].key > e.key; j--)
		{
			list->data[j].key = list->data[j - 1].key;
			list->data[j - 1].data = list->data[j - 1].data;
		}
		list->data[j] = e;
	}
}


void Sort_Insert_Shell(SortList* list)
{///间距gap=2
	for (int gap = list->length / 2; gap > 0; gap /= 2)
	{
		for (int i = gap;i < list->length; i++)
		{
			Element e = list->data[i];
			int j = i;
			for (j; j > 0 && list->data[j - 1].key > e.key; j--)
			{
				list->data[j].key = list->data[j - 1].key;
				list->data[j - 1].data = list->data[j - 1].data;
			}
			list->data[j] = e;
		}
	}
}

