#pragma once
#include <iostream>

#include "Global Variables.h"

/// <summary>
/// ����������������
/// ��Ӧ�ı�����������
/// �����ڴ�����ڵ�Ѱ���߼�ǰ���ͺ��
/// (����n���ڵ�Ķ�������n+1��������)
/// </summary>

struct ThreadNode
{
	DataType data;
	struct ThreadNode* left;
	struct ThreadNode* right;
	std::string name;
	//����Ƿ�Ϊ��������ָ���߼�ǰ��
	bool Thread_left;
	//����Ƿ�Ϊ��������ָ���߼����
	bool Thread_right;
};
typedef struct ThreadNode ThreadNode;

struct BinaryTree_Thread
{
	ThreadNode* root;
	int num;
};
typedef BinaryTree_Thread BTree_Thread;

//����������ͷ�ڵ㣬�󶨽ڵ�rootΪ��
BTree_Thread* BinaryTree_Init_Root(ThreadNode* root);
//ɾ������������
void BinaryTree_Destory(BTree_Thread* tree);
//���������ڵ㣬�ڵ�����Ϊname
ThreadNode* BinaryTree_CreateNode_Thread(std::string name);
// ���������ڵ㣬��������tree�У�˫��Ϊparenr��[��/��]λ��
void BinaryTree_Insert_Thread(BTree_Thread* tree, ThreadNode* parent, Direction pos, ThreadNode* node);
//���������ڵ���
void BinaryTree_Visit(ThreadNode* node);
// ����������������
void BinaryTree_Thread_Inorder(ThreadNode* node);
// ���������������(�Ż�����)
void BinaryTree_Traversal_Inorder_Thread(ThreadNode* node);


