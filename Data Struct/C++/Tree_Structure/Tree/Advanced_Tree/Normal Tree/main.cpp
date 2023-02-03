
#include "Tree_Normal.h"


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

void Test_Tree()
{
	Tree_Advanced<bool> tree(3);

	Node_Tree_ChildSibling<bool>* a = tree.Node_Create("A");
	Node_Tree_ChildSibling<bool>* b = tree.Node_Create("B");
	Node_Tree_ChildSibling<bool>* c = tree.Node_Create("C");
	Node_Tree_ChildSibling<bool>* d = tree.Node_Create("D");
	Node_Tree_ChildSibling<bool>* e = tree.Node_Create("E");
	Node_Tree_ChildSibling<bool>* f = tree.Node_Create("F");
	Node_Tree_ChildSibling<bool>* g = tree.Node_Create("G");
	Node_Tree_ChildSibling<bool>* h = tree.Node_Create("H");
	Node_Tree_ChildSibling<bool>* i = tree.Node_Create("I");
	Node_Tree_ChildSibling<bool>* j = tree.Node_Create("J");
	Node_Tree_ChildSibling<bool>* k = tree.Node_Create("K");

	tree.Tree_Set_Root(a);

	tree.Node_Insert(b, a, 1);
	tree.Node_Insert(c, a, 2);
	tree.Node_Insert(d, a, 3);
	tree.Node_Insert(e, b, 1);
	tree.Node_Insert(f, b, 2);
	tree.Node_Insert(g, b, 3);
	tree.Node_Insert(h, c, 1);
	tree.Node_Insert(i, d, 1);
	tree.Node_Insert(j, d, 2);

	//std::cout << "当前树深度为: " << tree.Tree_GetDepth() << std::endl;

	std::cout << "LEVEL: \n";
	tree.Tree_Traverse_LevelOrder(tree.Tree_GetRoot());
	std::cout << std::endl << std::endl;
	std::cout << "D[L->R]: \n";
	tree.Tree_Traverse_PreOrder(tree.Tree_GetRoot());
	std::cout << std::endl << std::endl << "[L->R]D: \n";
	tree.Tree_Traverse_PostOrder(tree.Tree_GetRoot());
	std::cout << std::endl;


	tree.Tree_Show();
	tree.Tree_Clear();
}

void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	Test_Tree();
}