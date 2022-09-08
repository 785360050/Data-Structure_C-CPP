#include "../API/Liner_Queue.h"
#include "../API/Liner_Stack.h"

#include "../API/Tree_Binary.h"



struct TQueue
{
	TNode* data[20];
	int front;
	int rear;
};
typedef struct TQueue TQueue;

///顺序队列
TQueue* TQueue_Init()
{
	TQueue* q = new TQueue;
	if (q)
	{
		//memset(q->data, 0, sizeof(q->data));
		q->front = 0;
		q->rear = 0;
	}

	return q;
}

void TQueue_Destory(TQueue* TQueue)
{
	if (TQueue)
		//if (TQueue->data)
		//{
		//	free(TQueue->data);
		//}			
		//此处应为非malloc申请的空间，而是定义的data[maxsize]，free(TQueue->data)后SeqQueue->data是野指针，所以无法free(TQueue)
		free(TQueue);
}

bool TQueue_CheckFull(TQueue* TQueue)
{
	if ((TQueue->rear + 1 ) % 20 == TQueue->front)
	{
		return true;
	}
	return false;
}

void TQueue_Push(TQueue* TQueue, TNode* node)
{
	try
	{
		if (!TQueue )
			throw 1;
		if (TQueue_CheckFull(TQueue))
			throw 2;
	}
	catch (...)
	{
		std::cout << "TQueue is not exist || Queue is Full" << std::endl;
		exit(0);
	}
	TQueue->data[TQueue->rear] = node;
	TQueue->rear = (TQueue->rear + 1) % maxsize;

}

TNode* TQueue_Pop(TQueue* TQueue)
{
	try
	{
		if (TQueue->front == TQueue->rear)
		{
			throw 1;
		}
	}
	catch (...)
	{
		std::cout << "Queue is empty" << std::endl;
		exit(0);
	}
	TNode* t = TQueue->data[TQueue->front];
	TQueue->front = (TQueue->front + 1) % maxsize;
	return t;
}














BTree* BinaryTree_Init_Root(TNode* root)
{
	BTree* t = new BTree;
	t->num = 1;
	t->root = root;
	return t;
}

TreeNode* BinaryTree_CreateNode(std::string name )
{
	TreeNode* n = new TreeNode;
	n->left = n->right = nullptr;
	n->name = name;
	return n;
}

void BinaryTree_Insert(BTree* tree, TNode* parent, Direction pos, TNode* node)
{
	pos == right ?
		parent->right = node : parent->left = node;
	tree->num++;
	
}

void BinaryTree_Visit(TNode* node)
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


void BinaryTree_Traversal_Level(BTree* tree)
{
	TQueue* q = TQueue_Init();
	TQueue_Push(q, tree->root);
	int length = (q->rear - q->front+20) % 20;
	TNode* n ;
	while (length>=0)
	{
		n =TQueue_Pop(q);
		BinaryTree_Visit(n);
		if (n->left)
			TQueue_Push(q, n->left);
		if (n->right)
			TQueue_Push(q, n->right);
	}
	TQueue_Destory(q);
}

void BinaryTree_Traversal_Preorder(TNode* node)
{
	if (node)
	{
		BinaryTree_Visit(node);//D
		BinaryTree_Traversal_Preorder(node->left);//L
		BinaryTree_Traversal_Preorder(node->right);//R
	}
}

void BinaryTree_Traversal_Inorder(TNode* node)
{
	if (node)
	{
		BinaryTree_Traversal_Inorder(node->left);//L
		BinaryTree_Visit(node);//D
		BinaryTree_Traversal_Inorder(node->right);//R
	}
}

void BinaryTree_Traversal_Postorder(TNode* node)
{
	if (node)
	{
		BinaryTree_Traversal_Postorder(node->left);//L
		BinaryTree_Traversal_Postorder(node->right);//R
		BinaryTree_Visit(node);//D
	}
}









