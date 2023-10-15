#pragma once


#include <string>

#include "../Node_Binary_Search.hpp"

template <typename DataType, typename KeyType>
class Node_Binary_Search_Balance :public Node_Binary_Search<DataType, KeyType>
{
public:
	//当前子树高度
	int height;///节点的平衡因子=左子树高度-右子树高度
	Node_Binary_Search_Balance<DataType, KeyType>* left;
	Node_Binary_Search_Balance<DataType, KeyType>* right;
public:
	Node_Binary_Search_Balance(KeyType key, std::string name, DataType element = 0)
		:Node_Binary_Search<DataType, KeyType>(key, name, element), left(nullptr), right(nullptr), height(1) {};
public:
	void replace_by(Node_Binary_Search_Balance<DataType, KeyType>* other)
	{
		this->element = other->element;
		this->name = other->name;
		this->key = other->key;
		//this->height = other->height;
	}
	int Height()
	{return (this == nullptr) ? 0 : height;}
	int Balance()
	{return (this == nullptr) ? left->Height() - right->Height() : 0;}
};
