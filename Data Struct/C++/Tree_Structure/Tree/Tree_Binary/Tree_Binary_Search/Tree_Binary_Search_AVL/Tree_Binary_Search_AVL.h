#pragma once

#include <iostream>

#include "Node_Binary_Search_Balance.h"



template <typename DataType, typename NodeType = Node_Binary_Search_Balance<DataType>>
class Tree_Binary_Search_AVL:public Tree_Binary_Search<DataType,NodeType>
{
public:
	//Node_Binary_Search_Balance<DataType>* root;
	//int count;
public:
	Tree_Binary_Search_AVL() :Tree_Binary_Search<DataType, NodeType>() {};
	Tree_Binary_Search_AVL(NodeType* root) :Tree_Binary_Search<DataType, NodeType>(root) {};
	~Tree_Binary_Search_AVL()
	{///自下而上递归销毁节点
		std::cout << "删除二叉树树节点个数:" << this->count << std::endl;
		if (this->root)
			Destroy_SubTree(this->root);
	}

private:
	void Destroy_SubTree(Node_Binary_Search_Balance<DataType>* node)
	{
		if (node)
		{
			Destroy_SubTree(node->left);
			Destroy_SubTree(node->right);
			std::cout << node->element << " ";
			delete node;
			this->count--;
		}
	}
	int maxnode(int a, int b)
	{
		return (a > b) ? a : b;
	}
	int hightnode(Node_Binary_Search_Balance<DataType>* node)
	{
		if (node == NULL)
			return 0;
		return node->height;
	}
	int getbalance(Node_Binary_Search_Balance<DataType>* node)
	{
		if (!node)
			return 0;
		else
		{
			int l = hightnode(node->left);
			int r = hightnode(node->right);
			return l - r;
		}
	}
	//左旋(以当前节点为子树根)
	Node_Binary_Search_Balance<DataType>* Rotate_Left(Node_Binary_Search_Balance<DataType>* node)
	{
		//Node_Binary_Search_Balance<DataType>* temp = node->right;
		//node->right = temp->left;
		//temp->right = node;
		//node->height = maxnode(hightnode(node->left), hightnode(node->right)) + 1;
		//temp->height = maxnode(hightnode(temp->left), hightnode(node->right)) + 1;
		//return temp;
		Node_Binary_Search_Balance<DataType>* temp = node->right;
		node->right = temp->left;
		temp->left = node;
		node->height = maxnode(hightnode(node->left), hightnode(node->right)) + 1;
		temp->height = maxnode(hightnode(temp->left), hightnode(node->right)) + 1;
		return temp;
	}
	//右旋(以当前节点为子树根)
	Node_Binary_Search_Balance<DataType>* Rotate_Right(Node_Binary_Search_Balance<DataType>* node)
	{
		Node_Binary_Search_Balance<DataType>* temp = node->left;
		node->left = temp->right;
		temp->right = node;
		temp->height = maxnode(hightnode(temp->left), hightnode(node->right)) + 1;
		node->height = maxnode(hightnode(node->left), hightnode(node->right)) + 1;
		return temp;
	}
	Node_Binary_Search_Balance<DataType>* node_insert(Node_Binary_Search_Balance<DataType>* node, DataType element)
	{
		if (!node)
		{///出口1，找到位置并创建节点插入树
			this->count++;
			return this->Node_Create(std::to_string(element), element);
		}
		else///递
		{///寻找插入节点的空位置
			if (element < node->element)
				node->left = node_insert(node->left, element);
			if (element > node->element)
				node->right = node_insert(node->right, element);
		}
	

		///回归时同步更新子树根高度(上一层的节点高度)
		node->height = 1 + maxnode(hightnode(node->left), hightnode(node->right));
		///	根据平衡因子旋转
		/// 从上到下[第一个失衡节点][第二个失衡节点]
		///	LL->R
		///	RR->L
		///	LR->LR
		///	RL->RL
		int balance = getbalance(node);///计算平衡因子，调整子树(递归实现从下至上)
		if (balance>1)
		{//L重
			if (element < node->left->element)//L重
				return Rotate_Right(node);//LL右旋
			if (element > node->left->element)//R重
			{//LR
				node->left = Rotate_Left(node->left);//先左旋子树
				return Rotate_Right(node);//再整体右旋
			}
		}
		if (balance < -1)
		{//R重
			if (element > node->right->element)//R重
				return Rotate_Left(node);//RR左旋
			if (element < node->right->element)//L重
			{//RL
				node->right = Rotate_Right(node->left);//先右旋子树
				return Rotate_Left(node);//再整体左旋
			}
		}
		return node;///出口2，元素已存在，或平衡完毕后
	}
	void node_replace(Node_Binary_Search_Balance<DataType>* replace_target, Node_Binary_Search_Balance<DataType>* replace_source)
	{
		try
		{
			if (!replace_target || !replace_source)
				throw std::exception("Node is not exist");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}
		replace_target->name = replace_source->name;
		replace_target->element = replace_source->element;
	}
	Node_Binary_Search_Balance<DataType>* BinaryTree_AVL_Delete(Node_Binary_Search_Balance<DataType>* node, DataType data)
	{
		/// <summary>
		/// 删除同二叉搜索树，用逻辑前驱或后继代替，
		/// 删除完后，回归的同时更新平衡因子并调整
		/// </summary>
		/// <param name="tree"></param>
		/// <param name="node"></param>
		/// <param name="data"></param>
		/// <returns></returns>
		Node_Binary_Search_Balance<DataType>* temp;
		if (!node)///递归出口，目标节点不存在，直接回归退出
			return node;
		/// 递 寻找目标节点
		if (data < node->element)
			node->left = BinaryTree_AVL_Delete(node->left, data);
		else if (data > node->element)
			node->right = BinaryTree_AVL_Delete(node->right, data);
		else
		{///找到目标节点，删除并调整
			if (node->left==NULL || node->right==NULL)
			{///单子树用孩子代替
				temp = (node->left) ?
					node->left : node->right;
				if (!temp)
				{
					temp = node;
					node = nullptr;
				}
				else
				{//temp复制给node
					node->element = temp->element;
					node->left = temp->left;
					node->right = temp->right;
					node->height = temp->height;
				}
				delete temp;
				this->count--;
			}
			else
			{///删除节点左右孩子都存在,用逻辑前驱代替
				temp = node->left;
				while (temp->right)
					temp = temp->right;//找到逻辑前驱
				node_replace(node, temp);//用逻辑后继替换
				node->left = BinaryTree_AVL_Delete( node->left, temp->element);//替换后删除替换的节点
			}
		}

		/// 回归时同步平衡调整，同插入平衡化
		if (!node)
			return node;

		///
		node->height = 1 + maxnode(hightnode(node->left), hightnode(node->right));
		int balance = getbalance(node);///计算平衡因子，调整子树(递归实现从下至上)
		if (balance > 1)
		{//L重
			if (getbalance(node->left) < 0)
				node->left = Rotate_Left(node->left);
			return Rotate_Right(node);
		}
		if (balance < -1)
		{//R重
			if (getbalance(node->right) > 0)
				node->left = Rotate_Left(node->right);
			return Rotate_Left(node);
		}
		return node;///出口2
	}
public:
	// 插入AVL节点，在平衡二叉树tree中，双亲为parenr的[左/右]位置,递归过程中同步实现平衡化
	void Element_Insert(DataType data)
	{
		this->root = node_insert(this->root, data);
	}

	//删除平衡二叉树tree中元素值为data的节点，同步平衡
	void Element_Delete(DataType data)
	{
		BinaryTree_AVL_Delete(this->Tree_GetRoot(), data);
	}

};



