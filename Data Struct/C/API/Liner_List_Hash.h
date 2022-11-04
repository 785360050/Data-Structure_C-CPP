#pragma once

#include <iostream>






struct HashList
{
	int* data;
	int length;
	int maxsize;
};


void HashList_Init(HashList* list, int maxsize);

//哈希函数：除留余数法
int HashFunction_Remain(int size, int key);

//冲突函数：开放定址法-线性探测法
int CollisionFuction_OpenAddressing_LinerProbing(HashList* list, int index, int key);

void HashList_Insert(HashList* list, int key);

void HashList_Destroy(HashList* list);

void HashList_Show(const HashList* const list);


