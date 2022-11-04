#pragma once

#include <iostream>






struct HashList
{
	int* data;
	int length;
	int maxsize;
};


void HashList_Init(HashList* list, int maxsize);

//��ϣ����������������
int HashFunction_Remain(int size, int key);

//��ͻ���������Ŷ�ַ��-����̽�ⷨ
int CollisionFuction_OpenAddressing_LinerProbing(HashList* list, int index, int key);

void HashList_Insert(HashList* list, int key);

void HashList_Destroy(HashList* list);

void HashList_Show(const HashList* const list);


