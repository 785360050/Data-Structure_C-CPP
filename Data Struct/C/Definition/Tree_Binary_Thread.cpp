#include <iostream>

#include "../API/Tree_Binary_Thread.h"



BTree_Thread* BinaryTree_Init_Root(ThreadNode* root)
{
	BTree_Thread* t = new BTree_Thread;
	t->num = 0;
	t->root = root;
	return t;
}

static void DeleteNode(BTree_Thread* tree, ThreadNode* node)
{
	if (node)
	{///屏蔽线索进入的删除节点递归
		if (node->Thread_left == false)
			DeleteNode(tree, node->left);
		if (node->Thread_right == false)
			DeleteNode(tree, node->right);
		std::cout << node->name << " ";
		free(node);
		tree->num--;
		
	}
}
void BinaryTree_Destory(BTree_Thread* tree)
{///自下而上递归销毁节点
	if (tree)
	{
		std::cout << "删除二叉树树节点个数:" << tree->num << std::endl;
		if (tree->root)
			DeleteNode(tree, tree->root);
	}
}

ThreadNode* BinaryTree_CreateNode_Thread(std::string name)
{///初始化左右指针为空，线索标记为false
	ThreadNode* n = new ThreadNode;
	n->left = n->right = nullptr;
	n->Thread_left = n->Thread_right = false;
	n->name = name;
	return n;
}

void BinaryTree_Insert_Thread(BTree_Thread* tree, ThreadNode* parent, Direction pos, ThreadNode* node)
{
	/// <summary>
	/// 用于初始化线索树的测试，可能考虑不全
	/// </summary>
	/// <param name="tree"></param>
	/// <param name="parent"></param>
	/// <param name="pos"></param>
	/// <param name="node"></param>
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

static ThreadNode* pre = NULL;///辅助指针，指向逻辑前驱
void BinaryTree_Thread_Inorder(ThreadNode* node)
{	/// <summary>
	/// 利用辅助指针指向逻辑前驱节点
	/// 先找到中序起点，
	/// 在递归中序遍历的同时检查链域，为空时添加线索
	/// 
	/// </summary>
	/// <param name="node"></param>
	if (node)
	{
		BinaryTree_Thread_Inorder(node->left);
		if (node->left==NULL)
		{///定位到逻辑起点
			node->Thread_left = true;
			node->left = pre;
		}
		if (pre && pre->right == NULL)
		{///通过辅助节点添加逻辑后继的线索
			pre->Thread_right = true;
			pre->right = node;
		}
		pre = node;///向逻辑后继节点移动
		BinaryTree_Thread_Inorder(node->right);
	}
}

void BinaryTree_Traversal_Inorder_Thread(ThreadNode* node)
{	/// <summary>
	/// 线索化后优化遍历开销
	/// 先找到逻辑起点，开始循环向后遍历(关键思路)
	/// 线索存在时直接向逻辑后继移动并访问
	/// 线索不存在时在右孩子继续找逻辑起点向后找线索
	/// (即不断找逻辑起点，通过仅用线索遍历向后遍历)
	/// </summary>
	/// <param name="node"></param>
	while (node)
	{
		while (node->Thread_left == false)
			node = node->left;///定位到逻辑起点
		BinaryTree_Visit(node);
		while (node->Thread_right==true&&node->right)
		{///线索存在时直接向逻辑后继移动再访问
			node = node->right;
			BinaryTree_Visit(node);
		}
		node = node->right;///线索不存在时向后移动视角
	}
}


