#pragma once

#include <iostream>
#include "Tree_Binary_BRT.h"
#include "Global Variables.h"

struct RBNode
{
	enum Colour colour;
	int key;
	struct RBNode* partent;
	struct RBNode* left;
	struct RBNode* right;
};
typedef struct RBNode RBNode;


struct Tree_Binary_BRT
{
	RBNode* root;
	int num;
};
typedef struct Tree_Binary_BRT RBTree;

//初始化红黑树
RBTree* BRT_Init(RBNode* root = nullptr);

void RBTree_Destroy(RBTree* tree);

RBNode* RBTree_Search(RBTree* tree, int key);

//创建红黑节点(默认为红色)
RBNode* RBNode_Create(int key, Colour colour = red);

//在红黑树tree插入node节点
void RBTree_Insert(RBTree* tree, RBNode* node);

void RBTree_Traverse_Inorder(RBNode* node);
void RBTree_Traverse_Preorder(RBNode* node);