#include "../API/Tree_Binary_AVL.h"

#include <cstring>

BTree_AVL* BinaryTree_Init_Root_AVL()
{
	BTree_AVL* tree = new BTree_AVL;
	tree->root = nullptr;
	tree->num = 0;
	return tree;
}


static void DeleteNode(BTree_AVL* tree, AVLNode* node)
{
	if (node)
	{
		DeleteNode(tree, node->left);
		DeleteNode(tree, node->right);
		std::cout << node->data << " ";
		free(node);
		tree->num--;
	}
}
void BinaryTree_Destory(BTree_AVL* tree)
{///自下而上递归销毁节点
	if (tree)
	{
		std::cout << "删除二叉树树节点个数:" << tree->num << std::endl;
		if (tree->root)
			DeleteNode(tree, tree->root);
	}
}


static int maxnode(int a, int b)
{
	return (a > b) ? a : b;
}
static int hightnode(AVLNode* node)
{
	if (node == NULL)
		return 0;
	return node->hight;
}
AVLNode* BinaryTree_CreateNode_AVL(DataType data)
{
	AVLNode* node = new AVLNode;
	memset(node, 0, sizeof(AVLNode));
	node->data = data;
	node->hight = 1;///默认高度从1开始
	return node;
}

static int getbalance(AVLNode* node)
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
static AVLNode* Rotate_Left(AVLNode* node)
{
	AVLNode* temp = node->right;
	node->right = temp->left;
	temp->left = node;
	node->hight = maxnode(hightnode(node->left), hightnode(node->right)) + 1;
	temp->hight = maxnode(hightnode(temp->left), hightnode(node->right)) + 1;
	return temp;
}
//右旋(以当前节点为子树根)
static AVLNode* Rotate_Right(AVLNode* node)
{
	AVLNode* temp = node->left;
	node->left = temp->right;
	temp->right = node;
	temp->hight = maxnode(hightnode(temp->left), hightnode(node->right)) + 1;
	node->hight = maxnode(hightnode(node->left), hightnode(node->right)) + 1;
	return temp;
}
static AVLNode* node_insert(BinaryTree_AVL* tree, AVLNode* node, DataType data)
{
	if (!node)
	{///出口1，找到位置并创建节点插入树
		tree->num++;
		return BinaryTree_CreateNode_AVL(data);
	}
	else///递
	{///寻找插入节点的空位置
		if (data < node->data)
			node->left = node_insert(tree, node->left, data);
		if (data > node->data)
			node->right = node_insert(tree, node->right, data);
	}
	

	///回归时同步更新子树根高度(上一层的节点高度)
	node->hight = 1 + maxnode(hightnode(node->left), hightnode(node->right));
	///	根据平衡因子旋转
	/// 从上到下[第一个失衡节点][第二个失衡节点]
	///	LL->R
	///	RR->L
	///	LR->LR
	///	RL->RL
	int balance = getbalance(node);///计算平衡因子，调整子树(递归实现从下至上)
	if (balance>1)
	{//L重
		if (data < node->left->data)//L重
			return Rotate_Right(node);//LL右旋
		if (data > node->left->data)//R重
		{//LR
			node->left = Rotate_Left(node->left);//先左旋子树
			return Rotate_Right(node);//再整体右旋
		}
	}
	if (balance < -1)
	{//R重
		if (data > node->right->data)//L重
			return Rotate_Left(node);//LL右旋
		if (data < node->right->data)//R重
		{//RL
			node->right = Rotate_Right(node->left);//先左旋子树
			return Rotate_Left(node);//再整体右旋
		}
	}
	return node;///出口2，元素已存在，或平衡完毕后
}
// 插入AVL节点，在平衡二叉树tree中，双亲为parenr的[左/右]位置
void BinaryTree_Insert_AVL(BTree_AVL* tree, DataType data)
{
	if (tree)
		tree->root = node_insert(tree, tree->root, data);
}

//访问AVL节点名
void BinaryTree_Visit_AVL(AVLNode* node)
{
	if (node)
	{
		std::cout << node->data << " ";
	}
	else
	{
		std::cout << "TreeNode is not exist" << std::endl;
		exit(0);
	}
}
// 中序遍历平衡二叉树
void BinaryTree_Traversal_Inorder_AVL(AVLNode* node)
{
	if (node)
	{
		BinaryTree_Traversal_Inorder_AVL(node->left);//L
		BinaryTree_Visit_AVL(node);//D
		BinaryTree_Traversal_Inorder_AVL(node->right);//R
	}
}

AVLNode* BinaryTree_AVL_Delete(BTree_AVL* tree, AVLNode* node, DataType data)
{
	/// <summary>
	/// 删除同二叉搜索树，用逻辑前驱或后继代替，
	/// 删除完后，回归的同时更新平衡因子并调整
	/// </summary>
	/// <param name="tree"></param>
	/// <param name="node"></param>
	/// <param name="data"></param>
	/// <returns></returns>
	AVLNode* temp;
	if (!node)///递归出口，目标节点不存在，直接回归退出
		return node;
	/// 递 寻找目标节点
	if (data < node->data)
		node->left = BinaryTree_AVL_Delete(tree, node->left, data);
	if (data > node->data)
		node->right = BinaryTree_AVL_Delete(tree, node->right, data);
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
				node->data = temp->data;
				node->left = temp->left;
				node->right = temp->right;
				node->hight = temp->hight;
			}
			delete temp;
			tree->num--;
		}
		else
		{///删除节点左右孩子都存在,用逻辑前驱代替
			temp = node->left;
			while (temp->right)
				temp = temp->right;//找到逻辑前驱
			node->data = temp->data;//用逻辑后继替换
			node->left = BinaryTree_AVL_Delete(tree, node->left, temp->data);//替换后删除替换的节点
		}
	}

	/// 回归时同步平衡调整，同插入平衡化
	if (!node)
		return node;

	///
	node->hight = 1 + maxnode(hightnode(node->left), hightnode(node->right));
	int balance = getbalance(node);///计算平衡因子，调整子树(递归实现从下至上)
	if (balance > 1)
	{//L重
		if (getbalance(node->left) < 0)		//LR
			node->left = Rotate_Left(node->left); 
		return Rotate_Right(node);	//LL
	}
	if (balance < -1)
	{//R重
		if (getbalance(node->right) > 0)	//RL
			node->right = Rotate_Right(node->right);
		return Rotate_Left(node);	//RR
	}
	return node;///出口2
}