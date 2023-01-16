#pragma once

#include <iostream>


/// <summary>
/// 将二叉树线索化后，
/// 对应的遍历开销降低
/// 且易于从任意节点寻找逻辑前驱和后继
/// (任意n个节点的二叉树有n+1个空链域)
/// </summary>

#include "../../Node.h"
#include "Binary_Node.h"


template <typename DataType>
class BinaryTree_Thread
{
//public:
//	using Node = Node_BinaryThreadTree<DataType>;
public:
	Node_BinaryThreadTree<DataType>* root;
	int num;
private:
	Node_BinaryThreadTree<DataType>* pre = NULL;///辅助指针，指向逻辑前驱,用于先序遍历
	//BinaryTree_Thread(Node_BinaryThreadTree<DataType>* root=nullptr) :root{ root }, num{ 1 } {};
	void DeleteNode(Node_BinaryThreadTree<DataType>* node)
	{
		if (node)
		{///屏蔽线索进入的删除节点递归
			if (node->thread_left == false)
				DeleteNode(node->left);
			if (node->thread_right == false)
				DeleteNode(node->right);
			std::cout << node->name << " ";
			delete node;
			--num;

		}
	}
public:
	BinaryTree_Thread() :root{ nullptr }, num{ 0 } {};
	BinaryTree_Thread(Node_BinaryThreadTree<DataType>* node)
	{
		try
		{
			if (node==nullptr)
				throw std::exception("Root Init Failed: Node is not exisit.");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		this->root = node;
		++num;
	}
	//删除线索二叉子树
	~BinaryTree_Thread()
	{///自下而上递归销毁节点
		if (root)
		{
			std::cout << "删除二叉树树节点个数:" << num << std::endl;
				DeleteNode(root);
		}
		std::cout << std::endl << "BinaryTree_Thread Destroyed" << std::endl;
	}
	// 插入线索节点，在线索树tree中，双亲为parenr的[左/右]位置
	void BinaryTree_Insert_Thread(Node_BinaryThreadTree<DataType>* parent, Direction pos, Node_BinaryThreadTree<DataType>* node)
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
		++num;
	}
	//访问线索节点名
	void BinaryTree_Visit(Node_BinaryThreadTree<DataType>* node)
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
	// 中序线索化二叉树
	void BinaryTree_Thread_Inorder(Node_BinaryThreadTree<DataType>* node)
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
			if (node->left == NULL)
			{///定位到逻辑起点
				node->thread_left = true;
				node->left = pre;
			}
			if (pre && pre->right == NULL)
			{///通过辅助节点添加逻辑后继的线索
				pre->thread_right = true;
				pre->right = node;
			}
			pre = node;///向逻辑后继节点移动
			BinaryTree_Thread_Inorder(node->right);
		}
	}
	// 中序遍历线索化树(优化开销)
	void BinaryTree_Traversal_Inorder_Thread(Node_BinaryThreadTree<DataType>* node)
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
			while (node->thread_left == false)
				node = node->left;///定位到逻辑起点
			BinaryTree_Visit(node);
			while (node->thread_right == true && node->right)
			{///线索存在时直接向逻辑后继移动再访问
				node = node->right;
				BinaryTree_Visit(node);
			}
			node = node->right;///线索不存在时向后移动视角
		}
	}
};




