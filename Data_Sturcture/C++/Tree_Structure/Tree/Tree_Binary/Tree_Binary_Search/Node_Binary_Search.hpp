
#pragma once

#include <string>

// #include "../Node_BinaryTree.hpp"
#include "../../Tree_Node.hpp"

template <typename DataType, typename KeyType = int>
struct Node_Binary_Search : public TreeNode<DataType>
{
public:
	KeyType key; /// 用于搜索树的节点比较
	/// KeyType 若为class或struct类型需要重载运算符"<"、">"、"="
public:
	Node_Binary_Search(KeyType key, std::string name, DataType element = DataType{})
		: TreeNode<DataType>(name, element), key(key) {};

public:
	// 用于删除时替换
	void replace_by(Node_Binary_Search<DataType, KeyType> *other)
	{
		this->element = other->element;
		this->name    = other->name;
		this->key     = other->key;
	}
};

/// ============================================================================================================
/// NOTE: 此处的设计可能需要被重构
/// 由于直接访问Node_BinaryTree的成员无法实现复用left和right，因为无法实现直接转换为子类，所以目前3种搜索树的节点都是独自额外定义的
/// 如果将Node_BinaryTree改为动态多态，调用函数访问左右孩子，不仅需要每个子类override Child_Left()和Child_Right()，还需要改动所有搜索树的此类调用地方
/// 两种实现方式不见得哪种就更好
/// ============================================================================================================