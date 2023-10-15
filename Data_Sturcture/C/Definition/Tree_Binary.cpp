#include "../API/Liner_Queue.h"
#include "../API/Liner_Stack.h"

#include "../API/Tree_Binary.h"

#include <cstring>

//复制顺序队列 maxsize=20
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

//复制顺序栈	maxsize=20

//递增满栈(top=0栈空)


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



//二叉树函数

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
{///自下而上递归销毁节点
	if (tree)
	{
		std::cout << "删除二叉树树节点个数:" << tree->num << std::endl;
		if (tree->root)
			DeleteNode(tree, tree->root);
	}
}

TNode* BinaryTree_CreateNode(std::string name)
{
	TNode* n = new TNode;
	n->left = n->right = nullptr;
	n->name = name;
	return n;
}
TNode* BinaryTree_CreateNode(DataType data)
{
	TNode* n = new TNode;
	n->left = n->right = nullptr;
	n->data = data;
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
void BinaryTree_Visit_Data(TNode* node)
{
	if (node)
	{
		std::cout << node->data << " ";
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
void BinaryTree_Traversal_Inorder_Data(TNode* node)
{
	if (node)
	{
		BinaryTree_Traversal_Inorder_Data(node->left);//L
		BinaryTree_Visit_Data(node);//D
		BinaryTree_Traversal_Inorder_Data(node->right);//R
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
	/// 利用顺序栈实现递归特性，递归在栈上分配空间，非递归的栈在堆上分配空间
	/// DLR
	/// 从树根入栈开始循环
	/// 每次出栈并访问节点，将RL入栈(为保证出栈先L再R，所以入栈先R再L)
	/// 栈空为止
	/// 销毁顺序栈
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

void BinaryTree_Traversal_Inorder_NonRecursive(TNode* node)
{
	/// <summary>
	/// 利用顺序栈实现递归特性，递归在栈上分配空间，非递归的栈在堆上分配空间
	/// LDR
	/// 树根入队 开始循环
	/// 每次移动至L并入栈，直到L为空时出栈并访问(出双亲节点)，再移动到R并入栈(双亲的R)
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

void BinaryTree_Traversal_Postorder_NonRecursive(TNode* node)
{
	/// <summary>
	/// 利用两个栈实现递归特性，s1记录每个子树的头节点，s2记录头节点的左右孩子
	/// 树根节点先入栈s1
	/// 每次从s1出栈并压入s2栈,同时压入s1该节点的先L后R节点(为保证s2出栈先L后R再D，s1应该先L后R压入)
	/// 直到s1为空时，所有双亲节点(即所有节点)都压入s2
	/// 此时s2出栈时已经保证先L后R再D，依次出栈并访问
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


