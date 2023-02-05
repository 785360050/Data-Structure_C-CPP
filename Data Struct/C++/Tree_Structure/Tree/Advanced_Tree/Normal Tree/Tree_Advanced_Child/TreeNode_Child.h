#pragma once


#include <vector>

#include "../../../Tree_Node.h"
//单链节点
template<typename DataType>
class TreeNode_Child :public TreeNode<DataType>
{
public:
	std::vector<int> children;
	int length;	///当前节点孩子个数
public:
	TreeNode_Child(std::string name, DataType element = NULL)
		:TreeNode<DataType>(name, element),length(0) {};
};

