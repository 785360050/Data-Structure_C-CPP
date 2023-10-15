
#include <iostream>

#include "Tree_HighOrder_Child/Tree_HighOrder_Child.hpp"
#include "Tree_HighOrder_ChildSibling/Tree_HighOrder_ChildSibling.hpp"
#include "Tree_HighOrder_Parent/Tree_HighOrder_Parent.hpp"
#include "Normal Tree.hpp"

#ifdef _WIN32
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


void Test_Tree_Normal()
{
	Tree_Normal<bool, TreeNode_HighOrder<bool>>* tree=new Tree_HighOrder_Parent<bool>(3);

	//Bugs↓
	// Tree_Normal<bool, TreeNode_HighOrder_Child<bool>> *tree = new Tree_Advanced_Child<bool>(3);
	// Tree_Normal<bool, TreeNode_HighOrder_ChildSibling<bool>> *tree = new Tree_HighOrder_ChildSibling<bool>(3);
	

	auto a = tree->Node_Create("A");
	auto b = tree->Node_Create("B");
	auto c = tree->Node_Create("C");
	auto d = tree->Node_Create("D");
	auto e = tree->Node_Create("E");
	auto f = tree->Node_Create("F");
	auto g = tree->Node_Create("G");
	auto h = tree->Node_Create("H");
	auto i = tree->Node_Create("I");
	auto j = tree->Node_Create("J");
	auto k = tree->Node_Create("K");

	tree->Tree_Set_Root(a);

	tree->Node_Insert(b, a, 1);
	tree->Node_Insert(c, a, 2);
	tree->Node_Insert(d, a, 3);
	tree->Node_Insert(e, b, 1);
	tree->Node_Insert(f, b, 2);
	tree->Node_Insert(g, b, 3);
	tree->Node_Insert(h, c, 1);
	tree->Node_Insert(i, d, 1);
	tree->Node_Insert(j, d, 2);

	//std::cout << "当前树深度为: " << tree->Tree_GetDepth() << std::endl;

	std::cout << "LEVEL: \n";
	tree->Tree_Traverse_LevelOrder(tree->Tree_GetRoot());
	std::cout << std::endl << std::endl;
	std::cout << "D[L->R]: \n";
	tree->Tree_Traverse_PreOrder(tree->Tree_GetRoot());
	std::cout << std::endl << std::endl << "[L->R]D: \n";
	tree->Tree_Traverse_PostOrder(tree->Tree_GetRoot());
	std::cout << std::endl;


	tree->Tree_Show();
}

int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	Test_Tree_Normal();
}