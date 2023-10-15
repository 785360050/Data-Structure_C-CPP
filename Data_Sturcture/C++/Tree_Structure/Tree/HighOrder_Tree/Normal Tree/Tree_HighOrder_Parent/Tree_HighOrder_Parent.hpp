#pragma once

#include <vector>

#include "../../TreeNode_HighOrder.hpp"
#include "../Normal Tree.hpp"

template <typename DataType,typename NodeType= TreeNode_HighOrder<DataType>>
class Tree_HighOrder_Parent :public Tree_Normal<DataType,NodeType>
{///双亲表示法
protected:
	struct Element
	{
		NodeType* node;	///节点
		int parent;		///记录双亲在数组中的下标
		//int num;		///记录孩子个数
		Element(NodeType* node, int parent)
			:node(node), parent(parent){};
	};
protected:
	std::vector<Element> vertex;

private:
	//重置子树所有元素为0
	void Clear(NodeType* node)
	{
		std::cout << "Not Implemented yet" << std::endl;
	}
	int Deep(NodeType* node)
	{
		std::cout << "Not Implemented yet" << std::endl;
		return NULL;
	}
	//返回节点名为name的父节点
	NodeType* Parent(NodeType* node, std::string name)
	{
		std::cout << "Not Implemented yet" << std::endl;
		return nullptr;
	}
	//返回节点在vertex中的下标
	int Index(NodeType* node)
	{
		for (int i = 0; i < vertex.size(); ++i)
		{
			if (vertex[i].node == node)
				return i;
		}
		return -1;
	}
public:
	Tree_HighOrder_Parent(int branch)
		:Tree_Normal<DataType,NodeType>(branch) {};
	~Tree_HighOrder_Parent() = default;
public:
	//(普通树，二叉树，线索树，二叉搜索树，AVL树，并查集，红黑树)
	void Tree_Clear()
	{
		vertex.erase(vertex.begin(), vertex.end());
	}
	//返回树深度
	int Tree_GetDepth()
	{
		return Deep(this->root);
	}
	//返回树根节点
	NodeType* Tree_GetRoot() override
	{
		return this->root;
	}
	void Tree_Set_Root(NodeType* root)
	{///只能在初始化的时候使用
		vertex.push_back(Element(root, -1));
		this->count++;
	}
	//显示树所有信息
	virtual void Tree_Show()
	{
		std::cout << "当前子树节点总数: " << this->count << std::endl
			<< "分叉数: " << this->branch << std::endl;
		std::cout << "[index] [vertex] -> [index_parent]" << std::endl;
		for (int i = 0; i < vertex.size(); ++i)
		{
			std::cout << '[' << i << "] " << vertex[i].node->name << "->" << vertex[i].parent << std::endl;
		}
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
		node->element = element;
	}
	//todo 返回节点node的双亲节点
	NodeType* Node_GetParent(NodeType* node)
	{
		return Index(node).parent;
	}
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
				throw std::runtime_error("Node_Insert Failed: node is not exsist");
			if (!parent)
				throw std::runtime_error("Node_Insert Failed: parent is not exsist");
			if (position<1 || position>this->branch)
				throw std::runtime_error("Node_Insert Failed: position illegal");
			for (const auto& n : vertex)
			{
				if (n.node == node)
					throw std::runtime_error("Node_Insert Failed: Node already exists");
				if (n.node == parent && n.node->length >= this->branch)
					throw std::runtime_error("Node_Insert Failed: Parent's Child is full");
			}
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		int i;

		for (i = 0; i != vertex.size(); ++i)
		{///定位父节点下标
			if (vertex[i].node == parent)
				break;
		}
		vertex.push_back(Element(node, i));
		if (i != vertex.size())
		{///父节点存在
			++vertex[i].node->length;
		}
		this->count++;
	}

	//新建节点(new 分配空间)
	//virtual NodeType* Node_Create(std::string name, DataType element = 0)
	//{
	//	NodeType* node = new NodeType(name, element);
	//	return node;
	//}

public:
	//先根遍历
	void Tree_Traverse_PreOrder(NodeType* node)
	{
		static bool* visit_state = new bool[vertex.size()](false);
		int index = Index(node);
		if (!visit_state[index])
		{///未访问过时输出
			this->Tree_Visit_Name(node);
			visit_state[Index(node)] = true;
		}
		for (int i = 0; i < vertex.size(); ++i)
		{
			if (vertex[i].parent == Index(node))
				Tree_Traverse_PreOrder(vertex[i].node);
		}
	}
	//后根遍历
	void Tree_Traverse_PostOrder(NodeType* node)
	{
		static bool* visit_state = new bool[vertex.size()](false);
		int index = Index(node);
		for (int i = 0; i < vertex.size(); ++i)
		{
			if (vertex[i].parent == Index(node))
				Tree_Traverse_PostOrder(vertex[i].node);
		}
		if (!visit_state[index])
		{///未访问过时输出
			this->Tree_Visit_Name(node);
			visit_state[Index(node)] = true;
		}
	}
	//层次遍历
	void Tree_Traverse_LevelOrder(NodeType* node)
	{
		std::queue<int> queue;	///存节点下标
		static bool* visit_state = new bool[vertex.size()](false);

		queue.push(Index(this->root));
		while (!queue.empty())
		{
			int front = queue.front();
			for (int i = 0; i < vertex.size(); ++i)
			{
				if (vertex[i].parent == front)
					queue.push(i);
			}
			if (!visit_state[front])
			{
				this->Tree_Visit_Name(vertex[front].node);
				visit_state[front] = true;
			}
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