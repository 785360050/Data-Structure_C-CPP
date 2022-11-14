#include "../API/Tree_Advanced_B_Tree.h"


B_Node* B_Tree_Create_Node(int order)
{
	B_Node* n = new B_Node;
	n->length = 0;
	n->maxsize = order + 1;
	n->key = new int[order + 1];		///多一个元素空间用于预存
	n->index = new B_Node[order + 1];
	for (int i = 0; i < order + 1; i++)
		n = nullptr;
	n->parent = nullptr;
}

B_Tree* B_Tree_Init(B_Tree* tree, int order)
{///未完成
	tree->order = order;
	tree->count = 0;
}

void B_Tree_Destroy(B_Tree* tree);

void B_Tree_Visit(B_Node* node)
{
	if (node)
	{
		for (int i = 0; i < node->maxsize; i++)
		{
			std::cout << node->key << ' ';
			if (node->index[i])
				B_Tree_Visit(node->index[i]);
		}
	}
}









