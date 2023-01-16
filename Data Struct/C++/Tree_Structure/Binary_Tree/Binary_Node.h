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

template <typename DataType>
class Binary_Tree;	///友元模板类声明

template <typename DataType>
class Node_BinaryTree :public TreeNode<DataType>
{
public:
	Node_BinaryTree<DataType>* left;
	Node_BinaryTree<DataType>* right;
	friend class Binary_Tree<DataType>;
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


