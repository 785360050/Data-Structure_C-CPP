#include "../API/Tree_Binary_Search.h"
#include <string>





//BTree* BinaryTree_Search_Init();

void BinaryTree_Order_Increase(TNode* tree)
{
	BinaryTree_Traversal_Inorder_Data(tree);
}


//int BinaryTree_Search_Depth(BTree* tree);


TNode* BinaryTree_Search_LocateElement(BTree* tree, DataType data)
{
	TNode* p = tree->root;
	while (p)
	{
		if (p->data == data)
			return p;
		else
			data < p->data ?
			p = p->left : p = p->right;
	}
	return nullptr;
}

static TNode* insertnode(BTree* tree , TNode* node,DataType data)
{
	if (!node)
	{
		TNode* p = BinaryTree_CreateNode(data);
		tree->num++;
		return p;
	}
	else if (data < node->data)
	{
		TNode* l=insertnode(tree, node->left, data);
		node->left = l;
	}
	else if (data > node->data)
	{
		TNode* r=insertnode(tree, node->right, data);
		node->right = r;
	}
	else
		std::cout << "Insert failed: Existed" << std::endl;
	return node;
}
void BinaryTree_Search_Insert(BTree* tree, DataType data)
{
	BTree* temp = tree;
	insertnode(temp, tree->root, data);
}
void BinaryTree_Search_Insert_NonRecursive(BTree* tree, DataType data)
{
	TNode* current = tree->root, * precursor = nullptr;
	while (current)
	{///查找是否已存在相同节点
		precursor = current;
		if (data < current->data)
			current = current->left;
		else if (data > current->data)
			current = current->right;
		else
			return;
	}
	TNode* node = BinaryTree_CreateNode(data);
	++tree->num;
	if (precursor && data < precursor->data)
		precursor->left = node;
	else if (precursor && data > precursor->data)
		precursor->right = node;
	if (!precursor) 
		tree->root = node;

}

TNode* NextNode(TNode* node)
{///不存在抛错
	try
	{
		if (!node->right)
			throw 1;
	}
	catch (...)
	{
		std::cout << "No Next Node" << std::endl;
		exit(0);
	}
	node = node->right;
	while (node && node->left)
		node = node->left;
	return node;
}
TNode* PriNode(TNode* node)
{///不存在抛错
	try
	{
		if (!node->left)
			throw 1;
	}
	catch (...)
	{
			std::cout << "No Prior Node" << std::endl;
			exit(0);
	}
	node = node->left;
	while (node && node->right)
		node = node->right;
	return node;
}

TNode* BinaryTree_Search_Delete(TNode* tree, DataType data)
{///删除子树tree中值为data的节点
	/// <summary>
	/// [此处用逻辑后继顶替]
	/// </summary>
	/// <param name="tree"></param>
	/// <param name="node"></param>
	/// <param name="data"></param>
	/// <returns></returns>
	if (tree == NULL)///递归出口
		return nullptr;
	if (data < tree->data)
	{///第2-4个if用于寻路，找到删除目标节点
		tree->left = BinaryTree_Search_Delete(tree->left, data);
		return tree;
	}
	if (data > tree->data)
	{
		tree->right = BinaryTree_Search_Delete(tree->right, data);
		return tree;
	}
	///删除节点，找代替节点
	if (data == tree->data)
	{///此时位于删除节点处，删除节点并调整二叉搜索树
		if (tree->left == NULL && tree->right == NULL)
		{///前两个if处理单孩子情况
			delete tree;
			return nullptr;
		}
		if (tree->left == NULL)
		{
			TNode* temp = tree->right;
			delete tree;
			return temp;
		}
		if (tree->right == NULL)
		{
			TNode* temp = tree->left;
			delete tree;
			return temp;
		}
		else///左右子树都不为空
		{///用右孩子的最小节点代替(逻辑后继)
			TNode* p = NextNode(tree);
			tree->data = p->data;///直接用顶替的节点先覆盖
			tree->right = BinaryTree_Search_Delete(tree->right, p->data);///再删除顶替节点
			return tree;
		}
	}
}















