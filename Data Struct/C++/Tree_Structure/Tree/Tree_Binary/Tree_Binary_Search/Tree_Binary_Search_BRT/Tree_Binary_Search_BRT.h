#pragma once

#include <iostream>

#include "Node_Binary_Search_RB.h"
#include "../Tree_Binary_Search.h"

template <typename DataType, typename KeyType = int, typename NodeType = Node_Binary_Search_RB<DataType, KeyType>>
class Tree_Binary_Search_RBT :public Tree_Binary_Search<DataType, KeyType, NodeType>
{
public:
	Tree_Binary_Search_RBT() :Tree_Binary_Search<DataType, KeyType, NodeType>() {};
	~Tree_Binary_Search_RBT()
	{///自下而上递归销毁节点
		std::cout << "\n删除红黑树节点个数:" << this->count << std::endl;
		std::cout << "删除顺序为: ";
		if (this->root)
			DeleteNode(this->root);
	}
private:
	//左旋
	void Rotate_Left(NodeType* node)
	{
		NodeType* temp = node->right;
		node->right = temp->left;
		if (temp->left)
			temp->left->parent = node;
		temp->parent = node->parent;
		if (node->parent)
			node->parent->left == node ?
			node->parent->left = temp : node->parent->right = temp;
		else
			this->root = temp;
		temp->left = node;
		node->parent = temp;
	}
	//右旋
	void Rotate_Right(NodeType* node)
	{
		NodeType* temp = node->left;
		node->left = temp->right;
		if (temp->right)
			temp->right->parent = node;
		temp->parent = node->parent;
		if (node->parent)
			node->parent->right == node ?
			node->parent->right = temp : node->parent->left = temp;
		else
			this->root = temp;
		temp->right = node;
		node->parent = temp;
	}
	//节点颜色切换
	void Colour_Switch(NodeType* const node)
	{
		node->colour = (node->colour == red) ? black : red;
		//if (node->colour == red)
		//	node->colour = black;
		//else
		//	node->colour = red;
	}
	//调整
	void RBTree_Adjust_Insert(NodeType* node)
	{
		NodeType* parent, * ancestor, * uncle, * temp;//ancestor=GrandParent
		parent = node->parent;
		while (parent && (parent->colour == red))
		{///父节点为红
			ancestor = parent->parent;
			if (!ancestor)
				return;///祖先不存在时最高两层，不需要调整
			parent == ancestor->left ?///定位uncle节点位置
				uncle = ancestor->right : uncle = ancestor->left;
			if (uncle && uncle->colour == red)
			{///叔节点为红色->父、祖父、叔节点变色
				Colour_Switch(uncle);
				Colour_Switch(ancestor);
				Colour_Switch(parent);
				node = ancestor;
				parent = node->parent;
				continue;
			}
			///叔节点为黑色
			if (ancestor->left == parent)
			{///L
				if (parent->right == node)
				{///LR插入->左旋转父节点为LL
					Rotate_Left(parent);
					temp = parent;
					parent = node;
					node = temp;
				}
				///LL时->右旋祖父节点+变色祖父、父节点
				Rotate_Right(ancestor);
				Colour_Switch(ancestor);
				Colour_Switch(parent);
			}
			else
			{///R
				if (parent->left == node)
				{///RL插入->右旋父节点为RR
					Rotate_Right(parent);
					temp = parent;
					parent = node;
					node = temp;
				}
				///RR时->左旋祖父节点+变色祖父、父节点
				Rotate_Left(ancestor);
				Colour_Switch(ancestor);
				Colour_Switch(parent);
			}
		}
		///插入为根时，跳过所有条件判断变色根节点
		this->root->colour = black;
	}
	void RBTree_Adjust_Delete(NodeType* instead, NodeType* parent)
	{
		NodeType* brother;
		while
		(
			this->root != instead			///instead非根
			&&
			(!instead || instead->colour == black)	///instead为黑
		)
		{///instead非根节点，且为红色时
			if (parent->left == instead)
			{///instead为左孩子,则brother为右孩子
				brother = parent->right;
				if (brother->colour == red)
				{///兄弟节点为红色时
					/// 父、兄变色，旋转 转为兄黑处理
					brother->colour = black;
					parent->colour = red;
					Rotate_Left(parent);
					brother = parent->right;
				}
				if ((!brother->left || brother->left->colour == black)	///brother左孩为黑
					&&
					(!brother->right || brother->right->colour == black))		///brother右孩为黑
				{///兄弟两孩子都为黑色
					///兄弟变红，while执行向上递推处理
					//Colour_Switch(brother);
					brother->colour = red;
					instead = parent;
					parent = instead->parent;
				}
				else
				{///兄弟节点至少有一个为红色
					if (!brother->right || brother->right->colour == black)
					{///LR红时，转为LL红
						//Colour_Switch(brother->left);
						//Colour_Switch(brother);
						brother->left->colour = black;
						brother->colour = red;
						Rotate_Right(brother);
						brother = parent->right;
					}
					///RR红时
					brother->colour = parent->colour;
					//Colour_Switch(brother->right);
					//Colour_Switch(parent);
					brother->right->colour = black;
					parent->colour = black;
					Rotate_Left(parent);
					break;
				}
			}
			else
			{///brother为左孩子,方法同上
				brother = parent->left;
				if (brother->colour == red)
				{///兄弟节点为红色时
					/// 父、兄变色，旋转 转为兄黑处理
					//Colour_Switch(brother);
					//Colour_Switch(parent);
					brother->colour = black;
					parent->colour = red;
					Rotate_Right(parent);
					brother = parent->left;
				}
				if ((!brother->left || brother->left->colour == black)
					&&
					(!brother->right || brother->right->colour == black))
				{///兄弟两孩子都为黑色
					///兄弟变红，while执行向上递推处理
					//Colour_Switch(brother);
					//Colour_Switch(instead);
					brother->colour = red;
					instead = parent;
					parent = instead->parent;
				}
				else
				{
					if (!brother->left || brother->left->colour == black)
					{///RL红时，转RR处理
						//Colour_Switch(brother->right);
						//Colour_Switch(brother);
						brother->right->colour = black;
						brother->colour = red;
						Rotate_Left(brother);
						brother = parent->left;

					}
					///RR红时
					brother->colour = parent->colour;
					//Colour_Switch(brother);
					//Colour_Switch(parent);
					brother->left->colour = black;
					parent->colour = black;
					Rotate_Right(parent);
					break;
				}
			}
		}
		if (instead)
			instead->colour = black;
	}
	//删除节点
	void DeleteNode(NodeType* node)
	{
		if (node)
		{
			DeleteNode(node->left);
			DeleteNode(node->right);
			std::cout << node->element << " ";
			delete node;
			--this->count;
		}
	}
	//显示节点
	void Node_Visit_Key(NodeType* node) override
	{
		if (node)
			std::cout << '[' << node->key << ':' << (node->colour == black ? 'B' : 'R') << "] ";
	}
public:
	//插入node节点
	//void Element_Insert(NodeType* node)
	//{
	//	int element = node->element;
	//	NodeType* current = this->root, * precursor = nullptr;
	//	while (current)
	//	{
	//		precursor = current;
	//		if (element < current->element)
	//			current = current->left;
	//		else if (element > current->element)
	//			current = current->right;
	//		else
	//		{
	//			std::cout << "Node element is existed" << std::endl;
	//			return;
	//		}
	//	}
	//	node->parent = precursor;
	//	if (!precursor)///根节点插入
	//		this->root = node;
	//	else
	//		element < precursor->element ?///判断插入左右位置
	//		precursor->left = node : precursor->right = node;
	//	RBTree_Adjust_Insert(node);
	//	++this->count;
	//}

