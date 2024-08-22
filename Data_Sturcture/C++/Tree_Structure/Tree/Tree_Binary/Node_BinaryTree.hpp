#pragma once

#include <string>
using std::string;

#include "../Tree_Node.hpp"
#include "Tree_Binary_Normal/Tree_Binary_Normal.hpp"


///友元模板类声明
template <typename DataType, typename NodeType>
class Binary_Tree;	
template <typename DataType, typename NodeType>
class Binary_Tree_Search;

template <typename DataType>
class Node_BinaryTree :public TreeNode<DataType>
{
public:
	Node_BinaryTree<DataType>* left;
	Node_BinaryTree<DataType>* right;
public:
	friend class Binary_Tree<DataType, Node_BinaryTree<DataType>>;
	friend class Binary_Tree_Search<DataType, Node_BinaryTree<DataType>>;
public:
	Node_BinaryTree(std::string name, DataType element = 0)
		:TreeNode<DataType>(name, element), left(nullptr), right(nullptr) {};

};


// 另一种实现方式，不见得比直接访问成员变量好
// 因为虽然不用每个子类重复定义left和right，但是需要override Child_Left和Child_Right
namespace Refactor 
{

	template <typename DataType>
	class Node_Binary : public TreeNode<DataType>
	{
		using NodeType = Node_Binary<DataType>;

	private:
		NodeType *left{nullptr};
		NodeType *right{nullptr};

	public:
		Node_Binary(std::string name, DataType element = 0)
			: TreeNode<DataType>(name, element) {};

	public:
		NodeType *Child_Left() const { return left; };
		NodeType *Child_Right() const { return left; };
	};
}
