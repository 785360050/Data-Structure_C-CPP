#include <iostream>



#define C
//#define CPP

#ifdef C
///C
#include "C/API/Liner_List_Link.h"
#include "C/API/Liner_List_Sequential.h"
#include "C/API/Liner_List_Hash.h"
#include "C/API/Liner_Stack.h"
#include "C/API/Liner_Queue.h"
#include "C/API/Tree_Binary.h"
#include "C/API/Tree_Binary_Thread.h"
#include "C/API/Tree_Binary_Search.h"
#include "C/API/Tree_Binary_AVL.h"
#include "C/API/Tree_Binary_BRT.h"
#include "C/API/Tree_MergeFind_Set.h"
#include "C/API/Graph_matrix.h"
#include "C/API/Graph_AdjacencyList.h"
#include "C/Algorithm/Graph_MininumSpanningTree.h"
#include "C/API/Graph_EdgeSetList.h"
#include "C/Algorithm/Graph_ShortestPath_Dijkstra.h"
#include "C/Algorithm/Graph_TopoSort.h"
#include "C/Algorithm/Graph_CriticalPath.h"
#include "C/API/Tree_Binary_Heap.h"
#include "C/API/Tree_Advanced_B_Tree.h"
#include "C/API/Tree_Advanced_B+_Tree.h"
#include "C/API/String.h"

///C function
void TestSeqList()
{
	SeqList* L = SeqList_Init(10);
	SeqList_Show(L);
	for (int i = 1; i <= 5; i++)
		SeqList_Insert(L, i, i);
	std::cout << SeqList_Delete(L, 3) << std::endl;
	SeqList_Update(L, 9, 9);
	SeqList_Show(L);
	std::cout << "元素9的索引位置是：" << SeqList_Element_Locate(L, 9) << std::endl;
	SeqList_Destroy(L);
}
void TestLinkList()
{
	/// <summary>
	/// 测试链表的函数
	/// </summary>
	LinkList* L = LinkList_Init();
	for (int i = 1; i <= 10; i++)
		LinkList_AddNode_front(L, i);
	//LinkList_AddNode_rear(L, e);
	LinkList_Show(L);


	LinkList_InsertNode(L, 2, 2);
	LinkList_Show(L);
	ListNode* s = (ListNode*)malloc(sizeof(ListNode));
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	s = LinkList_LocateNode(L, 2);
	std::cout << LinkList_GetElem(s) << std::endl;
	p = LinkList_PriNode(L, s);
	std::cout << LinkList_GetElem(p) << std::endl;
	LinkList_DeleteList(L);

}
void TestHashList()
{
	//线性探测法解决冲突
	std::cout << "线性探测法解决冲突" << std::endl;
	HashList* h = new HashList;
	HashList_Init(h, 5);
	HashList_Show(h);
	HashList_Insert(h, 1);
	HashList_Insert(h, 2);
	HashList_Insert(h, 7);
	HashList_Insert(h, 12);
	HashList_Insert(h, 17);
	HashList_Show(h);

	std::cout << "key为12的下标索引为:" << HashList_Locate(h, 12) << std::endl;
	std::cout << "key为2的下标索引为:" << HashList_Locate(h, 2) << std::endl;
	std::cout << "key为17的下标索引为:" << HashList_Locate(h, 17) << std::endl;

	HashList_Destroy(h);

	///——————————————————————————
	std::cout << std::endl;
	//链地址法解决冲突
	std::cout << "链地址法解决冲突" << std::endl;
	HashList_Link* h2 = new HashList_Link;
	HashList_Init(h2, 5);
	HashList_Show(h2);

	HashList_Insert(h2, 1);
	HashList_Insert(h2, 2);
	HashList_Insert(h2, 3);
	HashList_Insert(h2, 4);
	HashList_Insert(h2, 5);
	HashList_Insert(h2, 7);
	HashList_Insert(h2, 12);
	HashList_Insert(h2, 23);
	HashList_Show(h2);

	std::cout << "key为12的下标索引为:" << HashList_Locate(h2, 12) << std::endl;
	std::cout << "key为23的下标索引为:" << HashList_Locate(h2, 23) << std::endl;

	HashList_Destroy(h2);
}

void TestSeqStack()
{
	SeqStack* s = SeqStack_Init(5);
	for (int i = 0; i < StackSize; i++)
	{
		SeqStack_Push(s, i);
	}
	for (int i = 0; i < StackSize; i++)
		std::cout << s->data[i] << " ";
	std::cout << std::endl;
	DataType x;
	while (s->top > 0)
	{
		x = SeqStack_Pop(s);
		std::cout << x << " ";
	}

	SeqStack_Destroy(s);
}
void TestLinkStack()
{
	LinkStack* S = LinkStack_Init();
	for (int i = 0; i < 5; i++)
	{
		LinkStack_Push(S, i);
	}
	LinkStack_Push(S, 1);
	while (S->next)
	{
		std::cout << LinkStack_Pop(S) << std::endl;
	}
	LinkStack_Destroy(S);
}

