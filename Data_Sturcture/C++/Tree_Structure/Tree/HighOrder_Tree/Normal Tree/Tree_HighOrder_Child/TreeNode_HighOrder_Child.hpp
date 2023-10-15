#pragma once


#include <vector>

#include "../../TreeNode_HighOrder.hpp"
//单链节点
template<typename DataType>
class TreeNode_HighOrder_Child :public TreeNode_HighOrder<DataType>
{
public:
	std::vector<int> children;
	int length;	///当前节点孩子个数
public:
	TreeNode_HighOrder_Child(std::string name, DataType element = NULL)
		:TreeNode_HighOrder<DataType>(name, element),length(0) {};
};

