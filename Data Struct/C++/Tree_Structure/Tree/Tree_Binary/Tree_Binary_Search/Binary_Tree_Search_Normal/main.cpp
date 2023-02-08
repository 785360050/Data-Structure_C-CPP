
#include "Binary_Tree_Search_Normal.h"


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


void BinarySearch()
{
	Binary_Tree_Search_Normal<int> tree;
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
	BinarySearch();
}