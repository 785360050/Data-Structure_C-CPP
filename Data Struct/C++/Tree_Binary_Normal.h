#pragma once




#include <iostream>

#include "Tree_Binary_ADT.h"
#include "Liner_Queue_Sequential.h"


enum Direction { left = 1, right = 2 };

template <typename DataType>
struct Node_BinaryTree:public TreeNode<DataType>
{
	Node_BinaryTree* left;
	Node_BinaryTree* right;
public:
	void Init(std::string name , DataType element=0 )
	{
		this->name = name;
		this->element = element;
		left = right = nullptr;
	}
};




template <typename DataType>
class Binary_Tree
{
private:
	Node_BinaryTree<DataType>* root;
	int count;

public:
	//初始化树头节点信息，栈维护
	Binary_Tree()
	{
		root = nullptr;
		count = 0;
	}
public:
	//初始化树(指定根节点)
	void Tree_Init(Node_BinaryTree<DataType>* node)
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
		count++;
	}
	//销毁树
	void Tree_Destroy() 
	{
		try
		{
			if (!root)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Tree Destroy Faild: Tree is not exists" << std::endl;
			return;
		}
		std::cout << "删除二叉树 树节点个数:" << count << std::endl
			<< "删除顺序为：";
		Destroy_SubTree(root);
		std::cout << std::endl;
	}
	//销毁子树
	//void Tree_Destroy_SubTree(Node_BinaryTree<DataType>* node)
	//{///需要更新父节点指针信息，未完成
	//	try
	//	{
	//		if (!root)
	//			throw 1;
	//	}
	//	catch (...)
	//	{
	//		std::cout << "Tree Destroy Faild: Tree is not exists" << std::endl;
	//		return;
	//	}
	//	std::cout << "删除二叉子树 树节点个数:" << count << std::endl
	//		<< "删除顺序为：";
	//	Destroy_SubTree(node);
	//	std::cout << std::endl;
	//
	//	//Node_BinaryTree<DataType>* parent = Node_GetParent(node);
	//	//parent->left = nullptr;
	//}


	//创建种类为TreeType的树
	//(普通树，二叉树，线索树，二叉搜索树，AVL树，并查集，红黑树)
	///void Tree_Create_Type() = 0;
	//清空树
	void Tree_Clear()
	{
		Clear(root);
	}
	//判断是否树空
	bool Tree_CheckEmpty()
	{
		if (count == 0)
			return true;
		return false;
	}
	//返回树深度
	int Tree_GetDepth()
	{
		return Deep(root);
	}
	//返回树根节点
	Node_BinaryTree<DataType>* Tree_GetRoot()
	{
		return root;
	}
	//显示树所有信息
	void Tree_Show()
	{
		std::cout << "当前子树节点总数: " << count << std::endl << "DLR: ";
		Tree_Traverse_PreOrder(root);
		std::cout << std::endl << "LDR: ";
		Tree_Traverse_InOrder(root);
		std::cout << std::endl;
	}
	//返回树中节点node的元素值
	void Node_GetElement(Node_BinaryTree<DataType>* node)
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
	void Node_SetElement(Node_BinaryTree<DataType>* node, DataType element)
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
	//返回节点node的双亲节点
	//Node_BinaryTree<DataType>* Node_GetParent(Node_BinaryTree<DataType>* node)
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
	void Node_Insert(Node_BinaryTree<DataType>* node, Node_BinaryTree<DataType>* parent, Direction pos)
	{
		pos == right ?
			parent->right = node : parent->left = node;
		count++;
	}

	//新建节点(new 分配空间)
	Node_BinaryTree<DataType>* Node_Create(std::string name,DataType element=0 )
	{
		Node_BinaryTree<DataType>* node = new Node_BinaryTree<DataType>;
		node->Init(name, element);
		return node;
	}
	//删除节点
	void Node_Delete(Node_BinaryTree<DataType>* node)
	{
		try
		{
			if (!node)
				throw 1;
		}
		catch (...)
		{
			std::cout << "Node Delete Failed: node is not exist" << std::endl;
			return;
		}
		delete node;
	}
	

public:
	//返回节点node的右孩子节点
	///void Node_GetChild_Right(Node_BinaryTree<DataType>* node) = 0;
	//返回节点node的左边兄弟节点
	///void Node_GetSibling_Left(Node_BinaryTree<DataType>* node) = 0;
	//前序遍历二叉树	DLR
	void Tree_Traverse_PreOrder(Node_BinaryTree<DataType>* node)
	{
		if (node)
		{
			Tree_Visit_Name(node);
			Tree_Traverse_PreOrder(node->left);
			Tree_Traverse_PreOrder(node->right);
		}
	}
	//前序遍历二叉树	LDR
	void Tree_Traverse_InOrder(Node_BinaryTree<DataType>* node)
	{
		if (node)
		{
			Tree_Traverse_InOrder(node->left);
			Tree_Visit_Name(node);
			Tree_Traverse_InOrder(node->right);
		}
	}
	//前序遍历二叉树	LRD
	void Tree_Traverse_PostOrder(Node_BinaryTree<DataType>* node)
	{
		if (node)
		{
			Tree_Traverse_PostOrder(node->left);
			Tree_Traverse_PostOrder(node->right);
			Tree_Visit_Name(node);
		}
	}
	//层次遍历二叉树
	void Tree_Traverse_LevelOrder(Node_BinaryTree<DataType>* node)
	{///队列实现层次遍历
		Sequence_Queue<Node_BinaryTree<DataType>> q;//todo
		q.Queue_Init(count);
		q.Element_Enqueue(root);
		int length = q.Queue_Length();
		Node_BinaryTree<DataType>* v;
		while (length > 0)
		{
			v = q.Element_Dequeue();
			Tree_Visit_Name(v);
			if (v->left)
				q.Element_Enqueue(v->left);
			if (v->right)
				q.Element_Enqueue(v->right);
		}
		q.Queue_Destroy();
	}
	//访问节点名
	void Tree_Visit_Name(Node_BinaryTree<DataType>* node)
	{
		if (node)
		{
			std::cout << node->name << ' ';
			//std::cout << '[' << node->name << ':' << node->element << "] ";
		}
	}

