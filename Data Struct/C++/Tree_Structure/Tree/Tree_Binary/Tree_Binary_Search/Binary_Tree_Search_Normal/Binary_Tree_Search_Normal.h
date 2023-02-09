#pragma once

#include "../../Tree_Binary_Normal/Tree_Binary_Normal.h"
#include "../Tree_Binary_Search.h"

template <typename DataType,typename NodeType = Node_BinaryTree<DataType>>
class Tree_Binary_Search_Normal:public Tree_Binary_Search<DataType,NodeType>
{
public:
	Tree_Binary_Search_Normal() :Tree_Binary_Search<DataType, NodeType>() {};
	~Tree_Binary_Search_Normal() = default;
protected:
	//增加二叉搜索节点data
	virtual Node_BinaryTree<DataType>* insertnode(Node_BinaryTree<DataType>* node,DataType data)
	{
		if (!node)
		{
			Node_BinaryTree<DataType>* p = this->Node_Create(std::to_string(data),data);
			++this->count;
			return p;
		}
		if (data < node->element)
		{
			Node_BinaryTree<DataType>* left = insertnode(node->left, data);
			node->left = left;
		}
		else if (data > node->element)
		{
			Node_BinaryTree<DataType>* right = insertnode(node->right, data);
			node->right = right;
		}
		else
			std::cout << "Insert failed: Existed" << std::endl;
		return node;
	}
	//删除二叉搜索节点data
	Node_BinaryTree<DataType>* deletenode(Node_BinaryTree<DataType>* tree, DataType data)
	{///删除子树tree中值为data的节点
		/// [此处用逻辑后继顶替]
		if (tree == nullptr)///递归出口
			return nullptr;
		if (data < tree->element)
		{///第2-4个if用于寻路，找到删除目标节点
			tree->left = deletenode(tree->left, data);
			return tree;
		}
		if (data > tree->element)
		{
			tree->right = deletenode(tree->right, data);
			return tree;
		}
		///删除节点，找代替节点
		if (data == tree->element)
		{///此时位于删除节点处，删除节点并调整二叉搜索树
			if (tree->left == NULL && tree->right == NULL)
			{///前两个if处理单孩子情况
				delete tree;
				return nullptr;
			}
			if (tree->left == nullptr)
			{
				Node_BinaryTree<DataType>* temp = tree->right;
				delete tree;
				return temp;
			}
			if (tree->right == nullptr)
			{
				Node_BinaryTree<DataType>* temp = tree->left;
				delete tree;
				return temp;
			}
			else///左右子树都不为空
			{///用右孩子的最小节点代替(逻辑后继)
				Node_BinaryTree<DataType>* p = this->Element_Next(tree);
				tree->element = p->element;///直接用顶替的节点先覆盖
				tree->name = p->name;
				tree->right = deletenode(tree->right, p->element);///再删除顶替节点
				return tree;
			}
		}
	}
public:
	void Element_Insert(DataType data)
	{
		this->root = insertnode(this->root, data);
	}
	void Element_Insert_NonRecursive(DataType data)
	{
		Node_BinaryTree<DataType>* current = this->root, * precursor = nullptr;
		while (current)
		{
			precursor = current;
			if (data == current->element)
			{
				std::cout << "Insert failed: Existed" << std::endl;
				return;
			}
			if (data < current->element)
				current = current->left;
			else
				current = current->right;
		}
		Node_BinaryTree<DataType>* node = new Node_BinaryTree<DataType>(std::to_string(data), data);
		++this->count;
		if (precursor && data < precursor->element) 
			precursor->left = node;
		else if (precursor && data > precursor->element) 
			precursor->right = node;
		if (!precursor) 
			this->root = node;



	}

	//删除二叉搜索子树tree中值为data的节点
	void Element_Delete(DataType data)
	{
		deletenode(this->root, data);
	}

	
};


