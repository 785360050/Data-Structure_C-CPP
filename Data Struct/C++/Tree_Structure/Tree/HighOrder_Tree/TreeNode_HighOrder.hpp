#pragma once

#include "../Tree_Node.h"

template <typename DataType>
class TreeNode_HighOrder :public TreeNode<DataType>
{
public:
	int length;		///当前节点孩子个数
public:
	TreeNode_HighOrder(std::string name, DataType element = NULL)
		:TreeNode<DataType>(name,element), length(0) {};
	virtual ~TreeNode_HighOrder() = default;
};