private:
	//销毁子树
	void Destroy_SubTree(Node_BinaryTree<DataType>* node)
	{
		if (!node)
			return;
		Destroy_SubTree(node->left);
		Destroy_SubTree(node->right);
		std::cout << node->name << " ";
		delete node;
		count--;
	}
	//重置子树所有元素为0
	void Clear(Node_BinaryTree<DataType>* node)
	{
		if (node)
		{
			node->element = 0;
			Clear(node->left);
			Clear(node->right);
		}
	}
	int Deep(Node_BinaryTree<DataType>* node)
	{
		if (!node)
			return 0;
		else
		{
			int deep_left, deep_right = 0;
			deep_left = Deep(node->left);
			deep_right = Deep(node->right);
			if (deep_left > deep_right)
				return ++deep_left;
			else
				return ++deep_right;
		}

	}

	//返回节点名为name的父节点
	//Node_BinaryTree<DataType>* Parent(Node_BinaryTree<DataType>* node, std::string name)
	//{
	//	Node_BinaryTree<DataType>* n = root;
	//	Node_BinaryTree<DataType>* parent;
	//	if (n->left->name == name || n->right->name == name)
	//		return n;
	//	if (n->left == NULL && n->right == NULL)
	//		return NULL;
	//	parent = Parent(n->left,name);
	//	if (!parent)
	//		parent = Parent(n->right,name);
	//	if (parent == NULL)
	//	{
	//		std::cout << "Parent Not Found!" << std::endl;
	//		return NULL;
	//	}
	//	return parent;
	//	
	//}

};






/*

//二叉树函数

void BinaryTree_Traversal_Preorder_NoneRecursion(TNode* node)
{
	/// <summary>
	/// 利用顺序栈实现递归特性，递归在栈上分配空间，非递归的栈在堆上分配空间
	/// DLR
	/// 从树根入栈开始循环
	/// 每次出栈并访问节点，将RL入栈(为保证出栈先L再R，所以入栈先R再L)
	/// 栈空为止
	/// 销毁顺序栈
	/// </summary>
	/// <param name="node"></param>
	TNode* visit;
	if (node)
	{
		TStack* stack = TStack_Init();
		TStack_Push(stack, node);
		while (stack->top > 0)
		{
			visit = TStack_Pop(stack);
			BinaryTree_Visit(visit);
			if (visit->right)
				TStack_Push(stack, visit->right);
			if (visit->left)
				TStack_Push(stack, visit->left);
		}
		TStack_Destroy(stack);
	}
}

void BinaryTree_Traversal_Inorder_NonRecursive(TNode* node)
{
	/// <summary>
	/// 利用顺序栈实现递归特性，递归在栈上分配空间，非递归的栈在堆上分配空间
	/// LDR
	/// 树根入队 开始循环
	/// 每次移动至L并入栈，直到L为空时出栈并访问(出双亲节点)，再移动到R并入栈(双亲的R)
	/// </summary>
	/// <param name="node"></param>
	if (node)
	{
		TNode* n = node;
		TStack* stack = TStack_Init();
		while (stack->top > 0 || n)
		{
			if (n)
			{
				TStack_Push(stack, n);
				n = n->left;
			}
			else
			{
				TNode* v = TStack_Pop(stack);
				BinaryTree_Visit(v);
				n = v->right;
			}
		}
		TStack_Destroy(stack);
	}
}

void BinaryTree_Traversal_Postorder_NonRecursive(TNode* node)
{
	/// <summary>
	/// 利用两个栈实现递归特性，s1记录每个子树的头节点，s2记录头节点的左右孩子
	/// 树根节点先入栈s1
	/// 每次从s1出栈并压入s2栈,同时压入s1该节点的先L后R节点(为保证s2出栈先L后R再D，s1应该先L后R压入)
	/// 直到s1为空时，所有双亲节点(即所有节点)都压入s2
	/// 此时s2出栈时已经保证先L后R再D，依次出栈并访问
	/// </summary>
	/// <param name="node"></param>
	TStack* s1 = TStack_Init();
	TStack* s2 = TStack_Init();
	TNode* n;
	TStack_Push(s1, node);
	while (s1->top > 0)
	{
		n = TStack_Pop(s1);
		TStack_Push(s2, n);
		if (n->left)
			TStack_Push(s1, n->left);
		if (n->right)
			TStack_Push(s1, n->right);
	}
	while (s2->top > 0)
		BinaryTree_Visit(TStack_Pop(s2));
	TStack_Destroy(s1);
	TStack_Destroy(s2);
}
*/
