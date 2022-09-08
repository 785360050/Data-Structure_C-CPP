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

//�½�������ͷ�ڵ�
BTree* BinaryTree_Init_Root(TNode* root);
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
//LDR
void BinaryTree_Traversal_Inorder(TNode* node);
//LRD
void BinaryTree_Traversal_Postorder(TNode* node);












