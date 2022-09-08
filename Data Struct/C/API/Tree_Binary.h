#include <iostream>
#include <string>
typedef int DataType;

struct TreeNode
{
	DataType data;
	struct TreeNode* left;
	struct TreeNode* right;
	std::string name;
};
typedef struct TreeNode TNode;

struct BinaryTree
{
	TNode* root;
	int num;
};
typedef BinaryTree BTree;

enum Direction {left = 1,right = 2 };

//新建二叉树头节点
BTree* BinaryTree_Init_Root(TNode* root);
//新建节点
TreeNode* BinaryTree_CreateNode(std::string name);
//二叉树tree中,在父节点parent的pos[左/右]位置，插入节点node,
void BinaryTree_Insert(BTree* tree, TNode* parent, Direction pos, TNode* node);
//访问node节点
void BinaryTree_Visit(TNode* node);

//广度遍历
void BinaryTree_Traversal_Level(BTree* tree);
//DLR
void BinaryTree_Traversal_Preorder(TNode* node);
//LDR
void BinaryTree_Traversal_Inorder(TNode* node);
//LRD
void BinaryTree_Traversal_Postorder(TNode* node);