	void Element_Insert(KeyType key, DataType element = NULL)
	{
		//try
		//{///判断元素重复
		//	NodeType
		//		* current = this->root,
		//		* precursor = nullptr;
		//	while (current)
		//	{
		//		precursor = current;
		//		if (element < current->element)
		//			current = current->left;
		//		else if (element > current->element)
		//			current = current->right;
		//		else
		//			throw std::exception("element is existed");
		//		{
		//		}
		//	}
		//}
		//catch (const std::exception& e)
		//{
		//	std::cout << e.what() << std::endl;
		//	return;
		//}
		
		NodeType* node = this->Node_Create(key, std::to_string(key), element);
		NodeType
			* current = this->root,
			* precursor = nullptr;


		while (current)
		{///定位待插入的节点precursor
			precursor = current;
			current = (key < current->key) ?
				current->left : current->right;
		}

		if (!precursor)///根节点插入
			this->root = node;
		else
		{
			key < precursor->key ?///判断插入左右位置
				precursor->left = node : precursor->right = node;
			node->parent = precursor;
		}
		RBTree_Adjust_Insert(node);
		++this->count;
	}

	//void Element_Delete(DataType data)
	void Element_Delete(KeyType key)
	{
		///———————————————————————————————————————————————
		/// 1.平衡树删除节点
		/// 
		/// 2.调整红黑树
		///———————————————————————————————————————————————
		NodeType* node = this->Node_Search(key);
		try
		{
			if (!node)///删除节点不存在
				throw std::exception("Delete Failed: Node is not exsist");
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return;
		}

		NodeType
			* del,		///删除目标节点，用逻辑前驱instead替换
			* instead,	///实际删除的节点(逻辑前驱),替换后删除
			* parent;	///instead的父节点

		///————————————————————————
		///定位del
		///————————————————————————
		if (!node->left || !node->right)	///防止Element_Precursor()抛出异常
			del = node;	///左右子树至少有一个为空，直接用孩子代替
		else
		{///del度为2时
			del = this->Element_Precursor(node);///逻辑前驱
		}


		///————————————————————————
		///定位instead
		///————————————————————————
		instead = del->left ? del->left : del->right;
		parent = del->parent;

		///————————————————————————
		///开始移除节点del,替换为instead
		///————————————————————————
		if (instead)
			instead->parent = parent;
		if (!del->parent)	///del为根时,instead替换根节点
			this->root = instead;		
		//else if (del->partent->left == del)
		//	del->partent->left = instead;
		//else
		//	instead->partent->right = instead;
		else
		{///del非根节点，instead替换到对应分叉
		 ///叶节点相当于，用NULL的instead替换
			if (del->parent->left == del)	
				del->parent->left = instead;	
			else
				del->parent->right = instead;
		}

		if (del != node)
		{///若删除的对象与目标节点不同，即del被替换过，则更新值，不更新颜色
			node->replace_by(del);
		}
		///————————————————————————
		/// 移除节点del完毕，更新为instead节点
		///————————————————————————

		///————————————————————————
		/// 判断del颜色，删除红色节点不调整
		///————————————————————————
		if (del->colour == black)	///删除黑色节点时(删除并替换后)
			RBTree_Adjust_Delete(instead, parent);
		delete del;
		--this->count;


	}

};

