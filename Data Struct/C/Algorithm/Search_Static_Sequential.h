#pragma once


#include <iostream>


extern struct Element;

struct SearchList
{
    Element* data;      // ��Ų��ұ�������Ԫ�ص��׵�ַ
    int length;         // ��Ԫ�ظ���
    int maxsize;        // ��ռ�����
};
typedef struct SearchList SearchList;


//����maxsize���ռ�ĵ������ݼ�,��Ԫ�ز����ڴ洢
void SearchList_Init(SearchList* list, int maxsize)
{///���±�1��ʼ�洢����
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


//˳����ң�����keyԪ���±�
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

//�۰���ң�Ҫ�����ǰ���ݼ�����
int Search_Binary(const SearchList* const list, int key)
{
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










