#pragma once


#include <iostream>
#include "Sort_TestCase.h"


extern struct Element;

struct SearchList
{
    Element* data;      // 存放查找表中数据元素的首地址
    int length;         // 表元素个数
    int maxsize;        // 表空间容量
};
typedef struct SearchList SearchList;


//生成maxsize个空间的递增数据集,首元素不用于存储
void SearchList_Init(SearchList* list, int maxsize)
{///从下标1开始存储数据
    list->length = maxsize;
    list->maxsize = maxsize+1;
    list->data = new Element[maxsize+1];
    for (int i = 1; i <= maxsize; i++)
        list->data[i].key = i;
    list->data[0].key = 0;
}

void SearchList_Show(const SearchList* const list)
{
    std::cout
        << "Length:" << list->length << std::endl
        << "Maxsize:" << list->maxsize << std::endl;
    for (int i = 0; i < list->maxsize; i++)
    {
        std::cout << list->data[i].key << ' ';
    }
    std::cout << std::endl;
}


//顺序查找，返回key元素下标
int Search_Sequence(SearchList* const list, int key)
{
    list->data[0].key = key;
    int i = list->length;
    while (list->data[i].key != key)
        i--;
    if (i == 0)
        return NULL;
    return i;
}

//折半查找，要求查找前数据集有序
int Search_Binary(const SearchList* const list, int key)
{
    try
    {
        if (list->length <= 0)
            throw std::exception{ "Searh List is not exisit" };
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    int begin = 1;
    int end = list->maxsize;
    int mid;
    while (begin<=end)
    {
        mid = (begin + end) / 2;
        if (list->data[mid].key == key)
            return mid;
        else if (list->data[mid].key < key)
            begin = mid + 1;
        if (list->data[mid].key > key)
            end = mid - 1;
    
    }
    return NULL;
}










