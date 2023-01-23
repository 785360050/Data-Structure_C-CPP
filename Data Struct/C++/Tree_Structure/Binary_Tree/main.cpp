
#include "Tree_Binary_Normal.h"
#include "Binary_Node.h"
#include "Binary_Tree_Thread.h"
#include "Tree_Binary_Search.h"
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

	tree.Tree_Set_Root(a);

	tree.Node_Insert(b, a, left);
	tree.Node_Insert(e, a, right);
	tree.Node_Insert(c, b, right);
	tree.Node_Insert(d, c, left);
	tree.Node_Insert(f, e, right);
	tree.Node_Insert(g, f, left);
	tree.Node_Insert(h, g, left);
	tree.Node_Insert(k, g, right);
	//tree.Node_Insert(i, k, right);

	std::cout << "当前树深度为: " << tree.Tree_GetDepth() << std::endl;

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


	tree.Tree_Show();
	tree.Tree_Clear();
}

void Test_Binary_Thread_Tree()
{
	Node_BinaryThreadTree<int>* a = new Node_BinaryThreadTree<int>("A");
	Node_BinaryThreadTree<int>* b = new Node_BinaryThreadTree<int>("B");
	Node_BinaryThreadTree<int>* c = new Node_BinaryThreadTree<int>("C");
	Node_BinaryThreadTree<int>* d = new Node_BinaryThreadTree<int>("D");
	Node_BinaryThreadTree<int>* e = new Node_BinaryThreadTree<int>("E");
	Node_BinaryThreadTree<int>* f = new Node_BinaryThreadTree<int>("F");
	Node_BinaryThreadTree<int>* g = new Node_BinaryThreadTree<int>("G");
	Node_BinaryThreadTree<int>* h = new Node_BinaryThreadTree<int>("H");
	Node_BinaryThreadTree<int>* k = new Node_BinaryThreadTree<int>("K");

	///指定a节点为树根
	BinaryTree_Thread<int> tree(a);

	tree.BinaryTree_Insert_Thread(a, left, b);
	tree.BinaryTree_Insert_Thread(a, right, e);
	tree.BinaryTree_Insert_Thread(b, right, c);
	tree.BinaryTree_Insert_Thread(c, left, d);
	tree.BinaryTree_Insert_Thread(e, right, f);
	tree.BinaryTree_Insert_Thread(f, left, g);
	tree.BinaryTree_Insert_Thread(g, left, h);
	tree.BinaryTree_Insert_Thread(g, right, k);

	tree.BinaryTree_Thread_Inorder(tree.root);

	tree.BinaryTree_Traversal_Inorder_Thread(tree.root);

	std::cout << std::endl;
}

void BinarySearch()
{
	Binary_Tree_Search<int> tree;
	Node_BinaryTree<int>* d = tree.Node_Create("4",4);

	tree.Tree_Set_Root(d);
	//tree.Tree_Element_Insert(2);
	//tree.Tree_Element_Insert(1);
	//tree.Tree_Element_Insert(3);
	//tree.Tree_Element_Insert(6);
	//tree.Tree_Element_Insert(5);
	//tree.Tree_Element_Insert(7);

	tree.Tree_Element_Insert_NonRecursive(2);
	tree.Tree_Element_Insert_NonRecursive(1);
	tree.Tree_Element_Insert_NonRecursive(3);
	tree.Tree_Element_Insert_NonRecursive(6);
	tree.Tree_Element_Insert_NonRecursive(5);
	tree.Tree_Element_Insert_NonRecursive(7);


	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());

	auto node = tree.Tree_Element_Locate("7");///查找测试
	if (node)
		std::cout << "Node Founded" << std::endl;
	else
		std::cout << "Node Not Found" << std::endl;

	tree.Tree_Element_Delete(2);
	std::cout << "After Delete 2" << std::endl;
	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());
	tree.Tree_Element_Delete(4);
	std::cout << "After Delete 4" << std::endl;
	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());

}




void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	//Test_Binary_Tree();
	//Test_Binary_Thread_Tree();
	BinarySearch();
}