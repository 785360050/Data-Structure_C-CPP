#pragma once

#include <iostream>

struct B_Node
{
	int* key;			///存放关键字
	int length;			///节点当前元素个数
	int maxsize;		///节点最大元素个数
	B_Node** index;		///存放指针索引
	B_Node* parent;		///
};

struct B_Tree
{///回溯法实现插入删除
	B_Node* root;
	int order;			///B树阶数
	int count;
};

//初始化B树
void B_Tree_Init(B_Tree* tree, int order);

//销毁B树
void B_Tree_Destroy(B_Tree* tree);

//创建有order个分叉的节点
B_Node* B_Tree_Create_Node(int order);
//
//Result B_Tree_Search(B_Tree* tree, int key);

static int B_Tree_Node_Locate(B_Node* node, int key);
//插入关键字
void B_Tree_Insert(B_Tree* tree, int key);

//中序遍历
void B_Tree_Traverse_Inorder(B_Node* node);



