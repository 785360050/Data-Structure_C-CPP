
#pragma once

#include <string>

#include "../Node_Binary_Search.hpp"

template <typename DataType, typename KeyType = int>
struct Node_Binary_Search_Normal :public Node_Binary_Search<DataType, KeyType>
{
public:
	Node_Binary_Search_Normal<DataType, KeyType>* left;
	Node_Binary_Search_Normal<DataType, KeyType>* right;
public:
	Node_Binary_Search_Normal(KeyType key, std::string name = "Unfixed name", DataType element = NULL)
		:Node_Binary_Search<DataType, KeyType>(key, name, element), 
		left(nullptr), right(nullptr) {};
};