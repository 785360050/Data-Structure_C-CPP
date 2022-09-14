#include <iostream>

#include "../API/Tree_Binary_Thread.h"



BTree_Thread* BinaryTree_Init_Root(ThreadNode* root)
{
	BTree_Thread* t = new BTree_Thread;
	t->num = 0;
	t->root = root;
	return t;
}
//void releaseTBTree(BTree_Thread* tree);           

ThreadNode* BinaryTree_CreateNode_Thread(std::string name)
{
	ThreadNode* n = new ThreadNode;
	n->left = n->right = nullptr;
	n->Thread_left = n->Thread_right = nullptr;
	n->name = name;
	return n;
}

void BinaryTree_Insert(BTree_Thread* tree, ThreadNode* parent, Direction pos, ThreadNode* node)
{
	pos == right ?
		parent->right = node : parent->left = node;
	tree->num++;
}

void BinaryTree_Visit(ThreadNode* node)
{
	if (node)
	{
		std::cout << node->name << " ";
	}
	else
	{
		std::cout << "TreeNode is not exist" << std::endl;
		exit(0);
	}

}

static ThreadNode* pre = NULL;
void BinaryTree_Thread_Inorder(ThreadNode* node);

void BinaryTree_Traversal_Inorder_Thread(ThreadNode* node);