void TestSeqQueue()
{
	SeqQueue* q;
	q = SeqQueue_Init();
	for (int i = 1; i < 6; i++)
	{
		SeqQueue_Push(q, i);
	}
	while (q->front != q->rear)
	{
		std::cout << SeqQueue_Pop(q) << std::endl;
	}
	SeqQueue_Destory(q);

}
void TestLinkQueue()
{
	LinkQueue* q = LinkQueue_Init();
	for (int i = 1; i <= 5; i++)
	{
		LinkQueue_Push(q, i);
	}
	while (q->length > 0)
	{
		std::cout << LinkQueue_Pop(q) << std::endl;
	}
	LinkQueue_Destroy(q);
}

void BinaryTree()
{
	TNode* a = BinaryTree_CreateNode("A");
	TNode* b = BinaryTree_CreateNode("B");
	TNode* c = BinaryTree_CreateNode("C");
	TNode* d = BinaryTree_CreateNode("D");
	TNode* e = BinaryTree_CreateNode("E");
	TNode* f = BinaryTree_CreateNode("F");
	TNode* g = BinaryTree_CreateNode("G");
	TNode* h = BinaryTree_CreateNode("H");
	TNode* k = BinaryTree_CreateNode("K");

	BTree* Tree = BinaryTree_Init_Root(a);

	BinaryTree_Insert(Tree, a, left, b);
	BinaryTree_Insert(Tree, a, right, e);
	BinaryTree_Insert(Tree, b, right, c);
	BinaryTree_Insert(Tree, c, left, d);
	BinaryTree_Insert(Tree, e, right, f);
	BinaryTree_Insert(Tree, f, left, g);
	BinaryTree_Insert(Tree, g, left, h);
	BinaryTree_Insert(Tree, g, right, k);

	std::cout << "非递归：";
	std::cout << std::endl << "DLR：";
	BinaryTree_Traversal_Preorder_NoneRecursion(Tree->root);
	std::cout << std::endl << "LDR：";
	BinaryTree_Traversal_Inorder_NonRecursive(Tree->root);
	std::cout << std::endl << "LRD：";
	BinaryTree_Traversal_Postorder_NonRecursive(Tree->root);

	std::cout << std::endl << std::endl << "递归：";
	std::cout << std::endl << "DLR：";
	BinaryTree_Traversal_Preorder(Tree->root);
	std::cout << std::endl << "LDR：";
	BinaryTree_Traversal_Inorder(Tree->root);
	std::cout << std::endl << "LRD：";
	BinaryTree_Traversal_Postorder(Tree->root);
	//std::cout << std::endl << "Level：";
	//BinaryTree_Traversal_Level(Tree);
	///BUG
	std::cout << std::endl;
	BinaryTree_Destory(Tree);
}
void BinaryThreadTree()
{
	ThreadNode* a = BinaryTree_CreateNode_Thread("A");
	ThreadNode* b = BinaryTree_CreateNode_Thread("B");
	ThreadNode* c = BinaryTree_CreateNode_Thread("C");
	ThreadNode* d = BinaryTree_CreateNode_Thread("D");
	ThreadNode* e = BinaryTree_CreateNode_Thread("E");
	ThreadNode* f = BinaryTree_CreateNode_Thread("F");
	ThreadNode* g = BinaryTree_CreateNode_Thread("G");
	ThreadNode* h = BinaryTree_CreateNode_Thread("H");
	ThreadNode* k = BinaryTree_CreateNode_Thread("K");

	BTree_Thread* Tree = BinaryTree_Init_Root(a);

	BinaryTree_Insert_Thread(Tree, a, left, b);
	BinaryTree_Insert_Thread(Tree, a, right, e);
	BinaryTree_Insert_Thread(Tree, b, right, c);
	BinaryTree_Insert_Thread(Tree, c, left, d);
	BinaryTree_Insert_Thread(Tree, e, right, f);
	BinaryTree_Insert_Thread(Tree, f, left, g);
	BinaryTree_Insert_Thread(Tree, g, left, h);
	BinaryTree_Insert_Thread(Tree, g, right, k);

	BinaryTree_Thread_Inorder(Tree->root);

	BinaryTree_Traversal_Inorder_Thread(Tree->root);

	std::cout << std::endl;
	BinaryTree_Destory(Tree);
}

