#pragma once

#include <iostream>


/// <summary>
/// 将二叉树线索化后，
/// 对应的遍历开销降低
/// 且易于从任意节点寻找逻辑前驱和后继
/// (任意n个节点的二叉树有n+1个空链域)
/// </summary>

#include "Node_BinaryThreadTree.h"
#include "../Tree_Binary.h"

template <typename DataType, typename NodeType = Node_BinaryThreadTree<DataType>>
class BinaryTree_Thread:public Tree_Binary<DataType,NodeType>
{
private:
	bool thread;	///记录是否已线索化
	NodeType* pre = NULL;///辅助指针，指向逻辑前驱,用于先序遍历
private:
	void Delete_Subtree(NodeType* node)
	{
		if (node)
		{///屏蔽线索进入的删除节点递归
			if (node->thread_left == false)
				Delete_Subtree(node->left);
			if (node->thread_right == false)
				Delete_Subtree(node->right);
			std::cout << node->name << " ";
			delete node;
			--this->count;
		}
	}
public:
	BinaryTree_Thread():Tree_Binary<DataType,NodeType>(),thread(false) {};
	BinaryTree_Thread(NodeType* node)
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
		++this->count;
	}
	//删除线索二叉子树
	~BinaryTree_Thread()
	{///自下而上递归销毁节点
		if (this->root)
		{
			std::cout << "删除二叉树树节点个数:" << this->count << std::endl;
			Delete_Subtree(this->root);
			this->root = nullptr;	///防止基类root指针悬空
		}
		std::cout << std::endl << "BinaryTree_Thread Destroyed" << std::endl;
	}
	// 插入线索节点，在线索树tree中，双亲为parenr的[左/右]位置
	void Node_Insert(NodeType* node, NodeType* parent, Direction pos) override
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
		++this->count;
	}

	void Tree_Traverse_PreOrder(NodeType* node) override
	{
		std::cout << "Not Implemented yet" << std::endl;
	}
	void Tree_Traverse_InOrder(NodeType* node) override
	{
		std::cout << "Not Implemented yet" << std::endl;
	}
	// 中序遍历线索化树(优化开销)
	void Tree_Traverse_LevelOrder(NodeType* node) override
	{	/// <summary>
	/// 线索化后优化遍历开销
	/// 先找到逻辑起点，开始循环向后遍历(关键思路)
	/// 线索存在时直接向逻辑后继移动并访问
	/// 线索不存在时在右孩子继续找逻辑起点向后找线索
	/// (即不断找逻辑起点，通过仅用线索遍历向后遍历)
	/// </summary>
	/// <param name="node"></param>
		try
		{
			if (!thread)
				throw std::exception("UnModified yet,can't level traverse");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		while (node)
		{
			while (node->thread_left == false)
				node = node->left;///定位到逻辑起点
			this->Tree_Visit_Name(node);
			while (node->thread_right == true && node->right)
			{///线索存在时直接向逻辑后继移动再访问
				node = node->right;
				this->Tree_Visit_Name(node);
			}
			node = node->right;///线索不存在时向后移动视角
		}
	}
	void Tree_Traverse_PostOrder(NodeType* node) override
	{
		std::cout << "Not Implemented yet" << std::endl;
	}
	void Tree_Show()
	{
		std::cout << "当前子树节点总数: " << this->count << std::endl;
	}

public:///非接口
	// 线索化二叉树(中序遍历的同时线索化)
	void ThreadTree_Modify(NodeType* node)
	{	/// <summary>
	/// 利用辅助指针指向逻辑前驱节点
	/// 先找到中序起点，
	/// 在递归中序遍历的同时检查链域，为空时添加线索
	/// 
	/// </summary>
	/// <param name="node"></param>
		if (thread)
			return;
		if (node)
		{
			ThreadTree_Modify(node->left);
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
			ThreadTree_Modify(node->right);
		}
		if (node == this->root)
			thread = true;	///标记已线索化(仅执行一次)
	}

};




