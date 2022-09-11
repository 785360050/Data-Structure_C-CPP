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

struct TreeNode_Thread
{
	DataType data;
	bool Thread_Left;
	struct TreeNode* left;
	bool Thread_Right;
	struct TreeNode* right;
	std::string name;
};
typedef TreeNode_Thread ThreadNode;

struct BinaryTree
{
	TNode* root;
	int num;
};
typedef BinaryTree BTree;

enum Direction {left = 1,right = 2 };

//新建二叉树头节点
BTree* BinaryTree_Init_Root(TNode* root);
//新建普通二叉树节点
TreeNode* BinaryTree_CreateNode(std::string name);
//二叉树tree中,在父节点parent的pos[左/右]位置，插入节点node,
void BinaryTree_Insert(BTree* tree, TNode* parent, Direction pos, TNode* node);
//访问node节点
void BinaryTree_Visit(TNode* node);

//广度遍历
void BinaryTree_Traversal_Level(BTree* tree);
//DLR
void BinaryTree_Traversal_Preorder(TNode* node);
void BinaryTree_Traversal_Preorder_NoneRecursion(TNode* node);
//LDR
void BinaryTree_Traversal_Inorder(TNode* node);
void BinaryTree_Traversal_Inorder_NoneRecursion(TNode* node);
//LRD
void BinaryTree_Traversal_Postorder(TNode* node);
void BinaryTree_Traversal_Postorder_NoneRecursion(TNode* node);


/*线索二叉树
//新建线索二叉树节点
ThreadNode* BinaryTree_CreateNode_Thread(std::string name);
//TODO: BinaryTree_Destory

void BinaryTree_Insert_Thread(BTree* tree, ThreadNode* parent, Direction pos, TNode* node);
//访问node节点
void BinaryTree_Visit_Thread(ThreadNode* node);

void BinaryTree_Modify_ThreadTree(ThreadNode* node);

void BinaryTree_Traversal_Thread_Inorder(ThreadNode* node);

*/






