#pragma once

#include <string>

#include "../Node_Binary_Search.h"

enum Colour { red = 0, black = 1 };

template <typename DataType, typename KeyType = int>
struct Node_Binary_Search_RB :public Node_Binary_Search<DataType, KeyType>
{
	enum Colour colour;
	Node_Binary_Search_RB<DataType>* parent;
	Node_Binary_Search_RB<DataType>* left;
	Node_Binary_Search_RB<DataType>* right;
public:
	Node_Binary_Search_RB(KeyType key, std::string name, DataType element = NULL, Colour colour = red)
		:Node_Binary_Search<DataType, KeyType>(key, name, element), 
		left(nullptr), right(nullptr), colour(colour), parent(nullptr) {};
public:
	void replace_by(Node_Binary_Search_RB<DataType, KeyType>* other)
	{
		this->element = other->element;
		this->name = other->name;
		this->key = other->key;
		//this->colour = other->colour;	///?
	}
};


