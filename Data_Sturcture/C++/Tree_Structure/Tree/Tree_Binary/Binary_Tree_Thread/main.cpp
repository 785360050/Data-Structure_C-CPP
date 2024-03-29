
#include "Binary_Tree_Thread.hpp"

#ifdef _Win32 // ARM32/64, x86/x64
// 详见 https://learn.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-170
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
#endif

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

	std::cout << std::endl << "DLR: ";
	tree.Tree_Traverse_PreOrder(tree.Tree_GetRoot());
	std::cout << std::endl << "LDR: ";
	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());	///线索化优化过
	std::cout << std::endl << "LRD: ";
	tree.Tree_Traverse_PostOrder(tree.Tree_GetRoot());
	std::cout << std::endl << "Level Traverse: ";
	tree.Tree_Traverse_LevelOrder(tree.Tree_GetRoot());	

	std::cout << std::endl;
}

int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	Test_Binary_Thread_Tree();

	return EXIT_SUCCESS;
}