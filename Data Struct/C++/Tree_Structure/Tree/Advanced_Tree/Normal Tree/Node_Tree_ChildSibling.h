#pragma once



#pragma once

#include <string>
using std::string;

#include "../../Tree_Node.h"



//孩子兄弟法表示的树节点
template <typename DataType>
class Node_Tree_ChildSibling :public TreeNode<DataType>
{
public:
	Node_Tree_ChildSibling<DataType>* child_first;
	Node_Tree_ChildSibling<DataType>* sibling_next;
	int length;	///当前节点孩子个数

public:
	Node_Tree_ChildSibling
	(
		std::string name, DataType element = NULL,
		Node_Tree_ChildSibling<DataType>* child_first = nullptr,
		Node_Tree_ChildSibling<DataType>* sibling_next = nullptr
	)
		:TreeNode<DataType>(name, element), child_first(child_first), sibling_next(sibling_next),length(0)
	{};
	virtual ~Node_Tree_ChildSibling() = default;
};
