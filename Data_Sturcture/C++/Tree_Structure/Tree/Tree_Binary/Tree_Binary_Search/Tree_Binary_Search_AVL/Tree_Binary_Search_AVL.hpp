#pragma once

#include <iostream>

#include "Node_Binary_Search_Balance.h"



template <typename DataType, typename KeyType = int, typename NodeType = Node_Binary_Search_Balance<DataType, KeyType>>
class Tree_Binary_Search_AVL :public Tree_Binary_Search<DataType, KeyType, NodeType>
{
public:
	Tree_Binary_Search_AVL() :Tree_Binary_Search<DataType, KeyType, NodeType>() {};
	~Tree_Binary_Search_AVL() = default;
private:
	int MaxHeight(int a, int b)
	{return (a > b) ? a : b;}
	//左旋(以当前节点为子树根)
	NodeType* Rotate_Left(NodeType* node)
	{
		//NodeType* temp = node->right;
		//node->right = temp->left;
		//temp->right = node;
		//node->height = maxnode(hightnode(node->left), hightnode(node->right)) + 1;
		//temp->height = maxnode(hightnode(temp->left), hightnode(node->right)) + 1;
		//return temp;
		NodeType* temp = node->right;
		node->right = temp->left;
		temp->left = node;
		node->height = 1 + MaxHeight(node->left->Height(), node->right->Height());
		temp->height = 1 + MaxHeight(temp->left->Height(), temp->right->Height());
		return temp;
	}
	//右旋(以当前节点为子树根)
	NodeType* Rotate_Right(NodeType* node)
	{
		NodeType* temp = node->left;
		node->left = temp->right;
		temp->right = node;
		temp->height = 1 + MaxHeight(temp->left->Height(), temp->right->Height());
		node->height = 1 + MaxHeight(node->left->Height(), node->right->Height());
		return temp;
	}
	NodeType* node_insert(NodeType* node, KeyType key, DataType data = NULL)
	{
		if (!node)
		{///出口1，找到位置并创建节点插入树
			this->count++;
			return this->Node_Create(key, std::to_string(key), data);
		}
		else///递
		{///寻找插入节点的空位置
			if (key < node->key)
				node->left = node_insert(node->left, key, data);
			if (key > node->key)
				node->right = node_insert(node->right, key, data);
		}
	

		///回归时同步更新子树根高度(上一层的节点高度)
		node->height = 1 + MaxHeight(node->left->Height(), node->right->Height());
		///	根据平衡因子旋转
		/// 从上到下[第一个失衡节点][第二个失衡节点]
		///	LL->R
		///	RR->L
		///	LR->LR
		///	RL->RL
		int balance = node->Balance();///计算平衡因子，调整子树(递归实现从下至上)
		if (balance>1)
		{//L重
			if (key < node->left->key)//L重
				return Rotate_Right(node);//LL右旋
			if (key > node->left->key)//R重
			{//LR
				node->left = Rotate_Left(node->left);//先左旋子树
				return Rotate_Right(node);//再整体右旋
			}
		}
		if (balance < -1)
		{//R重
			if (key > node->right->key)//R重
				return Rotate_Left(node);//RR左旋
			if (key < node->right->key)//L重
			{//RL
				node->right = Rotate_Right(node->left);//先右旋子树
				return Rotate_Left(node);//再整体左旋
			}
		}
		return node;///出口2，元素已存在，或平衡完毕后
	}
	NodeType* node_delete(NodeType* node, KeyType key)
	{
		/// <summary>
		/// 删除同二叉搜索树，用逻辑前驱或后继代替，
		/// 删除完后，回归的同时更新平衡因子并调整
		/// </summary>
		/// <param name="tree"></param>
		/// <param name="node"></param>
		/// <param name="data"></param>
		/// <returns></returns>
		NodeType* temp;
		if (!node)///递归出口，目标节点不存在，直接回归退出
			return node;
		/// 递 寻找目标节点
		if (key < node->key)
			node->left = node_delete(node->left, key);
		else if (key > node->key)
			node->right = node_delete(node->right, key);
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
					node->replace_by(temp);
					//node->element = temp->element;
					node->height = temp->height;
					node->left = temp->left;
					node->right = temp->right;
				}
				delete temp;
				this->count--;
			}
			else
			{///删除节点左右孩子都存在,用逻辑前驱代替
				temp = this->Element_Precursor(node);//找到逻辑前驱
				node->replace_by(temp);//用逻辑前驱替换
				node->left = node_delete(node->left, temp->key);//替换后删除替换的节点
			}
		}

		/// 回归时同步平衡调整，同插入平衡化
		if (!node)
			return node;

		///
		node->height = 1 + MaxHeight(node->left->Height(), node->right->Height());
		int balance = node->Balance();///计算平衡因子，调整子树(递归实现从下至上)
		if (balance > 1)
		{///L重
			if (node->left->Balance() < 0)		///LR = Rotate_Left + Rotate_Right
				node->left = Rotate_Left(node->left);
			return Rotate_Right(node);			///LL = Rotate_Right
		}
		if (balance < -1)
		{///R重
			if (node->right->Balance() > 0)		///RL = Rotate_Right + Rotate_Left
				node->right = Rotate_Right(node->right);
			return Rotate_Left(node);			///RR = Rotate_Left
		}
		return node;///出口2
	}
public:
	// 插入AVL节点，在平衡二叉树tree中，双亲为parenr的[左/右]位置,递归过程中同步实现平衡化
	void Element_Insert(KeyType key, DataType element = NULL)
	{
		this->root = node_insert(this->root, key, element);
	}

	//删除平衡二叉树tree中元素值为data的节点，同步平衡
	void Element_Delete(KeyType key)
	{
		node_delete(this->root, key);
	}
};



