#pragma once

//#include "../Tree.h"
#include <vector>

enum Direction { left = 1, right = 2 };

template <typename DataType,typename NodeType>
class Tree_Binary
{
protected:
	NodeType* root;
	int count;

public:
	Tree_Binary() :root(nullptr), count(0) {};
	virtual ~Tree_Binary() = default;
protected:
	//重置子树所有元素为0
	//virtual void Clear(NodeType* node);
	//virtual int Deep(NodeType* node);
	//返回节点名为name的父节点
	//virtual NodeType* Parent(NodeType* node, std::string name)
	//{
	//	NodeType* n = root;
	//	NodeType* parent;
	//	if (n->left->name == name || n->right->name == name)
	//		return n;
	//	if (n->left == NULL && n->right == NULL)
	//		return NULL;
	//	parent = Parent(n->left, name);
	//	if (!parent)
	//		parent = Parent(n->right, name);
	//	if (parent == NULL)
	//	{
	//		std::cout << "Parent Not Found!" << std::endl;
	//		return NULL;
	//	}
	//	return parent;
	//}
	//访问节点名
	void Node_Visit_Name(NodeType* node)
	{
		if (node)
		{std::cout << node->name << ' '; }
	}
	virtual void Destroy_SubTree(NodeType* node) = 0;
public:
	void Tree_Set_Root(NodeType* node)
	{
		try
		{
			if (!node)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Root Init Faild: node is not exists" << std::endl;
			return;
		}
		root = node;
		++count;
	}
	bool Tree_CheckEmpty() const
	{return count == 0 ? true : false;}
	//返回树深度
	//virtual int Tree_GetDepth()
	//{return Deep(root);}
	//返回树根节点
	virtual NodeType* Tree_GetRoot()
	{return root;}
	//显示树所有信息
	virtual void Tree_Show() = 0;

	//将节点node作为第x个孩子插入到子树tree中
	virtual void Node_Insert(NodeType* node, NodeType* parent, Direction pos) = 0;

	//新建节点(new 分配空间)
	virtual NodeType* Node_Create(std::string name, DataType element = NULL)
	{return new NodeType(name, element);}

public:
	//前序遍历二叉树	DLR
	virtual void Tree_Traverse_PreOrder(NodeType* node) = 0;
	//前序遍历二叉树	LDR
	virtual void Tree_Traverse_InOrder(NodeType* node) = 0;
	//前序遍历二叉树	LRD
	virtual void Tree_Traverse_PostOrder(NodeType* node) = 0;
	//层次遍历二叉树
	virtual void Tree_Traverse_LevelOrder(NodeType* node) = 0;

private: ///构造二叉树[先序+中序/后续+中序]
	//先序+中序构造子树
	NodeType* Build_Preorder
	(
		const std::vector<int>& preorder, const int& begin_preorder, const int& end_preorder,
		const std::vector<int>& inorder, const int& begin_inorder, const int& end_inorder
	)
	{ // 切割区间维持左闭右开[)
		if (begin_inorder > end_inorder || begin_preorder > end_preorder)
			throw std::runtime_error("Index Illigal");
		if (begin_inorder == end_inorder)
			return nullptr;

		if (end_inorder - begin_inorder == 1)
			return Node_Create(std::to_string(preorder[begin_preorder]));

		NodeType* root = Node_Create(std::to_string(preorder[begin_preorder]));// 注意用begin_preorder 不要用0

		int index_root;
		for (index_root = begin_inorder; index_root < end_inorder; index_root++)
		{
			if (inorder[index_root] == preorder[begin_preorder])
				break;
		}

		///构造左子树
		// 切割中序数组
		int begin_inorder_left = begin_inorder;
		int end_inorder_left = index_root;
		// 切割前序数组
		int begin_preorder_left = begin_preorder + 1;
		int end_preorder_left = begin_preorder + 1 + index_root - begin_inorder; // 终止位置是起始位置加上中序左区间的大小size
		root->left = Build_Preorder(preorder, begin_preorder_left, end_preorder_left,
			inorder, begin_inorder_left, end_inorder_left);

		/// 构造右子树
		// 切割前序数组
		int begin_preorder_right = begin_preorder + 1 + (index_root - begin_inorder);
		int end_preorder_right = end_preorder;
		// 切割中序数组
		int begin_inorder_right = index_root + 1;
		int end_inorder_right = end_inorder;

		root->right = Build_Preorder(preorder, begin_preorder_right, end_preorder_right,
			inorder, begin_inorder_right, end_inorder_right);

		return root;
	}

	//后序+中序构造子树
	NodeType* Build_Postorder
	(
		const std::vector<DataType>& postorder, const int& begin_postorder, const int& end_postorder,
		const std::vector<DataType>& inorder, const int& begin_inorder, const int& end_inorder
	)
	{ // 坚持左开右闭：注意LRD时-1
		if (begin_inorder > end_inorder || begin_postorder > end_postorder)
			throw std::runtime_error("Index Illigal");
		if (begin_inorder == end_inorder)
			return nullptr;

		if (end_inorder - begin_inorder == 1)
			return Node_Create(std::to_string(postorder[end_postorder - 1]));

		NodeType* root = Node_Create(std::to_string(postorder[end_postorder - 1]));

		int index_root;
		for (index_root = begin_inorder; index_root < end_inorder; ++index_root)
			if (inorder[index_root] == postorder[end_postorder - 1])
				break;

		// 构造左子树
		int begin_postorder_left = begin_postorder;
		int end_postorder_left = begin_postorder + index_root - begin_inorder;
		int begin_inorder_left = begin_inorder;
		int end_inorder_left = index_root;

		root->left = Build_Postorder(postorder, begin_postorder_left, end_postorder_left,
			inorder, begin_inorder_left, end_inorder_left);

		// 构造右子树
		int begin_postorder_right = end_postorder_left;
		int end_postorder_right = end_postorder - 1;
		int begin_inorder_right = index_root + 1;
		int end_inorder_right = end_inorder;

		root->right = Build_Postorder(postorder, begin_postorder_right, end_postorder_right,
			inorder, begin_inorder_right, end_inorder_right);

		return root;
	}

public:
	//Preorder_or_Postorder指定pre_post_order为先序还是后续，true为先序
	void Tree_Build(const std::vector<DataType>& pre_post_order, const std::vector<DataType>& inorder,bool Preorder_or_Postorder)
	{
		try
		{
			if (inorder.size()!= pre_post_order.size())
				throw std::runtime_error("Traversal Vector Size Unequal");
			if (inorder.empty() || pre_post_order.empty())
				throw std::runtime_error("Traversal Vector Empty");
		}
		catch (const std::runtime_error& e)
		{
			std::cout << e.what() << std::endl;
		}

		this->count = inorder.size();
		// 维持左开又闭
		if (Preorder_or_Postorder)
			this->root = Build_Preorder(pre_post_order, 0, pre_post_order.size(),
				inorder, 0, inorder.size());
		else
			this->root = Build_Postorder(pre_post_order, 0, pre_post_order.size(),
				inorder, 0, inorder.size());
		
	}
};

