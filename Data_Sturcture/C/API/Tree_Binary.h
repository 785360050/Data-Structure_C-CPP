#pragma once


#include <iostream>
#include <string>

#include "Global Variables.h"

struct TreeNode
{
	DataType data;
	struct TreeNode* left;
	struct TreeNode* right;
	std::string name;
};
typedef struct TreeNode TNode;

struct BinaryTree
{
	TNode* root;
	int num;
};
typedef struct BinaryTree BTree;



//新建二叉树头节点
BTree* BinaryTree_Init_Root(TNode* root);
//删除树
void BinaryTree_Destory(BTree* tree);
//新建节点(节点名)
TNode* BinaryTree_CreateNode(std::string name);
//新建节点(值)
TNode* BinaryTree_CreateNode(DataType data);
//二叉树tree中,在父节点parent的pos[左/右]位置，插入节点node,
void BinaryTree_Insert(BTree* tree, TNode* parent, Direction pos, TNode* node);

//访问node节点
void BinaryTree_Visit(TNode* node);
//访问node节点数据
void BinaryTree_Visit_Data(TNode* node);

//广度遍历
void BinaryTree_Traversal_Level(BTree* tree);
//DLR
void BinaryTree_Traversal_Preorder(TNode* node);
void BinaryTree_Traversal_Preorder_NoneRecursion(TNode* node);
//LDR
void BinaryTree_Traversal_Inorder(TNode* node);
void BinaryTree_Traversal_Inorder_Data(TNode* node);
void BinaryTree_Traversal_Inorder_NonRecursive(TNode* node);
//LRD
void BinaryTree_Traversal_Postorder(TNode* node);
void BinaryTree_Traversal_Postorder_NonRecursive(TNode* node);






