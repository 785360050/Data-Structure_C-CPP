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

//创建线索树
BTree_Thread* BinaryTree_Init_Root(ThreadNode* root);
//void releaseTBTree(BTree_Thread* tree);           

ThreadNode* BinaryTree_CreateNode_Thread(std::string name);
// 插入节点，指定父、左右方向
void BinaryTree_Insert_Thread(BTree_Thread* tree, ThreadNode* parent, Direction pos, ThreadNode* node);
//访问线索节点
void BinaryTree_Visit(ThreadNode* node);
// 中序线索化
void BinaryTree_Thread_Inorder(ThreadNode* node);
// 中序遍历线索化树(优化开销)
void BinaryTree_Traversal_Inorder_Thread(ThreadNode* node);


