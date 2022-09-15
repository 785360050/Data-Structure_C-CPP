#include <iostream>
#include <string>

#include "Global Variables.h"

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



//�½�������ͷ�ڵ�
BTree* BinaryTree_Init_Root(TNode* root);
//ɾ����
void BinaryTree_Destory(BTree* tree);
//�½��ڵ�
TreeNode* BinaryTree_CreateNode(std::string name);
//������tree��,�ڸ��ڵ�parent��pos[��/��]λ�ã�����ڵ�node,
void BinaryTree_Insert(BTree* tree, TNode* parent, Direction pos, TNode* node);
//����node�ڵ�
void BinaryTree_Visit(TNode* node);

//��ȱ���
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












