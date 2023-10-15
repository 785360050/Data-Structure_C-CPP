#pragma once

#include <string>

#include "../../Node.hpp"

template <typename DataType>
class TreeNode :public Node<DataType>
{
public:
	std::string name{"Undefined"};
public:
	TreeNode(std::string name, DataType element = NULL)
		: Node<DataType>(std::move(element)), name(name){};
	TreeNode(std::string name, DataType &&element = NULL)
		: Node<DataType>(std::forward<DataType>(element)), name(name){};
	virtual ~TreeNode() = default;
public:
	void Set_Name(std::string name)
	{this->name = name;}
};