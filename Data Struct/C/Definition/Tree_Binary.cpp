#include "../API/Liner_Queue.h"
#include "../API/Liner_Stack.h"

#include "../API/Tree_Binary.h"


//����˳����� maxsize=20
struct TQueue
{
	TNode* data[20];
	int front;
	int rear;
};
typedef struct TQueue TQueue;

///˳�����
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
		//�˴�ӦΪ��malloc����Ŀռ䣬���Ƕ����data[maxsize]��free(TQueue->data)��SeqQueue->data��Ұָ�룬�����޷�free(TQueue)
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

//����˳��ջ	maxsize=20

//������ջ(top=0ջ��)


struct TStack
{
	TNode* data[20];
	int top;
};
typedef struct TStack TStack;

TStack* TStack_Init()
{
	TStack* s = new TStack;
	memset(s->data, 0, sizeof(s->data));
	s->top = 0;
	return s;
}

void TStack_Destroy(TStack* stack)
{
	delete stack;
}

void TStack_Push(TStack* stack, TNode* node)
{
	try
	{
		if (stack->top >= 20)
		{
			throw "overflow";
		}
	}
	catch (...)
	{
		std::cout << "Stack is Full" << std::endl;
		exit(0);
	}
	stack->data[stack->top] = node;
	stack->top++;
}

TNode* TStack_Pop(TStack* stack)
{
	try
	{
		if (stack->top < 0)
		{
			throw 1;
		}
	}
	catch (...)
	{
		std::cout << "Stack is Empty" << std::endl;
		exit(0);
	}
	stack->top--;
	return stack->data[stack->top];
}



//����������

BTree* BinaryTree_Init_Root(TNode* root)
{
	BTree* t = new BTree;
	t->num = 1;
	t->root = root;
	return t;
}

static void DeleteNode(BTree* tree , TNode* node)
{
	if (node)
	{
		DeleteNode(tree, node->left);
		DeleteNode(tree, node->right);
		std::cout << node->name << " ";
		free(node);
		tree->num--;
	}
}
void BinaryTree_Destory(BTree* tree)
{///���¶��ϵݹ����ٽڵ�
	if (tree)
	{
		std::cout << "ɾ�����������ڵ����:" << tree->num << std::endl;
		if (tree->root)
			DeleteNode(tree, tree->root);
	}
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


void BinaryTree_Traversal_Preorder_NoneRecursion(TNode* node)
{
	/// <summary>
	/// ����˳��ջʵ�ֵݹ����ԣ��ݹ���ջ�Ϸ���ռ䣬�ǵݹ��ջ�ڶ��Ϸ���ռ�
	/// DLR
	/// ��������ջ��ʼѭ��
	/// ÿ�γ�ջ�����ʽڵ㣬��RL��ջ(Ϊ��֤��ջ��L��R��������ջ��R��L)
	/// ջ��Ϊֹ
	/// ����˳��ջ
	/// </summary>
	/// <param name="node"></param>
	TNode* visit;
	if (node)
	{
		TStack* stack = TStack_Init();
		TStack_Push(stack, node);
		while (stack->top>0)
		{
			visit = TStack_Pop(stack);
			BinaryTree_Visit(visit);
			if (visit->right)
				TStack_Push(stack, visit->right);
			if (visit->left)
				TStack_Push(stack, visit->left);
		}
		TStack_Destroy(stack);
	}
}

void BinaryTree_Traversal_Inorder_NoneRecursion(TNode* node)
{
	/// <summary>
	/// ����˳��ջʵ�ֵݹ����ԣ��ݹ���ջ�Ϸ���ռ䣬�ǵݹ��ջ�ڶ��Ϸ���ռ�
	/// LDR
	/// ������� ��ʼѭ��
	/// ÿ���ƶ���L����ջ��ֱ��LΪ��ʱ��ջ������(��˫�׽ڵ�)�����ƶ���R����ջ(˫�׵�R)
	/// </summary>
	/// <param name="node"></param>
	if (node)
	{
		TNode* n = node;
		TStack* stack = TStack_Init();
		while (stack->top > 0 || n)
		{
			if (n)
			{
				TStack_Push(stack, n);
				n = n->left;
			}
			else
			{
				TNode* v = TStack_Pop(stack);
				BinaryTree_Visit(v);
				n = v->right;
			}
		}
		TStack_Destroy(stack);
	}
}

void BinaryTree_Traversal_Postorder_NoneRecursion(TNode* node)
{
	/// <summary>
	/// ��������ջʵ�ֵݹ����ԣ�s1��¼ÿ��������ͷ�ڵ㣬s2��¼ͷ�ڵ�����Һ���
	/// �����ڵ�����ջs1
	/// ÿ�δ�s1��ջ��ѹ��s2ջ,ͬʱѹ��s1�ýڵ����L��R�ڵ�(Ϊ��֤s2��ջ��L��R��D��s1Ӧ����L��Rѹ��)
	/// ֱ��s1Ϊ��ʱ������˫�׽ڵ�(�����нڵ�)��ѹ��s2
	/// ��ʱs2��ջʱ�Ѿ���֤��L��R��D�����γ�ջ������
	/// </summary>
	/// <param name="node"></param>
	TStack* s1 = TStack_Init();
	TStack* s2 = TStack_Init();
	TNode* n;
	TStack_Push(s1, node);
	while (s1->top>0)
	{
		n = TStack_Pop(s1);
		TStack_Push(s2, n);
		if (n->left)
			TStack_Push(s1, n->left);
		if (n->right)
			TStack_Push(s1, n->right);
	}
	while (s2->top > 0)
		BinaryTree_Visit(TStack_Pop(s2));
	TStack_Destroy(s1);
	TStack_Destroy(s2);
}



/*����������
ThreadNode* BinaryTree_CreateNode_Thread(std::string name)
{
	ThreadNode* tnode = new ThreadNode;
	tnode->data = 0;
	tnode->Thread_Left = tnode->Thread_Right = false;
	tnode->name = name;
	return tnode;
}
//BinaryTree_Destory

void BinaryTree_Insert_Thread(BTree* tree, ThreadNode* parent, Direction pos, ThreadNode* node)
{
	
}
//����node�ڵ�
void BinaryTree_Visit_Thread(ThreadNode* node)
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

void BinaryTree_Modify_ThreadTree(ThreadNode* node);

void BinaryTree_Traversal_Thread_Inorder(ThreadNode* node);

*/


