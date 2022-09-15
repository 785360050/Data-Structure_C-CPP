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



//�½�������ͷ�ڵ�
BTree* BinaryTree_Init_Root(TNode* root);
//�½���ͨ�������ڵ�
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


/*����������
//�½������������ڵ�
ThreadNode* BinaryTree_CreateNode_Thread(std::string name);
//TODO: BinaryTree_Destory

void BinaryTree_Insert_Thread(BTree* tree, ThreadNode* parent, Direction pos, TNode* node);
//����node�ڵ�
void BinaryTree_Visit_Thread(ThreadNode* node);

void BinaryTree_Modify_ThreadTree(ThreadNode* node);

void BinaryTree_Traversal_Thread_Inorder(ThreadNode* node);

*/






