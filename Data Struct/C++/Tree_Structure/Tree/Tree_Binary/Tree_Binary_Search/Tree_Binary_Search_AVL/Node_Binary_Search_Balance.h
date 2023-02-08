#pragma once


#include <string>

#include "../../../Tree_Node.h"

template <typename DataType>
class Node_Binary_Search_Balance:public TreeNode<DataType>
{
public:
	//DataType element;
	//std::string name;
	Node_Binary_Search_Balance<DataType>* left;
	Node_Binary_Search_Balance<DataType>* right;
	//当前子树高度
	int height;///节点的平衡因子=左子树高度-右子树高度
public:
	Node_Binary_Search_Balance(std::string name, DataType element = 0)
		:TreeNode<DataType>(name,element), left(nullptr), right(nullptr), height(1) {};

};