void BinarySearch()
{
	TNode* d = BinaryTree_CreateNode(4);

	BTree* Tree = BinaryTree_Init_Root(d);

	///递归插入
	//BinaryTree_Search_Insert(Tree, 2);
	//BinaryTree_Search_Insert(Tree, 1);
	//BinaryTree_Search_Insert(Tree, 3);
	//BinaryTree_Search_Insert(Tree, 6);
	//BinaryTree_Search_Insert(Tree, 5);
	//BinaryTree_Search_Insert(Tree, 7);

	///非递归插入
	BinaryTree_Search_Insert_NonRecursive(Tree, 2);
	BinaryTree_Search_Insert_NonRecursive(Tree, 1);
	BinaryTree_Search_Insert_NonRecursive(Tree, 3);
	BinaryTree_Search_Insert_NonRecursive(Tree, 6);
	BinaryTree_Search_Insert_NonRecursive(Tree, 5);
	BinaryTree_Search_Insert_NonRecursive(Tree, 7);

	BinaryTree_Order_Increase(Tree->root);

	TNode* node = BinaryTree_Search_LocateElement(Tree, 7);///查找测试
	if (node)
		std::cout << std::endl << "Node Found" << std::endl;
	else
		std::cout << std::endl << "Node Not Found" << std::endl;

	std::cout << std::endl << "After Delete 2" << std::endl;
	BinaryTree_Search_Delete(Tree->root, 2);
	BinaryTree_Order_Increase(Tree->root);
	std::cout << std::endl << "After Delete 4" << std::endl;
	BinaryTree_Search_Delete(Tree->root, 4);
	BinaryTree_Order_Increase(Tree->root);
	BinaryTree_Destory(Tree);
}
void BinarySearch_AVL()
{
	BinaryTree_AVL* Tree = BinaryTree_Init_Root_AVL();
	BinaryTree_Insert_AVL(Tree, 8);
	BinaryTree_Insert_AVL(Tree, 4);
	BinaryTree_Insert_AVL(Tree, 2);
	BinaryTree_Insert_AVL(Tree, 6);
	BinaryTree_Insert_AVL(Tree, 9);
	//std::cout << Tree->num << std::endl;
	BinaryTree_Traversal_Inorder_AVL(Tree->root);
	BinaryTree_AVL_Delete(Tree, Tree->root, 8);
	std::cout << std::endl;
	BinaryTree_Traversal_Inorder_AVL(Tree->root);
	BinaryTree_Destory(Tree);
}
//void BinarySearch_RBT()
//{
//	RBTree* tree = BRT_Init();
//
//	RBNode* a = RBNode_Create(8);
//	RBNode* b = RBNode_Create(5);
//	RBNode* c = RBNode_Create(15);
//	RBNode* d = RBNode_Create(12);
//	RBNode* e = RBNode_Create(19);
//	RBNode* f = RBNode_Create(9);
//	RBNode* g = RBNode_Create(13);
//	RBNode* h = RBNode_Create(23);
//
//	RBTree_RBNode_Insert(tree, a);
//	RBTree_RBNode_Insert(tree, b);
//	RBTree_RBNode_Insert(tree, c);
//	RBTree_RBNode_Insert(tree, d);///叔红 变色父、祖父、叔节点
//	RBTree_RBNode_Insert(tree, e);
//	RBTree_RBNode_Insert(tree, f);///叔红 变色父、祖父、叔节点
//	RBTree_RBNode_Insert(tree, g);
//	RBTree_RBNode_Insert(tree, h);
//	/////叔红->变色;切换视角为12节点 RL->右旋父节点+左旋祖父节点+变色父、祖父
//
//	RBTree_RBNode_Delete(tree, 15);
//	RBTree_RBNode_Delete(tree, 19);
//	RBTree_RBNode_Delete(tree, 13);
//	RBTree_RBNode_Delete(tree, 23);
//
//	
//
//	std::cout << "\nDLR:";
//	RBTree_Traverse_Preorder(tree->root);
//	std::cout << "\nLDR:";
//	RBTree_Traverse_Inorder(tree->root);
//
//	std::cout <<std::endl<<"\n搜索节点9：目标节点值为" << RBTree_Search(tree, 9)->key;
//
//	RBTree_Destroy(tree);
//}

void BinarySearch_RBT()
{
	RBTree* tree = BRT_Init();

	RBNode* a = RBNode_Create(4);
	RBNode* b = RBNode_Create(2);
	RBNode* c = RBNode_Create(1);
	RBNode* d = RBNode_Create(3);
	RBNode* e = RBNode_Create(6);
	RBNode* f = RBNode_Create(5);
	RBNode* g = RBNode_Create(7);
	//RBNode* h = RBNode_Create(23);

	RBTree_RBNode_Insert(tree, a);
	RBTree_RBNode_Insert(tree, b);
	RBTree_RBNode_Insert(tree, c);
	RBTree_RBNode_Insert(tree, d);///叔红 变色父、祖父、叔节点
	RBTree_RBNode_Insert(tree, e);
	RBTree_RBNode_Insert(tree, f);///叔红 变色父、祖父、叔节点
	RBTree_RBNode_Insert(tree, g);
	//RBTree_RBNode_Insert(tree, h);
	/////叔红->变色;切换视角为12节点 RL->右旋父节点+左旋祖父节点+变色父、祖父

	RBTree_RBNode_Delete(tree, 2);
	RBTree_RBNode_Delete(tree, 4);
	//RBTree_RBNode_Delete(tree, 13);
	//RBTree_RBNode_Delete(tree, 23);



	//std::cout << "\nDLR:";
	//RBTree_Traverse_Preorder(tree->root);
	//std::cout << "\nLDR:";
	//RBTree_Traverse_Inorder(tree->root);

	//std::cout << std::endl << "\n搜索节点9：目标节点值为" << RBTree_Search(tree, 9)->key;

	RBTree_Destroy(tree);




	//tree->Tree_Traverse_InOrder(tree->Tree_GetRoot());

	//std::cout << std::endl << "Search node: name == \"7\"" << std::endl;
	//auto node = tree->Node_Search("7");///查找测试
	//std::cout << ((node->name == "7") ? "Node Founded" : "Node Not Found") << std::endl;

	//tree->Element_Delete(2);
	//std::cout << "After Delete 2" << std::endl;
	//tree->Tree_Traverse_InOrder(tree->Tree_GetRoot());
	//tree->Element_Delete(4);
	//std::cout << std::endl;
	//std::cout << "After Delete 4" << std::endl;
	//tree->Tree_Traverse_InOrder(tree->Tree_GetRoot());
}

