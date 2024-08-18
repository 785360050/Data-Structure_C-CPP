#pragma once

#include <iostream>

template <typename DataType, typename NodeType>
class Tree_Normal
{
protected:
	NodeType *root; /// 根节点指针
	int branch;		/// 分叉数量上限
	int count;		/// 节点总数

public:
	Tree_Normal(int branch)
		: branch(branch), count(0), root(nullptr) {};
	virtual ~Tree_Normal() = default;

protected:
	bool Tree_CheckEmpty() const
	{
		return count == 0 ? true : false;
	}
	// 访问节点名
	void Tree_Visit_Name(NodeType *node)
	{
		if (node)
			std::cout << node->name << ' ';
	}
	virtual void Clear(NodeType *node) = 0;
	virtual int Deep(NodeType *node) = 0;
	virtual NodeType *Parent(NodeType *node, std::string name) = 0;

public:
	virtual NodeType *Tree_GetRoot() = 0;
	virtual NodeType *Node_Create(std::string name, DataType element = 0)
	{
		NodeType *node = new NodeType(name, element);
		return node;
	}
	/// 只能在初始化的时候使用
	virtual void Tree_Set_Root(NodeType *root) = 0;
	virtual void Node_Insert(NodeType *node, NodeType *parent, int position) = 0;

	/// ============================================================================================================
	/// 高阶树的遍历算法同二叉树，可以递归也可以用栈
	/// 具体可参考LeetCode 589 590。与子节点的存储有关
	/// ============================================================================================================
	// 先根遍历 = 二叉树先序遍历
	virtual void Tree_Traverse_PreOrder(NodeType *node) = 0;
	// 后根遍历 = 二叉树中序遍历
	virtual void Tree_Traverse_PostOrder(NodeType *node) = 0;
	// 层次遍历
	virtual void Tree_Traverse_LevelOrder(NodeType *node) = 0;
	virtual void Tree_Show() = 0;
	virtual int Tree_GetDepth() = 0;
};

namespace Logic
{
	template <typename DataType, typename NodeType, int branch> // 分叉数量上限
	class Tree_Normal
	{
	protected:
		NodeType *root; /// 根节点指针
		int count;		/// 节点总数

	public:
		Tree_Normal() : count(0), root(nullptr) {};
		virtual ~Tree_Normal() = default;

	protected:
		constexpr bool Is_Empty() { return count; }

		virtual void Clear(NodeType *node) = 0;
		virtual int Get_Depth(NodeType *node) = 0;
		// virtual int Deep(NodeType *node) = 0;

	public:
		virtual NodeType *Get_Root() { return root; }
		virtual void Set_Root(NodeType *root) { this->root = root; }
		virtual NodeType *Node_Create(std::string name, DataType element = DataType{}) { return new NodeType(name, element); }
		/// 只能在初始化的时候使用
		virtual void Node_Insert(NodeType *node, NodeType *parent, int position) = 0;

		/// ============================================================================================================
		/// 高阶树的遍历算法同二叉树，可以递归也可以用栈
		/// 具体可参考LeetCode 589 590。与子节点的存储有关
		/// ============================================================================================================
		// 访问节点名
		void Tree_Visit_Name(NodeType *node)
		{
			if (node)
				std::cout << node->name << ' ';
		}
		// 先根遍历 = 二叉树先序遍历
		virtual void Traverse_PreOrder(NodeType *node) = 0;
		// 后根遍历 = 二叉树中序遍历
		virtual void Traverse_PostOrder(NodeType *node) = 0;
		// 层次遍历
		virtual void Traverse_LevelOrder(NodeType *node) = 0;
		virtual void Show() = 0;
	};
}
