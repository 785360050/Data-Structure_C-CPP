#pragma once

#include <iostream>





//线性探测法解决冲突
struct HashList
{
	int* data;
	int length;
	int maxsize;
};

struct HashNode
{
	int key;
	void* data;
	struct HashNode* next;
};
typedef struct HashNode HashNode;

//链地址法解决冲突
struct HashList_Link
{
	HashNode* data;
	int length;//记录哈希表长度
	int count;//记录元素个数
};
typedef struct HashList_Link HashList_Link;




void HashList_Init(HashList* list, int maxsize);

//哈希函数：除留余数法
int HashFunction_Remain(int size, int key);

//冲突函数：开放定址法-线性探测法
int CollisionFuction_OpenAddressing_LinerProbing(const HashList* list, int index, int key);

void HashList_Insert(HashList* list, int key);

//查找元素key的下标
int HashList_Locate(const HashList* const list, int key);

void HashList_Destroy(HashList* list);

void HashList_Show(const HashList* const list);


///————————————————————————————————————————

void HashList_Init(HashList_Link* list, int maxsize);

void HashList_Insert(HashList_Link* list, int key);

int HashList_Locate(const HashList_Link* const list, int key);

void HashList_Destroy(HashList_Link* list);

void HashList_Show(const HashList_Link* const list);