void Binary_Heap()
{
	BinaryHeap* h = new BinaryHeap;
	BinaryHeap_Init(h, 5);
	std::cout << "堆的顺序数组首个空间不使用" << std::endl;
	BinaryHeap_Show(h);
	BinaryHeap_Element_Insert(h, 1);
	BinaryHeap_Element_Insert(h, 2);
	BinaryHeap_Element_Insert(h, 3);
	BinaryHeap_Element_Insert(h, 4);
	BinaryHeap_Element_Insert(h, 5);
	//BinaryHeap_Element_Insert(h, 6);

	BinaryHeap_Show(h);

	BinaryHeap_Root_Extract(h);
	BinaryHeap_Show(h);

	BinaryHeap_Destroy(h);
}

void Test_B_Tree()
{
	B_Tree* tree = new B_Tree;
	B_Tree_Init(tree, 5);

	for (int i = 1; i < 21; ++i)
	{
		B_Tree_Insert(tree, i);
		//B_Tree_Show(tree, "");
	}
	B_Tree_Show(tree, "After Insert 1-20");
	
	B_Tree_Delete(tree, 20);
	B_Tree_Show(tree, "After Delete 20");
	B_Tree_Delete(tree, 14);
	B_Tree_Show(tree, "After Delete 14");
	B_Tree_Delete(tree, 15);
	B_Tree_Show(tree, "After Delete 15");
	B_Tree_Delete(tree, 17);
	B_Tree_Show(tree, "After Delete 17");
	B_Tree_Delete(tree, 2);
	B_Tree_Show(tree, "After Delete 2");
	B_Tree_Delete(tree, 7);
	B_Tree_Show(tree, "After Delete 7");
	B_Tree_Delete(tree, 9);
	B_Tree_Show(tree, "After Delete 9");

	std::cout << std::endl;
	B_Tree_Destroy(tree);
}

int Test_BPlus_Tree()
{
	BPlus_Tree* tree= BPlus_Tree_Init();
	for (int i = 0; i < 30; i++)
		BPlus_Tree_Insert(tree, i, 1);
	
	BPlus_Tree_Show(tree);

	printf("\n删除元素\n");

	BPlus_Tree_Delete(tree, 1);
	BPlus_Tree_Delete(tree, 2);
	BPlus_Tree_Delete(tree, 3);
	BPlus_Tree_Delete(tree, 4);
	BPlus_Tree_Delete(tree, 5);
	BPlus_Tree_Delete(tree, 6);
	BPlus_Tree_Delete(tree, 7);
	BPlus_Tree_Delete(tree, 8);
	BPlus_Tree_Delete(tree, 9);
	BPlus_Tree_Delete(tree, 10);
	BPlus_Tree_Delete(tree, 11);
	BPlus_Tree_Delete(tree, 12);
	BPlus_Tree_Delete(tree, 26);
	BPlus_Tree_Delete(tree, 25);
	BPlus_Tree_Delete(tree, 23);
	BPlus_Tree_Show(tree);

}

void TestBinaryTree()
{
	//BinaryTree();
	//BinaryThreadTree();
	//BinarySearch();
	//BinarySearch_AVL();
	BinarySearch_RBT();
	//Binary_Heap();
}

void TestMergeFindSet()
{
	int n = 5;
	DataType data[5] = { 0,1,2,3,4 };

	///——————————————————QucikFind
	MFSet_QuickFind* set_QF = Set_Create_QuickFind(n);
	Set_Init(set_QF, data, n);
	Merge(set_QF, 0, 2);
	Merge(set_QF, 4, 2);
	std::cout << Find(set_QF, 0, 2) << std::endl;
	std::cout << Find(set_QF, 1, 2) << std::endl;
	Set_Show(set_QF);
	Set_Destroy(set_QF);

	///———————————————————QuickMerge
	MFSet_QuickMerge* set_QM = Set_Create_QuickMerge(n);
	Set_Init(set_QM, data, n);
	Set_Show(set_QM);
	Merge(set_QM, 0, 2);
	Merge(set_QM, 4, 2);
	Merge(set_QM, 1, 3);
	std::cout << Find(set_QM, 0, 2) << std::endl;
	std::cout << Find(set_QM, 1, 2) << std::endl;
	Set_Show(set_QM);
	std::cout << "RootIndex(2)= " << RootIndex(set_QM, 2) << std::endl;
	std::cout << "RootIndex(2)= " << RootIndex_Optimized(set_QM, 2) << std::endl;
	Set_Destroy(set_QM);

}

void TestMatrixGraph()
{
	Graph_matrix* g = new Graph_matrix;
	Graph_Init(g, 8, false);//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
	Graph_Edge_Add(g, 0, 1, 1);
	Graph_Edge_Add(g, 0, 2, 1);
	Graph_Edge_Add(g, 1, 3, 1);
	Graph_Edge_Add(g, 1, 4, 1);
	Graph_Edge_Add(g, 3, 7, 1);
	Graph_Edge_Add(g, 4, 7, 1);
	Graph_Edge_Add(g, 2, 6, 1);
	Graph_Edge_Add(g, 2, 5, 1);
	Graph_Edge_Add(g, 5, 6, 1);
	

	Graph_Show_Matrix(g);

	std::cout << "DFS" << std::endl;
	Graph_Traverse_DFS(g, 0);
	std::cout << std::endl << "BFS" << std::endl;
	Graph_Traverse_BFS(g, 0); 

	Graph_Destroy(g);
}

