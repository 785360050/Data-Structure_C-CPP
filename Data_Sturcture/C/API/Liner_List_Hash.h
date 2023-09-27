#pragma once

#include <iostream>





//����̽�ⷨ�����ͻ
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

//����ַ�������ͻ
struct HashList_Link
{
	HashNode* data;
	int length;//��¼��ϣ����
	int count;//��¼Ԫ�ظ���
};
typedef struct HashList_Link HashList_Link;




void HashList_Init(HashList* list, int maxsize);

//��ϣ����������������
int HashFunction_Remain(int size, int key);

//��ͻ���������Ŷ�ַ��-����̽�ⷨ
int CollisionFuction_OpenAddressing_LinerProbing(const HashList* list, int index, int key);

void HashList_Insert(HashList* list, int key);

//����Ԫ��key���±�
int HashList_Locate(const HashList* const list, int key);

void HashList_Destroy(HashList* list);

void HashList_Show(const HashList* const list);


///��������������������������������������������������������������������������������

void HashList_Init(HashList_Link* list, int maxsize);

void HashList_Insert(HashList_Link* list, int key);

int HashList_Locate(const HashList_Link* const list, int key);

void HashList_Destroy(HashList_Link* list);

void HashList_Show(const HashList_Link* const list);

