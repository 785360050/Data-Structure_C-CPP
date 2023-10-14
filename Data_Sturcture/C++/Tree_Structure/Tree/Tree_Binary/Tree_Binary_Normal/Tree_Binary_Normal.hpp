#pragma once


//TODO: Individual Stack,Queue

#include <iostream>
#include <queue>
#include <stack>
#include "../Tree_Binary_ADT.hpp"
//#include "Linear_Queue_Sequential.h"
//#include "Linear_Stack_Sequential.h"

#include "../Node_BinaryTree.hpp"
#include "../Tree_Binary.hpp"




template <typename DataType, typename NodeType = Node_BinaryTree<DataType>>
class Tree_Binary_Normal:public Tree_Binary<DataType,NodeType>
{
public:
	//初始化树头节点信息，栈维护
	Tree_Binary_Normal()
		:Tree_Binary<DataType, NodeType>() {};
	//初始化树(指定根节点)
	//Tree_Binary_Normal(NodeType* node)
	//{
	//	try
	//	{
	//		if (!node)
	//			throw 1;
	//	}
	//	catch (...)
	//	{
	//		std::cout << "this->root Init Faild: node is not exists" << std::endl;
	//		return;
	//	}
	//	this->root = node;
	//	++this->count;
	//}
	~Tree_Binary_Normal()
	{
		if (!this->root)
			return;
		std::cout << "删除二叉树 树节点个数:" << this->count << std::endl
			<< "删除顺序为：";
		this->Destroy_SubTree(this->root);
		std::cout << std::endl << "Binary_Tree Destroyed" << std::endl;
	}
private:
	//销毁子树
	void Destroy_SubTree(NodeType* node) override
	{
		if (!node)
			return;
		Destroy_SubTree(node->left);
		Destroy_SubTree(node->right);
		std::cout << node->name << " ";
		delete node;
		--this->count;
	}
	//重置子树所有元素为0
	//void Clear(NodeType* node)
	//{
	//	if (node)
	//	{
	//		node->element = 0;
	//		Clear(node->left);
	//		Clear(node->right);
	//	}
	//}
	int Deep(NodeType* node)
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
	//清空树
	//void Tree_Clear()
	//{
	//	Clear(this->root);
	//}
	////判断是否树空
	//返回树深度
	int Tree_GetDepth()
	{
		return Deep(this->root);
	}
	//显示树所有信息
	void Tree_Show() override
	{
		std::cout << "当前子树节点总数: " << this->count << std::endl << "DLR: ";
		Tree_Traverse_PreOrder(this->root);
		std::cout << std::endl << "LDR: ";
		Tree_Traverse_InOrder(this->root);
		std::cout << std::endl;
	}
	//将树中节点node的元素值为element
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
	
