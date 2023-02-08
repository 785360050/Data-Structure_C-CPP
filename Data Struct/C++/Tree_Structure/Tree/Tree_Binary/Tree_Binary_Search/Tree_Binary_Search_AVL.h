#pragma once

#include <iostream>

#include "Tree_Binary_ADT.h"
#include "../Tree_Binary_Normal/Tree_Binary_Normal.h"

#include "../Node_BinaryTree.h"



template <typename DataType>
struct Node_Binary_Search_Balance
{
public:
	DataType element;
	std::string name;
	Node_Binary_Search_Balance<DataType>* left;
	Node_Binary_Search_Balance<DataType>* right;
	//当前子树高度
	int height;//节点的平衡因子=左子树高度-右子树高度
public:
	Node_Binary_Search_Balance(std::string name,DataType element=0)
		:element(element),name(name),left(nullptr),right(nullptr), height(1) {};
	int Get_Height() const
	{
		return height;
	}

};


//#include "Global Variables.h"

template <typename DataType>
class Tree_Binary_Search_AVL
{
public:
	Node_Binary_Search_Balance<DataType>* root;
	int count;
public:
	Tree_Binary_Search_AVL() :root{ nullptr }, count{ 0 } {};
	~Tree_Binary_Search_AVL()
	{///自下而上递归销毁节点
		std::cout << "删除二叉树树节点个数:" << count << std::endl;
		if (root)
			DeleteNode(root);
	}


private:
	void DeleteNode(Node_Binary_Search_Balance<DataType>* node)
	{
		if (node)
		{
			DeleteNode(node->left);
			DeleteNode(node->right);
			std::cout << node->element << " ";
			delete node;
			count--;
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
		Node_Binary_Search_Balance<DataType>* temp = node->right;
		node->right = temp->left;
		temp->right = node;
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
	Node_Binary_Search_Balance<DataType>* node_insert(Tree_Binary_Search_AVL<DataType>* tree, Node_Binary_Search_Balance<DataType>* node, DataType element)
	{
		if (!node)
		{///出口1，找到位置并创建节点插入树
			tree->count++;
			return BinaryTree_CreateNode_AVL(element);
		}
		else///递
		{///寻找插入节点的空位置
			if (element < node->element)
				node->left = node_insert(tree, node->left, element);
			if (element > node->element)
				node->right = node_insert(tree, node->right, element);
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
			if (element > node->right->element)//L重
				return Rotate_Left(node);//LL右旋
			if (element < node->right->element)//R重
			{//RL
				node->right = Rotate_Right(node->left);//先左旋子树
				return Rotate_Left(node);//再整体右旋
			}
		}
		return node;///出口2，元素已存在，或平衡完毕后
	}

public:
	Node_Binary_Search_Balance<DataType>* BinaryTree_CreateNode_AVL(DataType element)
	{
		return new Node_Binary_Search_Balance<DataType>(std::to_string(element),element);
	}
	// 插入AVL节点，在平衡二叉树tree中，双亲为parenr的[左/右]位置
	void BinaryTree_Insert_AVL(DataType data)
	{
		root = node_insert(this, root, data);
	}

	//访问AVL节点名
	void BinaryTree_Visit_AVL(Node_Binary_Search_Balance<DataType>* node)
	{
		if (node)
		{
			std::cout << node->name << " ";
		}
		else
		{
			std::cout << "TreeNode is not exist" << std::endl;
			return;
		}
	}
	// 中序遍历平衡二叉树
	void BinaryTree_Traversal_Inorder_AVL(Node_Binary_Search_Balance<DataType>* node)
	{
		if (node)
		{
			BinaryTree_Traversal_Inorder_AVL(node->left);//L
			BinaryTree_Visit_AVL(node);//D
			BinaryTree_Traversal_Inorder_AVL(node->right);//R
		}
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
		if (data > node->element)
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
				count--;
			}
			else
			{///删除节点左右孩子都存在,用逻辑前驱代替
				temp = node->left;
				while (temp->right)
					temp = temp->right;//找到逻辑前驱
				node->element = temp->element;//用逻辑后继替换
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
};

//template <typename DataType>
//class Tree_Binary_Search_AVL
//	//:public Binary_Tree_Search<DataType>
//{
//private:
//	int getbalance(Node_BinaryTree<DataType>* node)
//	{
//		if (!node)
//			return 0;
//		else
//		{
//			int l = hightnode(node->left);
//			int r = hightnode(node->right);
//			return l - r;
//		}
//	}
//	//左旋(以当前节点为子树根)
//	Node_Binary_Search_Balance<DataType>* Rotate_Left(Node_Binary_Search_Balance<DataType>* node)
//	{
//		Node_Binary_Search_Balance<DataType>* temp = node->right;
//		node->right = temp->left;
//		temp->right = node;
//		node->height = maxnode(hightnode(node->left), hightnode(node->right)) + 1;
//		temp->height = maxnode(hightnode(temp->left), hightnode(node->right)) + 1;
//		return temp;
//	}
//	//右旋(以当前节点为子树根)
//	Node_Binary_Search_Balance<DataType>* Rotate_Right(Node_Binary_Search_Balance<DataType>* node)
//	{
//		Node_Binary_Search_Balance<DataType>* temp = node->left;
//		node->left = temp->right;
//		temp->right = node;
//		temp->height = maxnode(hightnode(temp->left), hightnode(node->right)) + 1;
//		node->height = maxnode(hightnode(node->left), hightnode(node->right)) + 1;
//		return temp;
//	}
//	//Node_Binary_Search_Balance<DataType>* node_insert(Tree_Binary_Search_AVL<DataType>* tree, Node_Binary_Search_Balance<DataType>* node, DataType data);
//	Node_Binary_Search_Balance<DataType>* insertnode(Node_Binary_Search_Balance<DataType>* node, DataType data)
//	{
//		if (!node)
//		{///出口1，找到位置并创建节点插入树
//			++this->count;
//			return Node_Create(std::to_string(data));
//		}
//		else///递
//		{///寻找插入节点的空位置
//			if (data < node->element)
//				node->left = insertnode(node->left, data);
//			if (data > node->element)
//				node->right = insertnode(node->right, data);
//		}
//
//
//		///回归时同步更新子树根高度(上一层的节点高度)
//		node->height = 1 + maxnode(hightnode(node->left), hightnode(node->right));
//		///	根据平衡因子旋转
//		/// 从上到下[第一个失衡节点][第二个失衡节点]
//		///	LL->R
//		///	RR->L
//		///	LR->LR
//		///	RL->RL
//		int balance = getbalance(node);///计算平衡因子，调整子树(递归实现从下至上)
//		if (balance > 1)
//		{//L重
//			if (data < node->left->element)//L重
//				return Rotate_Right(node);//LL右旋
//			if (data > node->left->element)//R重
//			{//LR
//				node->left = Rotate_Left(node->left);//先左旋子树
//				return Rotate_Right(node);//再整体右旋
//			}
//		}
//		if (balance < -1)
//		{//R重
//			if (data > node->right->element)//L重
//				return Rotate_Left(node);//LL右旋
//			if (data < node->right->element)//R重
//			{//RL
//				node->right = Rotate_Right(node->left);//先左旋子树
//				return Rotate_Left(node);//再整体右旋
//			}
//		}
//		return node;///出口2，元素已存在，或平衡完毕后
//	}
//	int maxnode(int a, int b)
//	{
//		return (a > b) ? a : b;
//	}
//	int hightnode(Node_Binary_Search_Balance<DataType>* node)
//	{
//		if (node == NULL)
//			return 0;
//		return node->height;
//	}
//public:
//	BTree_AVL* BinaryTree_Init_Root_AVL()
//	{
//		BTree_AVL* tree = new BTree_AVL;
//		tree->root = nullptr;
//		tree->num = 0;
//		return tree;
//	}
//	static void DeleteNode(BTree_AVL* tree, AVLNode* node)
//	{
//		if (node)
//		{
//			DeleteNode(tree, node->left);
//			DeleteNode(tree, node->right);
//			std::cout << node->data << " ";
//			free(node);
//			tree->num--;
//		}
//	}
//	void BinaryTree_Destory(BTree_AVL* tree)
//	{///自下而上递归销毁节点
//		if (tree)
//		{
//			std::cout << "删除二叉树树节点个数:" << tree->num << std::endl;
//			if (tree->root)
//				DeleteNode(tree, tree->root);
//		}
//	}
//	Tree_Binary_Search_AVL() :Binary_Tree_Search<DataType>() {};
//	~Tree_Binary_Search_AVL() = default;
//
//
//public:
//	Node_Binary_Search_Balance<DataType>* Node_Create(std::string name, DataType element = 0)
//	{
//		//Node_Binary_Search_Balance<DataType>* node = 
//		//return node;
//		return new Node_Binary_Search_Balance<DataType>(std::to_string(element));
//	}
//
//	// 插入AVL节点，在平衡二叉树tree中，双亲为parenr的[左/右]位置
//	void Tree_Element_Insert(DataType data)
//	{
//		//Node_Binary_Search_Balance<DataType>* node = dynamic_cast<Node_Binary_Search_Balance<DataType>*>(this->root);
//		//this->root = insertnode(node, data);
//		this->root = insertnode(this->root, data);
//	}
//
//	Node_Binary_Search_Balance<DataType>* BinaryTree_AVL_Delete(Node_Binary_Search_Balance<DataType>* node, DataType data)
//	{
//		/// <summary>
//		/// 删除同二叉搜索树，用逻辑前驱或后继代替，
//		/// 删除完后，回归的同时更新平衡因子并调整
//		/// </summary>
//		/// <param name="tree"></param>
//		/// <param name="node"></param>
//		/// <param name="data"></param>
//		/// <returns></returns>
//		Node_Binary_Search_Balance<DataType>* temp;
//		if (!node)///递归出口，目标节点不存在，直接回归退出
//			return node;
//		/// 递 寻找目标节点
//		if (data < node->data)
//			node->left = BinaryTree_AVL_Delete(*this, node->left, data);
//		if (data > node->data)
//			node->right = BinaryTree_AVL_Delete(*this, node->right, data);
//		else
//		{///找到目标节点，删除并调整
//			if (node->left == NULL || node->right == NULL)
//			{///单子树用孩子代替
//				temp = (node->left) ?
//					node->left : node->right;
//				if (!temp)
//				{
//					temp = node;
//					node = nullptr;
//				}
//				else
//				{//temp复制给node
//					node->data = temp->data;
//					node->left = temp->left;
//					node->right = temp->right;
//					node->height = temp->height;
//				}
//				delete temp;
//				--this->count;
//			}
//			else
//			{///删除节点左右孩子都存在,用逻辑前驱代替
//				temp = node->left;
//				while (temp->right)
//					temp = temp->right;//找到逻辑前驱
//				node->data = temp->data;//用逻辑后继替换
//				node->left = BinaryTree_AVL_Delete(*this, node->left, temp->data);//替换后删除替换的节点
//			}
//		}
//
//		/// 回归时同步平衡调整，同插入平衡化
//		if (!node)
//			return node;
//
//		///
//		node->height = 1 + maxnode(hightnode(node->left), hightnode(node->right));
//		int balance = getbalance(node);///计算平衡因子，调整子树(递归实现从下至上)
//		if (balance > 1)
//		{//L重
//			if (getbalance(node->left) < 0)
//				node->left = Rotate_Left(node->left);
//			return Rotate_Right(node);
//		}
//		if (balance < -1)
//		{//R重
//			if (getbalance(node->right) > 0)
//				node->left = Rotate_Left(node->right);
//			return Rotate_Left(node);
//		}
//		return node;///出口2
//	}
//
//
//	//访问AVL节点名
//	void BinaryTree_Visit_AVL(AVLNode* node)
//	{
//		if (node)
//		{
//			std::cout << node->data << " ";
//		}
//		else
//		{
//			std::cout << "TreeNode is not exist" << std::endl;
//			exit(0);
//		}
//	}
//	// 中序遍历平衡二叉树
//	void BinaryTree_Traversal_Inorder_AVL(AVLNode* node)
//	{
//		if (node)
//		{
//			BinaryTree_Traversal_Inorder_AVL(node->left);//L
//			BinaryTree_Visit_AVL(node);//D
//			BinaryTree_Traversal_Inorder_AVL(node->right);//R
//		}
//	}
//};


////删除平衡二叉树
//void BinaryTree_Destory(BTree_AVL* tree);
////创建AVL节点，元素值为data,默认高度从1开始
//AVLNode* BinaryTree_CreateNode_AVL(DataType data);
////删除平衡二叉树tree中元素值为data的节点，同步平衡
//AVLNode* BinaryTree_AVL_Delete(BTree_AVL* tree, AVLNode* node, DataType data);
//// 插入AVL节点，在平衡二叉树tree中,递归过程中同步实现平衡化
//void BinaryTree_Insert_AVL(BTree_AVL* tree, DataType data);
////访问AVL节点名
//void BinaryTree_Visit_AVL(AVLNode* node);
//// 中序遍历平衡二叉树
//void BinaryTree_Traversal_Inorder_AVL(AVLNode* node);









