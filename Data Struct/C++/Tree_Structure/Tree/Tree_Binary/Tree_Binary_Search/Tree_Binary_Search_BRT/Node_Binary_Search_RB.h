#pragma once

#include <string>

#include "../../../Tree_Node.h"

enum Colour { red = 0, black = 1 };

template <typename DataType>
struct Node_Binary_Search_RB:public TreeNode<DataType>
{
	enum Colour colour;
	//std::string name;
	//DataType element;
	Node_Binary_Search_RB<DataType>* parent;
	Node_Binary_Search_RB<DataType>* left;
	Node_Binary_Search_RB<DataType>* right;
public:
	Node_Binary_Search_RB(std::string name, DataType element = 0, Colour colour = red)
		:TreeNode<DataType>(name,element), left(nullptr), right(nullptr), colour(colour), parent(nullptr) {};

};
