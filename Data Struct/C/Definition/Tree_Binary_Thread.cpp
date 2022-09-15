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
	n->Thread_left = n->Thread_right = false;
	n->name = name;
	return n;
}

void BinaryTree_Insert_Thread(BTree_Thread* tree, ThreadNode* parent, Direction pos, ThreadNode* node)
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
void BinaryTree_Thread_Inorder(ThreadNode* node)
{
	if (node)
	{
		BinaryTree_Thread_Inorder(node->left);
		if (node->left==NULL)
		{
			node->Thread_left = true;
			node->left = pre;
		}
		if (pre && pre->right == NULL)
		{
			pre->Thread_right = true;
			pre->right = node;
		}
		pre = node;
		BinaryTree_Thread_Inorder(node->right);
	}
		
}

void BinaryTree_Traversal_Inorder_Thread(ThreadNode* node)
{
	while (node)
	{
		while (node->Thread_left == false)
			node = node->left;
		BinaryTree_Visit(node);
		while (node->Thread_right==true&&node->right)
		{
			node = node->right;
			BinaryTree_Visit(node);
		}
		node = node->right;
	}
}


