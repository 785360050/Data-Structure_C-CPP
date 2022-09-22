#pragma once


#include <iostream>
#include "Global Variables.h"


struct AVLNode
{
	DataType data;
	AVLNode* left;
	AVLNode* right;
	//当前子树高度
	int hight;//节点的平衡因子=左子树高度-右子树高度
};
typedef struct AVLNode AVLNode;

struct BinaryTree_AVL
{
	AVLNode* root;
	int num;
};
typedef BinaryTree_AVL BTree_AVL;


//创建平衡二叉树头节点，绑定节点root为根
BTree_AVL* BinaryTree_Init_Root_AVL();
//删除平衡二叉树
void BinaryTree_Destory(BTree_AVL* tree);
//创建AVL节点，元素值为data,默认高度从1开始
AVLNode* BinaryTree_CreateNode_AVL(DataType data);
//删除平衡二叉树tree中元素值为data的节点，同步平衡
AVLNode* BinaryTree_AVL_Delete(BTree_AVL* tree, AVLNode* node, DataType data);
// 插入AVL节点，在平衡二叉树tree中,递归过程中同步实现平衡化
void BinaryTree_Insert_AVL(BTree_AVL* tree, DataType data);
//访问AVL节点名
void BinaryTree_Visit_AVL(AVLNode* node);
// 中序遍历平衡二叉树
void BinaryTree_Traversal_Inorder_AVL(AVLNode* node);