void TestAdjacencyListGraph()
{
	AdjacencyList* g = new AdjacencyList;
	Graph_AdjacencyList_Init(g, 8, false);//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
	Graph_AdjacencyList_Edge_Add(g, 0, 1, 1);
	Graph_AdjacencyList_Edge_Add(g, 0, 2, 1);
	Graph_AdjacencyList_Edge_Add(g, 1, 3, 1);
	Graph_AdjacencyList_Edge_Add(g, 1, 4, 1);
	Graph_AdjacencyList_Edge_Add(g, 3, 7, 1);
	Graph_AdjacencyList_Edge_Add(g, 4, 7, 1);
	Graph_AdjacencyList_Edge_Add(g, 2, 6, 1);
	Graph_AdjacencyList_Edge_Add(g, 2, 5, 1);
	Graph_AdjacencyList_Edge_Add(g, 5, 6, 1);

	Graph_Show_AdjacencyList(g);

	std::cout << "DFS" << std::endl;
	Graph_AdjacencyList_Traverse_DFS(g, 0);
	Reset_VistedState(g);
	std::cout << std::endl << "BFS" << std::endl;
	Graph_AdjacencyList_Traverse_BFS(g, 0);

	Graph_AdjacencyList_Destroy(g);
}

void TestEdgeSetGraph()
{
	Graph_EdgeSet* g = new Graph_EdgeSet;
	Graph_EdgeSetList_Init(g, 8, false);

	Graph_EdgeSetList_Edge_Add(g, 0, 1, 1);
	Graph_EdgeSetList_Edge_Add(g, 0, 2, 1);
	Graph_EdgeSetList_Edge_Add(g, 1, 3, 1);
	Graph_EdgeSetList_Edge_Add(g, 1, 4, 1);
	Graph_EdgeSetList_Edge_Add(g, 3, 7, 1);
	Graph_EdgeSetList_Edge_Add(g, 4, 7, 1);
	Graph_EdgeSetList_Edge_Add(g, 2, 6, 1);
	Graph_EdgeSetList_Edge_Add(g, 2, 5, 1);
	Graph_EdgeSetList_Edge_Add(g, 5, 6, 1);

	Graph_EdgeSetList_Show(g);

	Graph_EdgeSetList_Edge_Delete(g, 1, 4);
	Graph_EdgeSetList_Edge_Delete(g, 2, 5);

	std::cout << "删除1-4,2-5边后" << std::endl;
	Graph_EdgeSetList_Show(g);

	Graph_EdgeSetList_Destroy(g);
}

void TestMininumSpanningTree()
{
	
	/// Kruskal用边集数组存储方便
	//int Sum = Graph_MininumSpanningTree_Kruskal(g, edgeset, 8, result);
	//std::cout << "最小生成树权值为：" << Sum << std::endl;

	Graph_matrix* g = new Graph_matrix;
	Graph_Init(g, 7, false);//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
	Graph_Edge_Add(g, 0, 1, 12);
	Graph_Edge_Add(g, 0, 5, 16);
	Graph_Edge_Add(g, 0, 6, 14);
	Graph_Edge_Add(g, 1, 2, 10);
	Graph_Edge_Add(g, 1, 5, 7);
	Graph_Edge_Add(g, 6, 5, 9);
	Graph_Edge_Add(g, 6, 4, 8);
	Graph_Edge_Add(g, 5, 4, 2);
	Graph_Edge_Add(g, 5, 2, 6);
	Graph_Edge_Add(g, 2, 4, 5);
	Graph_Edge_Add(g, 2, 3, 3);
	Graph_Edge_Add(g, 3, 4, 4);


	Graph_Show_Matrix(g);

	Graph_matrix* minimum=Graph_MininumSpanningTree_Prim(*g,0);
	std::cout << "获得的最小生成树为：" << std::endl;
	Graph_Show_Matrix(minimum);
	Graph_Destroy(g);
	Graph_Destroy(minimum);
}

void TestShortestPath()
{
	Graph_matrix* g = new Graph_matrix;
	Graph_Init(g, 7, true);
	Graph_Edge_Add(g, 0, 1, 4);
	Graph_Edge_Add(g, 0, 2, 6);
	Graph_Edge_Add(g, 0, 3, 6);
	Graph_Edge_Add(g, 1, 2, 1);
	Graph_Edge_Add(g, 1, 4, 7);
	Graph_Edge_Add(g, 2, 4, 6);
	Graph_Edge_Add(g, 2, 5, 4);
	Graph_Edge_Add(g, 3, 2, 2);
	Graph_Edge_Add(g, 3, 5, 5);
	Graph_Edge_Add(g, 4, 6, 6);
	Graph_Edge_Add(g, 5, 4, 1);
	Graph_Edge_Add(g, 5, 6, 8);

	Graph_Show_Matrix(g);
	ShortestPath_Dijkstra(*g, 0);
}

void TestTopoSort()
{
	AdjacencyList* g = new AdjacencyList;
	Graph_AdjacencyList_Init(g, 6 , true);
	Graph_AdjacencyList_Edge_Add(g, 0, 1, 1);
	Graph_AdjacencyList_Edge_Add(g, 0, 2, 1);
	Graph_AdjacencyList_Edge_Add(g, 0, 3, 1);
	Graph_AdjacencyList_Edge_Add(g, 2, 1, 1);
	Graph_AdjacencyList_Edge_Add(g, 2, 4, 1);
	Graph_AdjacencyList_Edge_Add(g, 3, 4, 1);
	Graph_AdjacencyList_Edge_Add(g, 5, 3, 1);
	Graph_AdjacencyList_Edge_Add(g, 5, 4, 1);

	Graph_Show_AdjacencyList(g);
	TopoSort(g);
}

