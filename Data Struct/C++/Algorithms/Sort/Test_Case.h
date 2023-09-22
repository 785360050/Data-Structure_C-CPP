#pragma once

#include <iostream>
#include <stdlib.h>
#include <time.h>



struct Element
{
    int key;            // 查找表中每个数据元素的关键值
    void* data;         // 数据的其他区域
};

struct SortList
{
    Element* data;      // 存放查找表中数据元素的首地址
    int length;         // 表元素个数
};





void Element_Swap(Element* x, Element* y)
{  
    Element temp;
    temp.key = x->key;
    temp.data = x->data;

    x->key = y->key;
    x->data = y->data;

    y->key = temp.key;
    y->data = temp.data;
}




// 产生随机数范围[low,high]
SortList* generateRandomArray(int num, int begin, int end)
{
    SortList* list = new SortList; //(SortList* )malloc(sizeof(SortList));
    list->length = num;
    list->data = new Element[num];//(Element* )malloc(sizeof(Element) * num);
    srand(time(NULL) + 1);
    for (int i = 0; i < num; ++i) {
        list->data[i].key = (rand() % (end - begin + 1)) + begin;
        list->data[i].data = NULL;
    }
    return list;
}


SortList* SortList_Copy(SortList* old)
{
    SortList* list = (SortList*)malloc(sizeof(SortList));
    list->length = old->length;
    list->data = (Element* )malloc(sizeof(Element) * old->length);
    for (int i = 0; i < old->length; ++i) {
        list->data[i].key = old->data[i].key;
        list->data[i].data = old->data[i].data;
    }
    return list;
}

void SortList_Destroy(SortList* list)
{
    if (list) {
        if (list->data) {
            free(list->data);
        }
        free(list);
    }
}

static bool Result_Check(SortList* table) 
{
    for (int i = 0; i < table->length - 1; ++i) 
    {
        if (table->data[i].key > table->data[i + 1].key) 
            return false;
    }
    return true;
}


//typedef void (*sort_fun)(SortList*);

void testSort(const char* sortName, void sort_method(SortList*), SortList* table)
{
    clock_t start = clock();
    sort_method(table);///函数作为参数传入实现排序方式的切换实现
    clock_t end = clock();
    if (Result_Check(table) == false) {
        printf("%s failed!\n", sortName);
        return;
    }
    printf("%s cost time: %fs.\n", sortName, (double)(end - start) / CLOCKS_PER_SEC);
    //printf("%s cost time: %fs.\n", sortName, (double)(end - start));
}

//显示排序数据集合
void SortList_Show(const SortList* const list)
{
    for (int i = 0; i < list->length; i++)
        std::cout << list->data[i].key << ' ';
    std::cout << std::endl;
}






