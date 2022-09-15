#include <iostream>

#include "../API/Tree_Binary_Thread.h"



BTree_Thread* BinaryTree_Init_Root(ThreadNode* root)
{
	BTree_Thread* t = new BTree_Thread;
	t->num = 0;
	t->root = root;
	return t;
}

static void DeleteNode(BTree_Thread* tree, ThreadNode* node)
{
	if (node)
	{///�������������ɾ���ڵ�ݹ�
		if (node->Thread_left == false)
			DeleteNode(tree, node->left);
		if (node->Thread_right == false)
			DeleteNode(tree, node->right);
		std::cout << node->name << " ";
		free(node);
		tree->num--;
		
	}
}
void BinaryTree_Destory(BTree_Thread* tree)
{///���¶��ϵݹ����ٽڵ�
	if (tree)
	{
		std::cout << "ɾ�����������ڵ����:" << tree->num << std::endl;
		if (tree->root)
			DeleteNode(tree, tree->root);
	}
}

ThreadNode* BinaryTree_CreateNode_Thread(std::string name)
{///��ʼ������ָ��Ϊ�գ��������Ϊfalse
	ThreadNode* n = new ThreadNode;
	n->left = n->right = nullptr;
	n->Thread_left = n->Thread_right = false;
	n->name = name;
	return n;
}

void BinaryTree_Insert_Thread(BTree_Thread* tree, ThreadNode* parent, Direction pos, ThreadNode* node)
{
	/// <summary>
	/// ���ڳ�ʼ���������Ĳ��ԣ����ܿ��ǲ�ȫ
	/// </summary>
	/// <param name="tree"></param>
	/// <param name="parent"></param>
	/// <param name="pos"></param>
	/// <param name="node"></param>
	pos == right ?
		parent->right = node : parent->left = node;
	tree->num++;
}

void BinaryTree_Visit(ThreadNode* node)
{
	if (node)
	{
		std::cout << node->name << " ";
	}
	else
	{
		std::cout << "TreeNode is not exist" << std::endl;
		exit(0);
	}

}

static ThreadNode* pre = NULL;///����ָ�룬ָ���߼�ǰ��
void BinaryTree_Thread_Inorder(ThreadNode* node)
{	/// <summary>
	/// ���ø���ָ��ָ���߼�ǰ���ڵ�
	/// ���ҵ�������㣬
	/// �ڵݹ����������ͬʱ�������Ϊ��ʱ�������
	/// 
	/// </summary>
	/// <param name="node"></param>
	if (node)
	{
		BinaryTree_Thread_Inorder(node->left);
		if (node->left==NULL)
		{///��λ���߼����
			node->Thread_left = true;
			node->left = pre;
		}
		if (pre && pre->right == NULL)
		{///ͨ�������ڵ�����߼���̵�����
			pre->Thread_right = true;
			pre->right = node;
		}
		pre = node;///���߼���̽ڵ��ƶ�
		BinaryTree_Thread_Inorder(node->right);
	}
}

void BinaryTree_Traversal_Inorder_Thread(ThreadNode* node)
{	/// <summary>
	/// ���������Ż���������
	/// ���ҵ��߼���㣬��ʼѭ��������(�ؼ�˼·)
	/// ��������ʱֱ�����߼�����ƶ�������
	/// ����������ʱ���Һ��Ӽ������߼�������������
	/// (���������߼���㣬ͨ��������������������)
	/// </summary>
	/// <param name="node"></param>
	while (node)
	{
		while (node->Thread_left == false)
			node = node->left;///��λ���߼����
		BinaryTree_Visit(node);
		while (node->Thread_right==true&&node->right)
		{///��������ʱֱ�����߼�����ƶ��ٷ���
			node = node->right;
			BinaryTree_Visit(node);
		}
		node = node->right;///����������ʱ����ƶ��ӽ�
	}
}


