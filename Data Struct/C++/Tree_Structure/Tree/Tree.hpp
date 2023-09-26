#pragma once



#include <iostream>

#include "Tree_Node.h"

using Direction = int;

template <typename NodeType,typename DataType >
class Tree
{///孩子兄弟表示法
protected:
	NodeType* root;
	int branch;			///分叉数量上限
	int count;

protected:
	//重置子树所有元素为0
	virtual void Clear(NodeType* node);
	//virtual int Deep(NodeType* node);
	//返回节点名为name的父节点
	virtual NodeType* Parent(NodeType* node, std::string name)
	{
		NodeType* n = root;
		NodeType* parent;
		if (n->left->name == name || n->right->name == name)
			return n;
		if (n->left == NULL && n->right == NULL)
			return NULL;
		parent = Parent(n->left, name);
		if (!parent)
			parent = Parent(n->right, name);
		if (parent == NULL)
		{
			std::cout << "Parent Not Found!" << std::endl;
			return NULL;
		}
		return parent;

	}
	//访问节点名
	void Node_Visit_Name(NodeType* node)
	{
		if (node)
		{
			std::cout << node->name << ' ';
		}
	}
public:
	Tree()
	{};
	virtual ~Tree() = default;
public:
	//(普通树，二叉树，线索树，二叉搜索树，AVL树，并查集，红黑树)
	bool Tree_CheckEmpty() const
	{return count == 0 ? true : false;}
	//返回树深度
	//virtual int Tree_GetDepth()
	//{return Deep(root);}
	//返回树根节点
	virtual NodeType* Tree_GetRoot()
	{return root;}
	//显示树所有信息
	virtual void Tree_Show() = 0;
	//将节点node作为第x个孩子插入到子树tree中
	void Node_Insert(NodeType* node, NodeType* parent, Direction pos)
	{
		pos == right ?
			parent->right = node : parent->left = node;
		count++;
	}

	//新建节点(new 分配空间)
	virtual NodeType* Node_Create(std::string name, DataType element = 0) = 0;
	//{
	//	NodeType* node = new NodeType(name, element);
	//	return node;
	//}


public:
	//前序遍历二叉树	DLR
	virtual void Tree_Traverse_PreOrder(NodeType* node) = 0;
	//前序遍历二叉树	LDR
	virtual void Tree_Traverse_InOrder(NodeType* node) = 0;
	//前序遍历二叉树	LRD
	virtual void Tree_Traverse_PostOrder(NodeType* node) = 0;
	//层次遍历二叉树
	virtual void Tree_Traverse_LevelOrder(NodeType* node) = 0;
	

};



