#pragma once

#include <iostream>

#include "Node_Binary_Search_RB.h"
#include "../Tree_Binary_Search.h"

template <typename DataType, typename NodeType = Node_Binary_Search_RB<DataType>>
class Tree_Binary_Search_RBT :public Tree_Binary_Search<DataType, NodeType>
{
//public:
//	Node_Binary_Search_RB<DataType>* root;
//	int count;
public:
	Tree_Binary_Search_RBT() :Tree_Binary_Search<DataType, NodeType>() {};
	Tree_Binary_Search_RBT(NodeType* root) :Tree_Binary_Search<DataType, NodeType>(root) {};

	~Tree_Binary_Search_RBT()
	{///自下而上递归销毁节点
		std::cout << "\n删除红黑树节点个数:" << this->count << std::endl;
		std::cout << "删除顺序为: ";
		if (this->root)
			DeleteNode(this->root);
	}
private:
	//左旋
	void Rotate_Left(Node_Binary_Search_RB<DataType>* node)
	{
		Node_Binary_Search_RB<DataType>* temp = node->right;
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
	void Rotate_Right(Node_Binary_Search_RB<DataType>* node)
	{
		Node_Binary_Search_RB<DataType>* temp = node->left;
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
	void Colour_Switch(Node_Binary_Search_RB<DataType>* const node)
	{
		node->colour = (node->colour == red) ? black : red;
		//if (node->colour == red)
		//	node->colour = black;
		//else
		//	node->colour = red;
	}
	//调整
	void RBTree_Adjust_Insert(Node_Binary_Search_RB<DataType>* node)
	{
		Node_Binary_Search_RB<DataType>* parent, * ancestor, * uncle, * temp;//ancestor=GrandParent
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
	void RBTree_Adjust_Delete(Node_Binary_Search_RB<DataType>* instead, Node_Binary_Search_RB<DataType>* parent)
	{
		Node_Binary_Search_RB<DataType>* brother;
		while
		(
			this->root != instead			///instead非根
			&&
			(!instead || instead->colour == black)	///instead为黑
		)///instead为黑
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
				if ((!brother->left && brother->left->colour == black)
					&&
					(!brother || brother->right->colour == black))
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
	void DeleteNode(Node_Binary_Search_RB<DataType>* node)
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
	void Node_Visit_Name(NodeType* node) override
	{
		if (node)
			std::cout << '[' << node->element << ':' << (node->colour == black ? 'B' : 'R') << "] ";
	}
public:
	//插入node节点
	//void Element_Insert(Node_Binary_Search_RB<DataType>* node)
	//{
	//	int element = node->element;
	//	Node_Binary_Search_RB<DataType>* current = this->root, * precursor = nullptr;
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

	void Element_Insert(DataType element)
	{
		//try
		//{///判断元素重复
		//	Node_Binary_Search_RB<DataType>
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
		
		NodeType* node = this->Node_Create(std::to_string(element), element);
		Node_Binary_Search_RB<DataType>
			* current = this->root,
			* precursor = nullptr;


		while (current)
		{///定位待插入的节点precursor
			precursor = current;
			current = (element < current->element) ? 
				current->left : current->right;
		}

		if (!precursor)///根节点插入
			this->root = node;
		else
		{
			element < precursor->element ?///判断插入左右位置
				precursor->left = node : precursor->right = node;
			node->parent = precursor;
		}
		RBTree_Adjust_Insert(node);
		++this->count;
	}

	//void Element_Delete(DataType data)
	void Element_Delete(DataType data)
	{
		Node_Binary_Search_RB<DataType>* node = this->Node_Search(std::to_string(data));
		if (!node)///删除节点不存在
			return;

		Node_Binary_Search_RB<DataType>
			* del,		///删除的节点
			* instead,	///替换的节点，覆盖删除的节点del
			* parent;	///父节点

		///————————————————————————
		///定位删除节点
		///————————————————————————
		if (node->left == nullptr || node->right == nullptr)
			del = node;
		else
		{///del度为2时
			//del = node->right;
			//while (del->left)
			//	del = del->left;
			del = node->left;
			while (del->right)///逻辑前驱
				del = del->right;
		}
		///————————————————————————
		///定位替换节点(逻辑前驱)
		///————————————————————————
		instead = del->left ? del->left : del->right;
		parent = del->parent;

		///————————————————————————
		///开始删除
		///————————————————————————
		if (instead)
			instead->parent = parent;
		if (del->parent == nullptr)	///del为根时
			this->root = instead;		///替换根节点
		//else if (del->partent->left == del)
		//	del->partent->left = instead;
		//else
		//	instead->partent->right = instead;
		else
		{
			if (del->parent->left == del)
				del->parent->left = instead;
			else
				del->parent->right = instead;
		}

		///————————————————————————
		/// 删除del完毕，更新instead值
		///————————————————————————
		if (del != node)
		{
			node->element = del->element;
			node->name = del->name;
		}

		///————————————————————————
		///删除红色节点不调整
		///————————————————————————
		if (del->colour == black)	///删除黑色节点时(删除并替换后)
			RBTree_Adjust_Delete(instead, parent);
		delete del;
		--this->count;


	}

};

