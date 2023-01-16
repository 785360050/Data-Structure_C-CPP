#pragma once
#include "Tree_Binary_ADT.h"
#include "Tree_Binary_Normal.h"

template <typename DataType>
class Binary_Tree_Search :public Binary_Tree<DataType>
{
public:
	Binary_Tree_Search() :Binary_Tree<DataType>() {};
private:
//	//增加二叉搜索节点data
//	//Node_BinaryTree<DataType>* insertnode(Node_BinaryTree<DataType>* node,DataType data)
//	//{
//	//	if (!node)
//	//	{
//	//		Node_BinaryTree<DataType>* p = this->Node_Create(data);
//	//		++this->count;
//	//		return p;
//	//	}
//	//	if (data < node->data)
//	//	{
//	//		Node_BinaryTree<DataType>* l = insertnode(node->left, data);
//	//		node->left = l;
//	//	}
//	//	else if (data > node->data)
//	//	{
//	//		Node_BinaryTree<DataType>* r = insertnode(node->right, data);
//	//		node->right = r;
//	//	}
//	//	else
//	//		std::cout << "Insert failed: Existed" << std::endl;
//	//	return node;
//	//}
//public:
//	//递增输出所有元素(中序遍历)
//	void TreeIncrease(Node_BinaryTree<DataType>* tree)
//	{
//		BinaryTree_Traversal_Inorder_Data(tree);
//	}
//	//查找节点  O(Logn)
//	Node_BinaryTree<DataType>* Tree_LocateElement(string name)
//	{
//		Node_BinaryTree<DataType>* p = this->root;
//		while (p)
//		{
//			if (p->name == name)
//				return p;
//			else
//				p = data < p->data ? p->left : p->right;
//		}
//		return nullptr;
//	}
//
//	void Tree_Element_Insert(DataType data)
//	{
//		insertnode(tree->root, data);
//	}
//	void Tree_Insert_NonRecursive(Binary_Tree_Search<DataType>* tree, DataType data)
//	{
//		Node_BinaryTree<DataType>* current = this->root, * precursor = nullptr;
//		while (current)
//		{
//			precursor = current;
//			if (data < current->element)
//				current = current->left;
//			if (data > current->element)
//				current = current->right;
//			return;
//		}
//		Node_BinaryTree<DataType>* node = new Node_BinaryTree<DataType>(data);
//		++this->count;
//		if (precursor && data < precursor->element) 
//			precursor->left = node;
//		else if (precursor && data > precursor->element) 
//			precursor->right = node;
//		if (!precursor) 
//			this->root = node;
//
//
//
//	}
//
//	//删除二叉搜索子树tree中值为data的节点
//	Node_BinaryTree<DataType>* Tree_Delete(Node_BinaryTree<DataType>* tree, DataType data)
//	{///删除子树tree中值为data的节点
//		/// <summary>
//		/// [此处用逻辑后继顶替]
//		/// </summary>
//		/// <param name="tree"></param>
//		/// <param name="node"></param>
//		/// <param name="data"></param>
//		/// <returns></returns>
//		if (tree == nullptr)///递归出口
//			return nullptr;
//		if (data < tree->data)
//		{///第2-4个if用于寻路，找到删除目标节点
//			return BinaryTree_Search_Delete(tree->left, data);
//		}
//		if (data > tree->data)
//		{
//			return BinaryTree_Search_Delete(tree->right, data);
//		}
//		///删除节点，找代替节点
//		if (data == tree->data)
//		{///此时位于删除节点处，删除节点并调整二叉搜索树
//			if (tree->left == NULL && tree->right == NULL)
//			{///前两个if处理单孩子情况
//				delete tree;
//				return nullptr;
//			}
//			if (tree->left == NULL)
//			{
//				TNode* temp = tree->right;
//				delete tree;
//				return temp;
//			}
//			if (tree->right == NULL)
//			{
//				TNode* temp = tree->left;
//				delete tree;
//				return temp;
//			}
//			else///左右子树都不为空
//			{///用右孩子的最小节点代替(逻辑后继)
//				TNode* p = NextNode(tree);
//				tree->data = p->data;///直接用顶替的节点先覆盖
//				tree->right = BinaryTree_Search_Delete(tree->right, p->data);///再删除顶替节点
//				return tree;
//			}
//		}
//	}
//
//	//定位逻辑后继节点，即右子树的中序首节点
//	Node_BinaryTree<DataType>* Element_Next(Node_BinaryTree<DataType>* node)
//	{///不存在抛错
//		try
//		{
//			if (!node->right)
//				throw std::exception("No Next Node");
//		}
//		catch (const std::exception& e)
//		{
//			std::cout << e.what() << std::endl;
//			return nullptr;
//		}
//		node = node->right;
//		while (node && node->left)
//			node = node->left;
//		return node;
//	}
//	//定位逻辑前驱节点，即左子树的中序末节点
//	Node_BinaryTree<DataType>* Element_Precursor(Node_BinaryTree<DataType>* node)
//	{///不存在抛错
//		try
//		{
//			if (!node->left)
//				throw std::exception("No Precursor Node");
//		}
//		catch (const std::exception& e)
//		{
//			std::cout << e.what() << std::endl;
//			return nullptr;
//		}
//		node = node->left;
//		while (node && node->right)
//			node = node->right;
//		return node;
//	}

};


