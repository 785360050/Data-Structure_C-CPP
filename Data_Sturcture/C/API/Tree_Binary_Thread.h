#pragma once
#include <iostream>

#include "Global Variables.h"

/// <summary>
/// 将二叉树线索化后，
/// 对应的遍历开销降低
/// 且易于从任意节点寻找逻辑前驱和后继
/// (任意n个节点的二叉树有n+1个空链域)
/// </summary>

struct ThreadNode
{
	DataType data;
	struct ThreadNode* left;
	struct ThreadNode* right;
	std::string name;
	//标记是否为左线索，指向逻辑前驱
	bool Thread_left;
	//标记是否为右线索，指向逻辑后继
	bool Thread_right;
};
typedef struct ThreadNode ThreadNode;

struct BinaryTree_Thread
{
	ThreadNode* root;
	int num;
};
typedef BinaryTree_Thread BTree_Thread;

//创建线索树头节点，绑定节点root为根
BTree_Thread* BinaryTree_Init_Root(ThreadNode* root);
//删除线索二叉树
void BinaryTree_Destory(BTree_Thread* tree);
//创建线索节点，节点名字为name
ThreadNode* BinaryTree_CreateNode_Thread(std::string name);
// 插入线索节点，在线索树tree中，双亲为parenr的[左/右]位置
void BinaryTree_Insert_Thread(BTree_Thread* tree, ThreadNode* parent, Direction pos, ThreadNode* node);
//访问线索节点名
void BinaryTree_Visit(ThreadNode* node);
// 中序线索化二叉树
void BinaryTree_Thread_Inorder(ThreadNode* node);
// 中序遍历线索化树(优化开销)
void BinaryTree_Traversal_Inorder_Thread(ThreadNode* node);


