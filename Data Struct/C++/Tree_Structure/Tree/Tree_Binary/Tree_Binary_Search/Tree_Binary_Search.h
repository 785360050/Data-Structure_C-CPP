#pragma once

#include <queue>
#include <string>

///根据key排序，插入，删除，搜索
template <typename DataType, typename KeyType, typename NodeType>
class Tree_Binary_Search
{
public:
	NodeType* root;
	int count;
private:
	void Destroy_SubTree(NodeType* node)
	{
		if (node)
		{
			Destroy_SubTree(node->left);
			Destroy_SubTree(node->right);
			std::cout << node->key << " ";
			delete node;
			--this->count;
		}
	}
public:
	Tree_Binary_Search() :root(nullptr), count(0) {};
	~Tree_Binary_Search()
	{///自下而上递归销毁节点
		std::cout << "删除二叉树树节点个数:" << this->count << std::endl
			<< "删除顺序为: ";
		if (this->root)
			Destroy_SubTree(this->root);
	}

protected:
	//新建树所需的节点
	virtual NodeType* Node_Create(KeyType key,std::string name, DataType element = NULL)
	{return new NodeType(key, name, element);}
	virtual void Node_Visit_Name(NodeType* node)
	{
		if (node)
		{
			std::cout << node->name << ' ';
		}
	}
	virtual void Node_Visit_Key(NodeType* node)
	{
		if (node)
		{
			std::cout << node->key << ' ';
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
	//插入关键字为key,数据为element的元素
	virtual void Element_Insert(KeyType key, DataType element = NULL) = 0;
	//删除树中关键字为key的元素(同时删除节点)
	virtual void Element_Delete(KeyType key) = 0;
	//查找关键字为key的节点
	NodeType* Node_Search(KeyType key)
	{
		NodeType* p = root;
		while (p)
		{
			if (p->key == key)
				return p;
			else
				p = (key < p->key) ? p->left : p->right;
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

	//先序遍历二叉搜索子树
	void Tree_Traverse_PreOrder(NodeType* node)
	{
		if (node)
		{
			this->Node_Visit_Key(node);			///D
			Tree_Traverse_PreOrder(node->left);		///L
			Tree_Traverse_PreOrder(node->right);	///R
		}
	}
	//中序遍历二叉搜索子树
	void Tree_Traverse_InOrder(NodeType* node)
	{
		if (node)
		{
			Tree_Traverse_InOrder(node->left);		///L
			this->Node_Visit_Key(node);				///D
			Tree_Traverse_InOrder(node->right);		///R
		}
	}
	//后序遍历二叉搜索子树
	void Tree_Traverse_PostOrder(NodeType* node)
	{
		if (node)
		{
			Tree_Traverse_PostOrder(node->left);		///L
			Tree_Traverse_PostOrder(node->right);		///R
			this->Node_Visit_Key(node);				///D
		}
	}

	void Tree_Traverse_LevelOrder(NodeType* node)
	{
		std::queue<NodeType* > q;
		q.push(this->root);
		NodeType* v;
		while (!q.empty())
		{
			v = q.front();
			q.pop();
			this->Node_Visit_Key(v);
			if (v->left)
				q.push(v->left);
			if (v->right)
				q.push(v->right);
		}
	}
};