	//将节点node作为第x个孩子插入到子树tree中
	virtual void Node_Insert(NodeType* node, NodeType* parent, Direction pos)
	{
		pos == right ?
			parent->right = node : parent->left = node;
		this->count++;
	}

public:
	//前序遍历二叉树	DLR
	virtual void Tree_Traverse_PreOrder(NodeType* node) override
	{
		if (node)
		{
			this->Node_Visit_Name(node);
			Tree_Traverse_PreOrder(node->left);
			Tree_Traverse_PreOrder(node->right);
		}
	}
	//前序遍历二叉树	DLR	非递归
	void Tree_Traverse_PreOrder_NoneRecursive(NodeType* node)
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

#define Standard_Stack	//标准库stack
//#define Individual_Stack	//自制stack

#ifdef Standard_Stack
		std::stack<NodeType* > s;
		NodeType* n;
		s.push(node);
		while (!s.empty())
		{
			n = s.top();
			s.pop();
			this->Node_Visit_Name(n);
			if (n->right)
				s.push(n->right);
			if (n->left)
				s.push(n->left);
		}
		std::cout << std::endl;
#endif // Standard_Stack
#ifdef Individual_Stack
		Sequence_Stack<NodeType* >* s = new Sequence_Stack<NodeType* >;
		NodeType* n;
		s->Stack_Init(this->count);
		s->Element_Push(node);
		while (!s->Stack_CheckEmpty())
		{
			n = s->Element_Pop();
			Tree_Visit_Name(n);
			if (n->right)
				s->Element_Push(n->right);
			if (n->left)
				s->Element_Push(n->left);
		}
		s->Stack_Destroy();
		std::cout << std::endl;
#endif // Individual_Stack
	}
	//前序遍历二叉树	LDR
	virtual void Tree_Traverse_InOrder(NodeType* node) override
	{
		if (node)
		{
			Tree_Traverse_InOrder(node->left);
			this->Node_Visit_Name(node);
			Tree_Traverse_InOrder(node->right);
		}
	}
	void Tree_Traverse_InOrder_NoneRecursive(NodeType* node)
	{
		/// <summary>
		/// 利用顺序栈实现递归特性，递归在栈上分配空间，非递归的栈在堆上分配空间
		/// LDR
		/// 树根入队 开始循环
		/// 每次移动至L并入栈，直到L为空时出栈并访问(出双亲节点)，再移动到R并入栈(双亲的R)
		/// </summary>
		/// <param name="node"></param>
#define Standard_Stack	//标准库stack
//#define Individual_Stack	//自制stack

#ifdef Standard_Stack
		std::stack< NodeType* > s;
		NodeType* n = node;
		while (!s.empty() || n)
		{
			if (n)
			{
				s.push(n);
				n = n->left;
			}
			else
			{
				NodeType* temp = s.top();
				s.pop();
				this->Node_Visit_Name(temp);
				n = temp->right;
			}
		}
#endif // Standard_Stack
#ifdef Individual_Stack
		Sequence_Stack<NodeType*>* s = new Sequence_Stack< NodeType* >;
		s->Stack_Init(this->count);
		NodeType* n = node;
		while (!s->Stack_CheckEmpty() || n)
		{
			if (n)
			{
				s->Element_Push(n);
				n = n->left;
			}
			else
			{
				NodeType* temp = s->Element_Pop();
				Tree_Visit_Name(temp);
				n = temp->right;
			}
		}
		s->Stack_Destroy();
#endif // Individual_Stack

	}

	//前序遍历二叉树	LRD
	virtual void Tree_Traverse_PostOrder(NodeType* node) override
	{
		if (node)
		{
			Tree_Traverse_PostOrder(node->left);
			Tree_Traverse_PostOrder(node->right);
			this->Node_Visit_Name(node);
		}
	}
	//前序遍历二叉树	LRD 非递归
	void Tree_Traverse_PostOrder_NoneRecursive(NodeType* node)
	{
		/// <summary>
		/// 利用两个栈实现递归特性，s1记录每个子树的头节点，s2记录头节点的左右孩子
		/// 树根节点先入栈s1
		/// 每次从s1出栈并压入s2栈,同时压入s1该节点的先L后R节点(为保证s2出栈先L后R再D，s1应该先L后R压入)
		/// 直到s1为空时，所有双亲节点(即所有节点)都压入s2
		/// 此时s2出栈时已经保证先L后R再D，依次出栈并访问
		/// </summary>
		/// <param name="node"></param>
#define Standard_Stack	//标准库stack
//#define Individual_Stack	//自制stack
		
#ifdef Standard_Stack
		std::stack<NodeType*> s1;
		std::stack<NodeType*> s2;
		NodeType* n;
		s1.push(node);
		while (!s1.empty())
		{
			n = s1.top();
			s1.pop();
			s2.push(n);
			if (n->left)
				s1.push(n->left);
			if (n->right)
				s1.push(n->right);
		}
		while (!s2.empty())
		{
			n = s2.top();
			s2.pop();
			this->Node_Visit_Name(n);
		}
#endif // Standard_Stack
#ifdef Individual_Stack
		Sequence_Stack<NodeType* >* s1 = new Sequence_Stack<NodeType* >;
		Sequence_Stack<NodeType* >* s2 = new Sequence_Stack<NodeType* >;
		s1->Stack_Init(this->count);
		s2->Stack_Init(this->count);
		NodeType* n;
		s1->Element_Push(node);

		while (!s1->Stack_CheckEmpty())
		{
			n = s1->Element_Pop();
			s2->Element_Push(n);
			if (n->left)
				s1->Element_Push(n->left);
			if (n->right)
				s1->Element_Push(n->right);
		}
		while (!s2->Stack_CheckEmpty())
		{
			n = s2->Element_Pop();
			Tree_Visit_Name(n);
		}
		s1->Stack_Destroy();
		s2->Stack_Destroy();

#endif // Individual_Stack
		std::cout << std::endl;
	}
	//层次遍历二叉树
	virtual void Tree_Traverse_LevelOrder(NodeType* node) override
	{///队列实现层次遍历
#define Standard_Queue	///标准模板库实现
//#define Queue	///自制的队列实现

#ifdef Queue
		Sequence_Queue<NodeType* >* q = new Sequence_Queue<NodeType* >;
		q->Queue_Init(this->count);
		q->Element_Enqueue(this->root);
		int length = q->Queue_Length();
		NodeType* v;
		while ( q->Queue_Length() > 0)
		{
			v = q->Element_Dequeue();
			Tree_Visit_Name(v);
			if (v->left)
				q->Element_Enqueue(v->left);
			if (v->right)
				q->Element_Enqueue(v->right);
		}
		q->Queue_Destroy();
#endif // Queue

#ifdef Standard_Queue	///std::queue
		std::queue<NodeType* > q;
		q.push(this->root);
		NodeType* v;
		while (!q.empty())
		{
			v = q.front();
			q.pop();
			this->Node_Visit_Name(v);
			if (v->left)
				q.push(v->left);
			if (v->right)
				q.push(v->right);
		}
#endif
	}

};