void TestCriticalPath()
{
	AdjacencyList* g = new AdjacencyList;
	Graph_AdjacencyList_Init(g, 9, true);//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)

	Graph_AdjacencyList_Edge_Add(g, 0, 1, 6);
	Graph_AdjacencyList_Edge_Add(g, 0, 2, 4);
	Graph_AdjacencyList_Edge_Add(g, 0, 3, 5);
	Graph_AdjacencyList_Edge_Add(g, 1, 4, 1);
	Graph_AdjacencyList_Edge_Add(g, 2, 4, 1);
	Graph_AdjacencyList_Edge_Add(g, 3, 5, 2);
	Graph_AdjacencyList_Edge_Add(g, 4, 6, 9);
	Graph_AdjacencyList_Edge_Add(g, 4, 7, 7);
	Graph_AdjacencyList_Edge_Add(g, 5, 7, 4);
	Graph_AdjacencyList_Edge_Add(g, 6, 8, 2);
	Graph_AdjacencyList_Edge_Add(g, 7, 8, 4);
	std::cout << "当前图的邻接表为：" << std::endl;
	Graph_Show_AdjacencyList(g);

	std::cout << "当前图的拓扑排序为：" << std::endl;
	Graph_CriticalPath(g);
	
	delete[] g->vertex;
	delete g;
}

//void TestInsertSort()
//{
//	
//}
#include "C/Algorithm/Sort_TestCase.h"
#include "C/Algorithm/Sort_Insert.h"
#include "C/Algorithm/Sort_Swap.h"
#include "C/Algorithm/Sort_Merge.h"
void TestSort()
{
	int n = 10;
	SortList* l = generateRandomArray(n, 0, n);

	SortList_Show(l);

	//testSort("Directly Insert Sort", Sort_Insert_Direct, l);
	//testSort("Optimized Directly Insert Sort", Sort_Insert_Direct_Optimized, l);
	//testSort("Shell Sort", Sort_Insert_Shell, l);
	//testSort("Bubble Sort", Sort_Bubble_Classic, l);
	//testSort("Bubble Sort Optimized 1", Sort_Bubble_Optimized_1, l);
	//testSort("Bubble Sort Optimized 2", Sort_Bubble_Optimized_2, l);
	//testSort("Quick Sort Double Way", Sort_Quick_DoubleWay, l);
	//testSort("Quick Sort Single Way", Sort_Quick_SingleWay, l);
	//testSort("Heap Sort", Sort_Heap, l);
	testSort("Binary Merge Sort", Sort_Merge, l);

	SortList_Show(l);
	SortList_Destroy(l);

}

void TestCost_Sort()
{
	int n = 10000;
	SortList* l = generateRandomArray(n, 0, n);
	SortList* a = SortList_Copy(l);
	SortList* b = SortList_Copy(l);
	SortList* c = SortList_Copy(l);
	SortList* d = SortList_Copy(l);
	SortList* e = SortList_Copy(l);
	SortList* f = SortList_Copy(l);
	SortList* g = SortList_Copy(l);
	SortList* h = SortList_Copy(l);
	SortList* i = SortList_Copy(l);

	testSort("Directly Insert Sort", Sort_Insert_Direct, l);
	testSort("Optimized Directly Insert Sort", Sort_Insert_Direct_Optimized, a);
	testSort("Shell Sort", Sort_Insert_Shell, b);
	testSort("Bubble Sort", Sort_Bubble_Classic, c);
	testSort("Bubble Sort Optimized 1", Sort_Bubble_Optimized_1, d);
	testSort("Bubble Sort Optimized 2", Sort_Bubble_Optimized_2, e);
	testSort("Quick Sort Double Way", Sort_Quick_DoubleWay, f);
	testSort("Quick Sort Single Way", Sort_Quick_SingleWay, g);
	testSort("Heap Sort", Sort_Heap, h);
	testSort("Binary Merge Sort", Sort_Merge, i);

	SortList_Destroy(l);
	SortList_Destroy(a);
	SortList_Destroy(b);
	SortList_Destroy(c);
	SortList_Destroy(d);
	SortList_Destroy(e);
	SortList_Destroy(f);
	SortList_Destroy(g);
	SortList_Destroy(h);
	SortList_Destroy(i);


}

#include "C/Algorithm/Search_Static_Sequential.h"
void TestSearch()
{
	SearchList* s = new SearchList;
	SearchList_Init(s, 10);
	SearchList_Show(s);

	int result = Search_Sequence(s, 3);
	std::cout << result << std::endl;
	result = Search_Binary(s, 5);
	std::cout << result << std::endl;

}

