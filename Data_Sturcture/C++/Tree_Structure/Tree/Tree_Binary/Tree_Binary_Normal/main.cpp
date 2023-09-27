
#include "Tree_Binary_Normal.h"

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
	Tree_Binary_Normal<bool> tree;

	auto* a = tree.Node_Create("A");
	auto* b = tree.Node_Create("B");
	auto* c = tree.Node_Create("C");
	auto* d = tree.Node_Create("D");
	auto* e = tree.Node_Create("E");
	auto* f = tree.Node_Create("F");
	auto* g = tree.Node_Create("G");
	auto* h = tree.Node_Create("H");
	auto* k = tree.Node_Create("K");
	//auto* i = tree.Node_Create("I");

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
	//tree.Tree_Clear();
}

void Test_Tree_Build()
{
	Tree_Binary_Normal<int> tree;
	tree.Tree_Build({ 3,9,20,15,7 }, { 9,3,15,20,7 },true);
	//tree.Tree_Build( { 9,15,7,20,3 }, { 9,3,15,20,7 },false);
	tree.Tree_Show();
}

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	//Test_Binary_Tree();
	Test_Tree_Build();
}