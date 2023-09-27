#pragma once

#include <string>
using std::string;

#include "../../Tree_Node.h"


template <typename DataType, typename NodeType>
class BinaryTree_Thread;	///友元模板类声明

template <typename DataType>
class Node_BinaryThreadTree :public TreeNode<DataType>
{
private:
	friend class BinaryTree_Thread<DataType, Node_BinaryThreadTree<DataType>>;
public:
	Node_BinaryThreadTree<DataType>* left;
	Node_BinaryThreadTree<DataType>* right;
	//标记是否为左线索，指向逻辑前驱
	bool thread_left;
	//标记是否为右线索，指向逻辑后继
	bool thread_right;
public:
	Node_BinaryThreadTree(std::string name, DataType element = 0)
		:TreeNode<DataType>(name, element),
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
