#pragma once

#include <string>
using std::string;

#include "../Tree_Node.h"
#include "Tree_Binary_Normal/Tree_Binary_Normal.h"


///友元模板类声明
template <typename DataType, typename NodeType>
class Binary_Tree;	
template <typename DataType, typename NodeType>
class Binary_Tree_Search;

template <typename DataType>
class Node_BinaryTree :public TreeNode<DataType>
{
public:
	Node_BinaryTree<DataType>* left;
	Node_BinaryTree<DataType>* right;
public:
	friend class Binary_Tree<DataType, Node_BinaryTree<DataType>>;
	friend class Binary_Tree_Search<DataType, Node_BinaryTree<DataType>>;
public:
	Node_BinaryTree(std::string name, DataType element = 0)
		:TreeNode<DataType>(name, element), left(nullptr), right(nullptr) {};

};