void Test_String()
{
	String string;
	String Sub_String;
	string.string_ = NULL;
	//String_Init(string, "ABCDABCABCABABCABCDA");
	//String_Init(string, "bacbababaabcbab");
	//String_Init(string, "ABADABABC");
	//String_Init(string, "ABC");
	std::cout << string.string_ << std::endl;
	Sub_String.string_ = NULL;
	//String_Init(Sub_String, "ABCABCD");
	//String_Init(Sub_String, "abababca");
	//String_Init(Sub_String, "ABC");
	//String_Init(Sub_String, "C");
	std::cout << Sub_String.string_ << std::endl;

	std::cout << "Brute Force: " <<
		String_Fetch_Brute_Force(string, Sub_String) << std::endl;
	std::cout << "KMP: " <<
		String_Fetch_KMP(string, Sub_String) << std::endl;

	///——————————————————————————
	/// KMP-BUG
	///——————————————————————————

	String_Destroy(string);
	String_Destroy(Sub_String);
}

void Test_C()
{
	//TestSeqList();//完毕
	//TestLinkList();//完毕
	//TestHashList();//完毕
	//TestSeqStack();//完毕
	//TestLinkStack();//完毕
	//TestSeqQueue();//完毕
	//TestLinkQueue();//完毕
	//TestBinaryTree();//完毕
	//TestMergeFindSet();//完毕
	//TestMatrixGraph();//完毕
	//TestAdjacencyListGraph();//完毕
	//TestEdgeSetGraph();
	//TestMininumSpanningTree();//完毕
	//TestShortestPath();//完毕
	//TestTopoSort();//完毕
	//TestCriticalPath();//完毕
	//TestSort();//完毕
	//TestCost_Sort();//完毕
	//TestSearch();//完毕
	//Test_B_Tree();
	Test_BPlus_Tree();
	//Test_String();//KMP_BUG
}

#endif // C

#ifdef CPP
///C++

#include "C++/Liner_List_Sequential.h"
#include "C++/Liner_List_Link.h"
#include "C++/Liner_Stack_Sequential.h"
#include "C++/Liner_Stack_Linked.h"
#include "C++/Liner_Queue_Sequential.h"
#include "C++/Liner_Queue_Linked.h"
#include "C++/Tree_Binary_Normal.h"


void TestSeqList()
{
	Sequential_List<int> L;
	L.List_Init(5);
	L.List_Show("初始化5个元素空间的顺序表后");

	for (int i = 1; i <= 5; i++)
		L.Element_Insert(i, i);
	L.List_Show("插入5个元素后");

	L.Element_Insert(2, 9);
	L.List_Show("第二个位置插入9后，检测到存储空间已满，扩展空间");

	std::cout << std::endl;
	L.Element_Insert(20, 20);
	L.List_Show("第20个非法位置插入20后");

	std::cout << std::endl;
	L.Element_Update(2, 999);
	L.List_Show("第二个元素改为999后");

	int del;
	del = L.Element_Delete(2);
	L.List_Show("删除第二个元素后");
	std::cout << "删除的第二个元素为:" << del << std::endl;

	std::cout << "获取第二个元素值:" << L.List_GetElement(2) << std::endl;
	
	std::cout << "判空 {0=F,1=T}:" << L.List_CheckEmpty() << std::endl;
	std::cout << "当前表长：" << L.List_GetLength() << std::endl;
	L.List_Clear();
	L.List_Show("清空后");
	std::cout << "当前表长：" << L.List_GetLength() << std::endl;

	L.List_Destroy();
}
void TestLinkList()
{///在堆上而不是栈上新建链表节点(不用构造函数新建)
	List_SingleLinked<int>* L = new List_SingleLinked<int>;
	L->List_Init(5);
	L->List_Show("初始化5个节点后：");
	for (int i = 1; i <= 5; i++)
		L->Insert_Front(i);
	L->List_Show("头插法插入5个节点后：");
	Node_SingleLinked<int>* pri = L->Element_Prior(L->Element_Locate(5));
	std::cout << "第5个元素的前驱节点为: " << pri->element << std::endl;
	Node_SingleLinked<int>* next = L->Element_Next(L->Element_Locate(5));
	std::cout << "第5个元素的后继节点为: " << next->element << std::endl;
	L->Element_Delete(2);
	L->List_Show("删除第2个节点后：");
	L->Element_Insert(2, 2);
	L->List_Show("在第2个节点插入元素2后：");
	L->List_Clear();
	L->List_Show("重置链表后：");
	std::cout << "当前链表长度为: " << L->List_GetLength() << std::endl;
	std::cout << "链表判空: " << L->List_CheckEmpty() << std::endl;
	L->List_Destroy();
}

void TestSequenceStack()
{
	Sequence_Stack<char> s;
	s.Stack_Init(5);
	s.Stack_Show("初始化5个单位的栈空间后：");
	for (int i = 65; i < 70; i++)
		s.Element_Push(i);
	s.Stack_Show("压入5个元素后：");
	//s.Stack_Clear();
	std::cout << "当前栈顶元素为：" << s.Stack_GetTop() << std::endl;
	std::cout << "当前栈长度为：" << s.Stack_GetLength() << std::endl;
	std::cout << "栈判空：" << s.Stack_CheckEmpty() << std::endl;
	while (s.Stack_GetLength() > 0)
	{
		std::cout << s.Element_Pop() <<"出栈" << std::endl;
	}

	std::cout << "栈判空：" << s.Stack_CheckEmpty() << std::endl;
	s.Stack_Destroy();

}
void TestLinkStack()
{
	Link_Stack<char> s;
	int c = 'Z';
	s.Stack_Init(5);
	s.Stack_Show("初始化链栈空间最大为5");
	for (int i = 0; i < 5; i++)
		s.Element_Push(c--);
	s.Stack_Show("插入5个元素后");
	std::cout << "当前栈顶元素为：" << s.Stack_GetTop() << std::endl;
	std::cout << "当前栈长度为：" << s.Stack_GetLength() << std::endl;
	std::cout << "依次出栈" << std::endl;
	while (!s.Stack_CheckEmpty())
		std::cout << s.Element_Pop() << std::endl;
	s.Stack_Destroy();
}

