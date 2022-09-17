#include "../API/Tree_Binary_Search.h"
#include <string>





BTree* BinaryTree_Search_Init();

void BinaryTree_Search_Destroy();


void BinaryTree_Order_Increase(TNode* tree)
{
	BinaryTree_Traversal_Inorder_Data(tree);
}


int BinaryTree_Search_Depth(BTree* tree);


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
	insertnode(tree, tree->root, data);
}
void BinaryTree_Search_Insert_NonRecursive(BTree* tree, DataType data);

void BinaryTree_Search_Delete(BTree* tree, TNode* node , DataType data)
{///此处用逻辑前驱顶替
	if (!node)
		return nullptr;
	if (data<node->data)

}

TNode* BinaryTree_Search_Locate_Max(BTree* tree);














