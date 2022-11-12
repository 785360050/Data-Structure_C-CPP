#include "../API/Tree_Binary_BRT.h"


//左旋
static void Rotate_Left(RBTree* tree, RBNode* node)
{
	RBNode* temp = node->right;
	node->right = temp->left;
	if (temp->left)
		temp->left->partent = node;
	temp->partent = node->partent;
	if (node->partent)
		node->partent->left == node ?
		node->partent->left = temp : node->partent->right = temp;
	else
		tree->root = temp;
	temp->left = node;
	node->partent = temp;
}
//右旋
static void Rotate_Right(RBTree* tree, RBNode* node)
{
	RBNode* temp = node->left;
	node->left = temp->right;
	if (temp->right)
		temp->right->partent = node;
	temp->partent = node->partent;
	if (node->partent)
		node->partent->right == node ?
		node->partent->right = temp : node->partent->left = temp;
	else
		tree->root = temp;
	temp->right = node;
	node->partent = temp;
}

//节点颜色切换
static void Colour_Switch(RBNode* const node)
{
	//node->colour = node->colour == red ? black : red;
	if (node->colour == red)
		node->colour = black;
	else
		node->colour = red;
}

///调整
static void RBTree_Adjust_Insert(RBTree* tree, RBNode* node)
{
	RBNode* parent, * ancestor, * uncle, * temp;//ancestor=GrandParent
	parent = node->partent;
	while (parent && (parent->colour == red))
	{///父节点为红
		ancestor = parent->partent;
		parent == ancestor->left ?///定位uncle节点位置
			uncle = ancestor->right : uncle = ancestor->left;
		if (uncle && uncle->colour == red)
		{///叔节点为红色->父、祖父、叔节点变色
			Colour_Switch(uncle);
			Colour_Switch(ancestor);
			Colour_Switch(parent);
			node = ancestor;
			parent = node->partent;
			continue;
		}
		///叔节点为黑色
		if (ancestor->left == parent)
		{///L
			if (parent->right == node)
			{///LR插入->左旋转父节点为LL
				Rotate_Left(tree, parent);
				temp = parent;
				parent = node;
				node = temp;
			}
			///LL时->右旋祖父节点+变色祖父、父节点
			Rotate_Right(tree, ancestor);
			Colour_Switch(ancestor);
			Colour_Switch(parent);
		}
		else
		{///R
			if (parent->left == node)
			{///RL插入->右旋父节点为RR
				Rotate_Right(tree, parent);
				temp = parent;
				parent = node;
				node = temp;
			}
			///RR时->左旋祖父节点+变色祖父、父节点
			Rotate_Left(tree, ancestor);
			Colour_Switch(ancestor);
			Colour_Switch(parent);
		}
	}
	///插入为根时，跳过所有条件判断变色根节点
	tree->root->colour = black;
}
static void RBTree_Adjust_Delete(RBTree* tree, RBNode* del, RBNode* parent)
{
	RBNode* temp;
	while (tree->root != del->partent && (!del || del->colour == black))
	{///del为非红时
		if (parent->left==del)
		{///del为左孩子
			temp = parent->right;
			if (temp->colour == red)
			{///兄弟节点为红色
				Colour_Switch(temp);
				Colour_Switch(parent);
				Rotate_Left(tree, parent);
				temp = parent->right;
			}
			if ((!temp->left && temp->left->colour == black) && (!temp || temp->right->colour == black))
			{///兄弟节点为黑色
				Colour_Switch(temp);
				del = parent;
				parent = del->partent;
			}
			else
			{///兄弟节点至少有一个为红色
				if (!temp->right || temp->right->colour == black)
				{///temp右孩子非红时
					Colour_Switch(temp->left);
					Colour_Switch(temp);
					Rotate_Right(tree, temp);
					temp = parent->right;
				}
				temp->colour = parent->colour;
				Colour_Switch(temp->right);
				Colour_Switch(parent);
				Rotate_Left(tree, parent);
				break;
			}
		}
		else
		{
			temp = parent->left;
			if (temp->colour == red)
			{
				Colour_Switch(temp);
				Colour_Switch(parent);
				Rotate_Right(tree, parent);
				temp = parent->left;
			}
			if ((!temp->left || temp->left->colour == black) && (!temp->right || temp->right->colour == black))
			{
				Colour_Switch(temp);
				Colour_Switch(del);
				parent = del->partent;
			}
			else
			{
				if (!temp->left || temp->left->colour == black)
				{///通向为黑色时
					Colour_Switch(temp->right);
					Colour_Switch(temp);
					Rotate_Left(tree, temp);
					temp = parent->left;

				}
				///通向红时
				temp->colour = parent->colour;
				Colour_Switch(temp);
				Colour_Switch(parent);
				Rotate_Right(tree, parent);
				break;
			}
		}
	}
}


