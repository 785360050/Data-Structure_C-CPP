#pragma once


#include <string>

#include "../../TreeNode_HighOrder.hpp"

//孩子兄弟法表示的树节点
template <typename DataType>
class TreeNode_HighOrder_ChildSibling :public TreeNode_HighOrder<DataType>
{
public:
	TreeNode_HighOrder_ChildSibling<DataType>* child_first;
	TreeNode_HighOrder_ChildSibling<DataType>* sibling_next;
	//int length;	///当前节点孩子个数

public:
	TreeNode_HighOrder_ChildSibling
	(
		std::string name, DataType element = NULL,
		TreeNode_HighOrder_ChildSibling<DataType>* child_first = nullptr,
		TreeNode_HighOrder_ChildSibling<DataType>* sibling_next = nullptr
	)
		:TreeNode_HighOrder<DataType>(name, element), child_first(child_first), sibling_next(sibling_next)
	{};
	virtual ~TreeNode_HighOrder_ChildSibling() = default;
};

