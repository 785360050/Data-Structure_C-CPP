#pragma once

#include <string>

#include "../../Node.h"

template <typename DataType>
class TreeNode :public Node<DataType>
{
public:
	std::string name;
public:
	TreeNode(std::string name, DataType element = NULL)
		:Node<DataType>(element), name(name) {};
	virtual ~TreeNode() = default;
public:
	void Set_Name(std::string name)
	{this->name = name;}
};