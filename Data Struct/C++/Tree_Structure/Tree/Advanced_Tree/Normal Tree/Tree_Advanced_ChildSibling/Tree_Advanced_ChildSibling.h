#pragma once


#include <vector>

#include "Node_Tree_ChildSibling.h"
#include "Tree_Advanced_ChildSibling.h"

template <typename DataType,typename NodeType= Node_Tree_ChildSibling<DataType>>
class Tree_Advanced_ChildSibling:public Tree_Normal<DataType,NodeType> 
{///孩子兄弟表示法
protected:
	//NodeType* root;
	//int branch;			///分叉数量上限
	//int count;
	
private:
	//重置子树所有元素为0
	void Clear(NodeType* node)
	{
		if (!node)
			return;
		while (node->child_first)
		{
			NodeType* del_child = node->child_first;
			node->child_first = del_child->child_first;
			while (del_child->sibling_next)
			{
				NodeType* del_sibling = del_child->sibling_next;
				del_child->sibling_next = del_sibling->sibling_next;
				delete del_sibling;
			}
			delete del_child;
		}
		delete node;
	}
	size_t Deep(NodeType* node)
	{
		if (!node)
			return 0;
		else
		{
			size_t deep_left, deep_right = 0;
			deep_left = Deep(node->left);
			deep_right = Deep(node->right);
			if (deep_left > deep_right)
				return ++deep_left;
			else
				return ++deep_right;
		}

	}
	//返回节点名为name的父节点
	NodeType* Parent(NodeType* node, std::string name)
	{
		NodeType* n = this->root;
		NodeType* parent;
		if (n->left->name == name || n->right->name == name)
			return n;
		if (n->left == NULL && n->right == NULL)
			return NULL;
		parent = Parent(n->left, name);
		if (!parent)
			parent = Parent(n->right, name);
		if (parent == NULL)
		{
			std::cout << "Parent Not Found!" << std::endl;
			return NULL;
		}
		return parent;

	}

public:
	Tree_Advanced_ChildSibling(int branch)
		:Tree_Normal<DataType, NodeType>(branch) {};
	~Tree_Advanced_ChildSibling()
	{Clear(this->root); }
public:
	//(普通树，二叉树，线索树，二叉搜索树，AVL树，并查集，红黑树)
	void Tree_Clear(NodeType* node)
	{Clear(node); }
	//bool Tree_CheckEmpty()
	//{
	//	return count == 0 ? true : false;
	//}
	//返回树深度
	//size_t Tree_GetDepth()
	//{
	//	return Deep(root);
	//}
	//返回树根节点
	virtual NodeType* Tree_GetRoot()
	{return this->root;}
	virtual void Tree_Set_Root(NodeType* root)
	{///只能在初始化的时候使用，后续使用count会出错
		this->root = root;
		this->count++;
	}
	//显示树所有信息
	virtual void Tree_Show()
	{
		std::cout << "当前子树节点总数: " << this->count << std::endl
			<< "分叉数: " << this->branch << std::endl;
		std::cout << std::endl;
	}
	//返回树中节点node的元素值
	void Node_GetElement(NodeType* node)
	{
		try
		{
			if (!node)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Get Element Faild: Node is not exist" << std::endl;
			return;
		}
		return node->element;
	}
	//将树中节点node的元素值为element
	void Node_SetElement(NodeType* node, DataType element)
	{
		try
		{
			if (!node)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Set Element Faild: Node is not exist" << std::endl;
			return;
		}
		node->element=element;
	}
	//todo 返回节点node的双亲节点
	//NodeType* Node_GetParent(NodeType* node)
	//{
	//	try
	//	{
	//		if (!node)
	//			throw 1;
	//	}
	//	catch (...)
	//	{
	//		std::cout << "Set Element Faild: Node is not exist" << std::endl;
	//		return NULL;
	//	}
	//	return Parent(node, node->name);
	//}
	//返回节点node的左孩子节点
	///void Node_GetChild_Left() = 0;
	//返回节点node的右边兄弟节点1
	///void Node_GetSibling_Right() = 0;
	//将节点node作为第x个孩子插入到子树tree中
	void Node_Insert(NodeType* node, NodeType* parent, int position)
	{
		try
		{
			if (!node)
				throw std::exception("Node_Insert Failed: node is not exsist");
			if (!parent)
				throw std::exception("Node_Insert Failed: parent is not exsist");
			if (position<1 || position>this->branch)
				throw std::exception("Node_Insert Failed: position illegal");
			if (parent->length == this->branch)
				throw std::exception("Node_Insert Failed: Parent's Child is full");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		NodeType* child = parent->child_first;
		if (!child && position == 1)	///若parent为叶节点则新增孩子
			parent->child_first = node;
		else
		{///在非叶节点parent处插入孩子
			for (int i = 1; i < position - 1; ++i)
				child = child->sibling_next;	///定位节点前驱
			node->sibling_next = child->sibling_next;
			child->sibling_next = node;
		}
		++parent->length;
		this->count++;
	}

	//新建节点(new 分配空间)
	//virtual NodeType* Node_Create(std::string name,DataType element=0 )
	//{
	//	NodeType* node = new NodeType(name, element);
	//	return node;
	//}
	//

public:
	//先根遍历
	void Tree_Traverse_PreOrder(NodeType* node)
	{
		while (node)
		{
			this->Tree_Visit_Name(node);
			Tree_Traverse_PreOrder(node->child_first);
			node = node->sibling_next;
		}
	}
	//后根遍历
	void Tree_Traverse_PostOrder(NodeType* node)
	{
		if (node->child_first)
		{
			for (NodeType* child = node->child_first; child; child = child->sibling_next)
				Tree_Traverse_PostOrder(child);
		}
		this->Tree_Visit_Name(node);
	}
	//层次遍历
	void Tree_Traverse_LevelOrder(NodeType* node)
	{
		std::queue<NodeType*> queue;
		queue.push(this->root);
		while (!queue.empty())
		{
			NodeType* child = queue.front()->child_first;
			while (child)
			{///所有下层节点入队
				queue.push(child);
				child = child->sibling_next;
			}
			this->Tree_Visit_Name(queue.front());
			queue.pop();
		}
	}
	//访问节点名
	//void Tree_Visit_Name(NodeType* node)
	//{
	//	if (node)
	//	{
	//		std::cout << node->name << ' ';
	//	}
	//}

};