void TestSeqQueue()
{
	Sequence_Queue<int> q;
	q.Queue_Init(5);
	q.Queue_Show("初始化5个队列空间后");
	for (int i = 10; i < 15; i++)
		q.Element_Enqueue(i);
	q.Queue_Show("5个元素入队后");
	std::cout << "当前队头元素为: " << q.Queue_GetHead() << std::endl;
	std::cout << "当前队列长度为: " << q.Queue_Length() << std::endl;
	std::cout << "出队元素为: " << q.Element_Dequeue() << std::endl;
	std::cout << "出队元素为: " << q.Element_Dequeue() << std::endl;
	q.Queue_Show("出队2个元素后：");
	q.Queue_Clear();
	q.Queue_Show("清空队列后");


	q.Queue_Destroy();
}
void TestLinkQueue()
{
	Link_Queue<int> q;
	q.Queue_Init(5);
	q.Queue_Show("初始化5个队列空间后");
	for (int i = 10; i < 15; i++)
		q.Element_Enqueue(i);
	q.Queue_Show("5个元素入队后");
	std::cout << "当前队头元素为: " << q.Queue_GetHead() << std::endl;
	std::cout << "当前队列长度为: " << q.Queue_Length() << std::endl;
	std::cout << "出队元素为: " << q.Element_Dequeue() << std::endl;
	std::cout << "出队元素为: " << q.Element_Dequeue() << std::endl;
	q.Queue_Show("出队2个元素后：");
	q.Queue_Clear();
	q.Queue_Show("清空队列后");
}

void TestBinaryTree()
{
	Binary_Tree<bool> tree;


	Node_BinaryTree<bool>* a = tree.Node_Create("A");
	Node_BinaryTree<bool>* b = tree.Node_Create("B");
	Node_BinaryTree<bool>* c = tree.Node_Create("C");
	Node_BinaryTree<bool>* d = tree.Node_Create("D");
	Node_BinaryTree<bool>* e = tree.Node_Create("E");
	Node_BinaryTree<bool>* f = tree.Node_Create("F");
	Node_BinaryTree<bool>* g = tree.Node_Create("G");
	Node_BinaryTree<bool>* h = tree.Node_Create("H");
	Node_BinaryTree<bool>* k = tree.Node_Create("K");
	//Node_BinaryTree<bool>* i = tree.Node_Create("I");
	
	tree.Tree_Init(a);
	tree.Node_Insert(b, a, left);
	tree.Node_Insert(e, a, right);
	tree.Node_Insert(c, b, right);
	tree.Node_Insert(d, c, left);
	tree.Node_Insert(f, e, right);
	tree.Node_Insert(g, f, left);
	tree.Node_Insert(h, g, left);
	tree.Node_Insert(k, g, right);
	//tree.Node_Insert(i, k, right);

	std::cout <<"当前树深度为: " << tree.Tree_GetDepth() << std::endl;

	std::cout << "LEVEL: \n";
	tree.Tree_Traverse_LevelOrder(tree.Tree_GetRoot());
	std::cout << std::endl << std::endl;
	std::cout << "DLR: \n";
	tree.Tree_Traverse_PreOrder(tree.Tree_GetRoot());
	std::cout << std::endl << "DLR None Recursive：\n";
	tree.Tree_Traverse_PreOrder_NoneRecursive(tree.Tree_GetRoot());


	std::cout << std::endl << "LDR: \n";
	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());
	std::cout << std::endl << "LDR None Recursive：\n";
	tree.Tree_Traverse_InOrder_NoneRecursive(tree.Tree_GetRoot());

	std::cout << std::endl << std::endl << "LRD: \n";
	tree.Tree_Traverse_PostOrder(tree.Tree_GetRoot());
	std::cout << std::endl << "LRD None Recursive：\n";
	tree.Tree_Traverse_PostOrder_NoneRecursive(tree.Tree_GetRoot());

	
	//tree.Tree_Show();
	//tree.Tree_Clear();
	tree.Tree_Destroy();




}


void Test_CPP()
{
	//TestSeqList();
	TestLinkList();
	//TestSequenceStack();
	//TestLinkStack();
	//TestSeqQueue();
	//TestLinkQueue();
	//TestBinaryTree();
}

#endif // CPP


#include <Windows.h>
///修改cmd编码方式
static bool  SetEncode(int EncodeId = 936)
{
	/// <summary>
	/// EncodeId 是代码页，设置它等于设置我们指定的编码格式。
	///	默认936为unicode编码
	/// SetConsoleCP() 设置控制台输入时使用的编码。
	///	SetConsoleOutputCP() 设置控制台输出时使用的编码。
	/// </summary>
	/// <param name="EncodeId"></param>
	/// <returns></returns>
	return SetConsoleCP(EncodeId) && SetConsoleOutputCP(EncodeId);
}

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	
	Test_C();
	//Test_CPP();



}









