#include "../API/Liner_List_Hash.h"

#include <cstring>

void HashList_Init(HashList* list, int maxsize)
{
	list->length = 0;
	list->maxsize = maxsize;
	list->data = new int[maxsize];
	memset(list->data, NULL, sizeof(int) * maxsize);
}

//��ϣ����������������
int HashFunction_Remain(int size, int key)
{
	return key % size;
}

//��ͻ���������Ŷ�ַ��-����̽�ⷨ
int CollisionFuction_OpenAddressing_LinerProbing(const HashList* list, int index, int key)
{
	return (index + 1) % list->maxsize;
}

void HashList_Insert(HashList* list, int key)
{
	try
	{
		if (list->length >= list->maxsize)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Insert Failed: Hash List is Full" << std::endl;
		return;
	}
	int index = HashFunction_Remain(list->maxsize, key);
	while (list->data[index] != NULL)
	{
		index = CollisionFuction_OpenAddressing_LinerProbing(list, index, key);
	}
	list->data[index] = key;
	list->length++;
}

int HashList_Locate(const HashList* const list, int key)
{
	int index = HashFunction_Remain(list->maxsize, key);
	int t = 1;
	while (list->data[index] != key&&t<list->length)
	{
		index = CollisionFuction_OpenAddressing_LinerProbing(list, index, key);
		t++;
	}
	if (list->data[index] == key)
		return index;
	else
		return NULL;
}

void HashList_Destroy(HashList* list)
{
	delete[] list->data;
	delete list;
}

void HashList_Show(const HashList* const list)
{
	try
	{
		if (!list)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Hash List is not exist" << std::endl;
		return;
	}
	std::cout
		<< "Length:" << list->length << std::endl
		<< "Maxsize:" << list->maxsize << std::endl;
	for (int i = 0; i < list->maxsize; i++)
		std::cout << list->data[i] << ' ';
	std::cout << std::endl;
}






//�½���ϣ�ڵ㣬��ų�ͻ����
static HashNode* HashNode_Create(int key)
{
	HashNode* n = new HashNode;
	n->key = key;
	n->data = NULL;
	n->next = nullptr;
	return n;
}

//����ַ�������ͻ
//����Ϊͷ���ϣ�ڵ�
void CollisionFuction_OpenAddressing_LinkAddress(HashList_Link* list,int index, int key)
{
	HashNode* n = HashNode_Create(key);
	n->next = list->data[index].next;
	list->data[index].next = n;
}

void HashList_Init(HashList_Link* list, int maxsize)
{
	list->length = maxsize;
	list->count = 0;
	list->data = new HashNode[maxsize];
	memset(list->data, NULL, sizeof(HashNode) * maxsize);
}


void HashList_Insert(HashList_Link* list, int key)
{
	try
	{
		if (!list)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Insert Failed: Hash List is not exist" << std::endl;
		return;
	}
	int index = HashFunction_Remain(list->length, key);
	if (list->data[index].key == NULL)
		list->data[index].key = key;
	else
		CollisionFuction_OpenAddressing_LinkAddress(list, index, key);
	list->count++;
}

int HashList_Locate(const HashList_Link* const list, int key)
{
	int index = HashFunction_Remain(list->length, key);
	int t = 1;
	HashNode* n;
	if (list->data[index].key != key)
	{
		n = list->data[index].next;
		while (n && n->key != key)
			n = n->next;
		if (n && n->key == key)
			return index;
		else
			return NULL;
	}
	else
		return NULL;
}

void HashList_Destroy(HashList_Link* list)
{
	HashNode* n;
	for (int i = 0; i < list->length; i++)
	{
		while (list->data[i].next)
		{
			n = list->data[i].next;
			list->data[i].next = n->next;
			delete n;
		}
	}
	delete[] list->data;
	delete list;
}

void HashList_Show(const HashList_Link* const list)
{
	try
	{
		if (!list)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Hash List is not exist" << std::endl;
		return;
	}
	HashNode* n;
	std::cout
		<< "Length:" << list->length << std::endl
		<< "Count:" << list->count << std::endl
		<< "[Index:Key]->[HashNode...]" << std::endl;
	for (int i = 0; i < list->length; i++)
	{
		std::cout << i << ':' << list->data[i].key << "->";
		n = list->data[i].next;
		while (n)
		{
			std::cout << n->key << "->";
			n = n->next;
		}
		std::cout << "NULL" << std::endl;
	}
	std::cout << std::endl;
}


