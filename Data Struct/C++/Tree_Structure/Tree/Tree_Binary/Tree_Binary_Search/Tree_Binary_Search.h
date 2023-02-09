#pragma once


#include <string>

template <typename DataType, typename NodeType>
class Tree_Binary_Search
{
//protected:
public:
	NodeType* root;
	int count;
public:
	Tree_Binary_Search() :root(nullptr), count(0) {};
	~Tree_Binary_Search() = default;

protected:
	virtual NodeType* Node_Create(std::string name, DataType element = NULL)
	{return new NodeType(name, element);}
	virtual void Node_Visit_Name(NodeType* node)
	{
		if (node)
		{
			std::cout << node->name << ' ';
		}
	}
	//定位逻辑后继节点，即右子树的中序首节点
	NodeType* Element_Next(NodeType* node)
	{///不存在抛错
		try
		{
			if (!node->right)
				throw std::exception("No Next Node");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return nullptr;
		}
		node = node->right;
		while (node && node->left)
			node = node->left;
		return node;
	}
	//定位逻辑前驱节点，即左子树的中序末节点
	NodeType* Element_Precursor(NodeType* node)
	{///不存在抛错
		try
		{
			if (!node->left)
				throw std::exception("No Precursor Node");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return nullptr;
		}
		node = node->left;
		while (node && node->right)
			node = node->right;
		return node;
	}

public:
	NodeType* Tree_GetRoot()
	{return root;}
	
	virtual void Element_Insert(DataType data) = 0;
	virtual void Element_Delete(DataType data) = 0;
	NodeType* Node_Search(string name)
	{
		NodeType* p = root;
		while (p)
		{
			if (p->name == name)
				return p;
			else
				p = (name < p->name) ? p->left : p->right;
		}
		return nullptr;
	}

	DataType Element_Get(NodeType* node)
	{
		try
		{
			if (!node)
				throw std::exception("Node is not exisit");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return NULL;
		}
		return node->element;

	}

	//virtual void Tree_Traverse_InOrder(NodeType* node) = 0;
	void Tree_Traverse_PreOrder(NodeType* node)
	{
		if (node)
		{
			this->Node_Visit_Name(node);			///D
			Tree_Traverse_PreOrder(node->left);		///L
			Tree_Traverse_PreOrder(node->right);	///R
		}
	}
	void Tree_Traverse_InOrder(NodeType* node)
	{
		if (node)
		{
			Tree_Traverse_InOrder(node->left);		///L
			this->Node_Visit_Name(node);			///D
			Tree_Traverse_InOrder(node->right);		///R
		}
	}
	void Tree_Traverse_PostOrder(NodeType* node)
	{
		if (node)
		{
			Tree_Traverse_PostOrder(node->left);		///L
			Tree_Traverse_PostOrder(node->right);		///R
			this->Node_Visit_Name(node);				///D
		}
	}
};