#pragma once

#include <string>
using std::string;

#include "../../Node.h"
#include "Tree_Binary_Normal.h"

template <typename DataType>
class TreeNode :public Node<DataType>
{
protected:
//public:
	std::string name;
};


///友元模板类声明
template <typename DataType>
class Binary_Tree;	
template <typename DataType>
class Binary_Tree_Search;

template <typename DataType>
class Node_BinaryTree :public TreeNode<DataType>
{
public:
	Node_BinaryTree<DataType>* left;
	Node_BinaryTree<DataType>* right;
public:
	friend class Binary_Tree<DataType>;
	friend class Binary_Tree_Search<DataType>;
public:
	Node_BinaryTree(std::string name, DataType element = 0)
	{
		this->name = name;
		this->element = element;
		left = right = nullptr;
	}
	void Set_Element(DataType element)
	{this->element = element;}
	void Set_Name(std::string name)
	{this->name = name;}

};

template <typename DataType>
class BinaryTree_Thread;	///友元模板类声明

template <typename DataType>
class Node_BinaryThreadTree :public Node_BinaryTree<DataType>
{
private:
	friend class BinaryTree_Thread<DataType>;
public:
	Node_BinaryThreadTree<DataType>* left;
	Node_BinaryThreadTree<DataType>* right;
	//标记是否为左线索，指向逻辑前驱
	bool thread_left;
	//标记是否为右线索，指向逻辑后继
	bool thread_right;
public:
	Node_BinaryThreadTree(std::string name)
		:Node_BinaryTree<DataType>(name), 
		left{ nullptr }, right{ nullptr }, 
		thread_left{ false }, thread_right{ false }{};
	Node_BinaryThreadTree
	(
		std::string name, DataType element,
		Node_BinaryThreadTree<DataType>* left,
		Node_BinaryThreadTree<DataType>* right
	)
		:Node_BinaryTree<DataType>(name, element)
	{
		this->left = left;
		this->right = right;
		thread_left = thread_right = true;
	}
};

template <typename DataType>
class Tree_Binary_Search_AVL;

//template <typename DataType>
//class Node_Binary_Search_Balance :public Node_BinaryTree<DataType>
//{
//protected:	
//	///当前子树高度,创建默认高度从1开始
//	int height;//节点的平衡因子=左子树高度-右子树高度
//private:
//	friend Tree_Binary_Search_AVL<DataType>;
//public:
//	Node_Binary_Search_Balance(std::string name)
//		:Node_BinaryTree<DataType>(name),height(1) {};
//	int Get_Height() const
//	{return height;}
//
//};


