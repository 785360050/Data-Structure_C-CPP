
#pragma once

#include <string>

//#include "../Node_BinaryTree.hpp"
#include "../../Tree_Node.hpp"

template <typename DataType, typename KeyType = int>
struct Node_Binary_Search :public TreeNode<DataType>
{
public:
	KeyType key;	///用于搜索树的节点比较
	///KeyType 若为class或struct类型需要重载运算符"<"、">"、"="
public:
	Node_Binary_Search(KeyType key, std::string name, DataType element = DataType{})
		: TreeNode<DataType>(name, element), key(key){};

public:
	//用于删除时替换
	void replace_by(Node_Binary_Search<DataType, KeyType>* other)
	{
		this->element = other->element;
		this->name = other->name;
		this->key = other->key;
	}
};