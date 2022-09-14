#pragma once
#include <iostream>

#include "Global Variables.h"

struct ThreadNode
{
	DataType data;
	struct ThreadNode* left;
	struct ThreadNode* right;
	std::string name;
	bool Thread_left;
	bool Thread_right;
};
typedef struct ThreadNode ThreadNode;

struct BinaryTree_Thread
{
	ThreadNode* root;
	int num;
};
typedef BinaryTree_Thread BTree_Thread;

//����������
BTree_Thread* BinaryTree_Init_Root(ThreadNode* root);
//void releaseTBTree(BTree_Thread* tree);           

ThreadNode* BinaryTree_CreateNode_Thread(std::string name);
// ����ڵ㣬ָ���������ҷ���
void BinaryTree_Insert_Thread(BTree_Thread* tree, ThreadNode* parent, Direction pos, ThreadNode* node);
//���������ڵ�
void BinaryTree_Visit(ThreadNode* node);
// ����������
void BinaryTree_Thread_Inorder(ThreadNode* node);
// ���������������(�Ż�����)
void BinaryTree_Traversal_Inorder_Thread(ThreadNode* node);


