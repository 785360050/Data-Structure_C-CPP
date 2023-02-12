
#include "Tree_Binary_Normal/Tree_Binary_Normal.h"
#include "Node_BinaryTree.h"
#include "Binary_Tree_Thread/Binary_Tree_Thread.h"
#include "Tree_Binary_Search/Tree_Binary_Search.h"
#include "Tree_Binary_Search/Tree_Binary_Search_AVL.h"
#include "Tree_Binary_Search/Tree_Binary_Search_BRT.h"
#include "../../Heap/Binary_Heap.h"

#include <Windows.h>
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

void Test_Binary_Tree()
{
	Binary_Tree<bool>* tree=new Binary_Tree<bool>;

	Node_BinaryTree<bool>* a = tree->Node_Create("A");
	Node_BinaryTree<bool>* b = tree->Node_Create("B");
	Node_BinaryTree<bool>* c = tree->Node_Create("C");
	Node_BinaryTree<bool>* d = tree->Node_Create("D");
	Node_BinaryTree<bool>* e = tree->Node_Create("E");
	Node_BinaryTree<bool>* f = tree->Node_Create("F");
	Node_BinaryTree<bool>* g = tree->Node_Create("G");
	Node_BinaryTree<bool>* h = tree->Node_Create("H");
	Node_BinaryTree<bool>* k = tree->Node_Create("K");
	//Node_BinaryTree<bool>* i = tree.Node_Create("I");

	tree->Tree_Set_Root(a);

	tree->Node_Insert(b, a, left);
	tree->Node_Insert(e, a, right);
	tree->Node_Insert(c, b, right);
	tree->Node_Insert(d, c, left);
	tree->Node_Insert(f, e, right);
	tree->Node_Insert(g, f, left);
	tree->Node_Insert(h, g, left);
	tree->Node_Insert(k, g, right);
	//tree->Node_Insert(i, k, right);

	std::cout << "当前树深度为: " << tree->Tree_GetDepth() << std::endl;

	std::cout << "LEVEL: \n";
	tree->Tree_Traverse_LevelOrder(tree->Tree_GetRoot());
	std::cout << std::endl << std::endl;
	std::cout << "DLR: \n";
	tree->Tree_Traverse_PreOrder(tree->Tree_GetRoot());
	std::cout << std::endl << "DLR None Recursive：\n";
	tree->Tree_Traverse_PreOrder_NoneRecursive(tree->Tree_GetRoot());


	std::cout << std::endl << "LDR: \n";
	tree->Tree_Traverse_InOrder(tree->Tree_GetRoot());
	std::cout << std::endl << "LDR None Recursive：\n";
	tree->Tree_Traverse_InOrder_NoneRecursive(tree->Tree_GetRoot());

	std::cout << std::endl << std::endl << "LRD: \n";
	tree->Tree_Traverse_PostOrder(tree->Tree_GetRoot());
	std::cout << std::endl << "LRD None Recursive：\n";
	tree->Tree_Traverse_PostOrder_NoneRecursive(tree->Tree_GetRoot());


	tree->Tree_Show();
	//tree->Tree_Clear();
}

void Test_Binary_Thread_Tree()
{
	BinaryTree_Thread<int> tree;

	Node_BinaryThreadTree<int>* a = tree.Node_Create("A");
	Node_BinaryThreadTree<int>* b = tree.Node_Create("B");
	Node_BinaryThreadTree<int>* c = tree.Node_Create("C");
	Node_BinaryThreadTree<int>* d = tree.Node_Create("D");
	Node_BinaryThreadTree<int>* e = tree.Node_Create("E");
	Node_BinaryThreadTree<int>* f = tree.Node_Create("F");
	Node_BinaryThreadTree<int>* g = tree.Node_Create("G");
	Node_BinaryThreadTree<int>* h = tree.Node_Create("H");
	Node_BinaryThreadTree<int>* k = tree.Node_Create("K");

	///指定a节点为树根
	//BinaryTree_Thread<int> tree(a);
	tree.Tree_Set_Root(a);

	tree.Node_Insert(b, a, left);
	tree.Node_Insert(e, a, right);
	tree.Node_Insert(c, b, right);
	tree.Node_Insert(d, c, left);
	tree.Node_Insert(f, e, right);
	tree.Node_Insert(g, f, left);
	tree.Node_Insert(h, g, left);
	tree.Node_Insert(k, g, right);

	///线索化
	tree.ThreadTree_Modify(tree.Tree_GetRoot());

	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());
	tree.Tree_Traverse_LevelOrder(tree.Tree_GetRoot());	///线索化优化过
	tree.Tree_Traverse_PostOrder(tree.Tree_GetRoot());

	std::cout << std::endl;
}



void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	Test_Binary_Tree();
	//Test_Binary_Thread_Tree();
}