RBNode* RBNode_Create(int key, Colour colour)
{
	RBNode* node = new RBNode;
	node->key = key;
	node->left = node->right = node->partent = nullptr;
	node->colour = colour;
	return node;
}

RBTree* BRT_Init(RBNode* root)
{
	RBTree* tree = new RBTree;
	tree->root = root;
	tree->num = 0;
	return tree;
}

void RBTree_RBNode_Insert(RBTree* tree, RBNode* node)
{
	int key = node->key;
	RBNode* current = tree->root, * precursor = nullptr;
	while (current)
	{
		precursor = current;
		if (key < current->key)
			current = current->left;
		else if (key > current->key)
			current = current->right;
		else
		{
			std::cout << "Node Key is existed" << std::endl;
			return;
		}
	}
	node->partent = precursor;
	if (!precursor)///根节点插入
		tree->root = node;
	else
		key < precursor->key ?///判断插入左右位置
			precursor->left = node : precursor->right = node;
	RBTree_Adjust_Insert(tree,node);
	tree->num++;
}

void RBTree_RBNode_Delete(RBTree* tree, RBNode* node)
{
	RBNode* del, * instead, * parent;
	if (node->left == nullptr || node->right == nullptr)
		del = node;
	else
	{///del度为2，del指向中序逻辑后继
		del = node->right;
		while (del->left)
			del = del->left;
	}
	///定位到删除节点，找删除节点的逻辑后继(替换节点)
	instead = del->left ? del->left : del->right;
	parent = del->partent;
	///开始删除
	if (instead)
		instead->partent = parent;
	if (del->partent == nullptr)
		tree->root = instead;///替换根节点
	else if (del->partent->left == del)
		del->partent->left = instead;
	else
		instead->partent->right = instead;

	if (del != node)
		node->key = del->key;
	if (del->colour == black)
		RBTree_Adjust_Delete(tree, instead, parent);
	delete del;
}

RBNode* RBTree_Search(RBTree* tree, int key)
{
	RBNode* node = tree->root;
	while (node)
	{
		if (key < node->key)
			node = node->left;
		else if (key > node->key)
			node = node->right;
		else
			return node;
			
	}
	return nullptr;
}

static void DeleteNode(RBTree* tree, RBNode* node)
{
	if (node)
	{
		DeleteNode(tree, node->left);
		DeleteNode(tree, node->right);
		std::cout << node->key << " ";
		free(node);
		tree->num--;
	}
}
void RBTree_Destroy(RBTree* tree)
{///自下而上递归销毁节点
	if (tree)
	{
		std::cout << "\n删除红黑树节点个数:" << tree->num << std::endl;
		if (tree->root)
			DeleteNode(tree, tree->root);
	}
}

static void RBTree_Visit(const RBNode* const node)
{
	if (node)
		std::cout << '[' << node->key << ':' << (node->colour == black ? 'B' : 'R') << "] ";
}
void RBTree_Traverse_Inorder(RBNode* node)
{
	if (node)
	{
		RBTree_Traverse_Inorder(node->left);//L
		RBTree_Visit(node);//D
		RBTree_Traverse_Inorder(node->right);//R
	}
}
void RBTree_Traverse_Preorder(RBNode* node)
{
	if (node)
	{
		RBTree_Visit(node);//D
		RBTree_Traverse_Preorder(node->left);//L
		RBTree_Traverse_Preorder(node->right);//R
	}
}



