
#include "Binary_Tree_Search_Normal.hpp"

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


void BinarySearch()
{
	Tree_Binary_Search_Normal<int,int> tree;

	//tree.Element_Insert(4);
	//tree.Element_Insert(2);
	//tree.Element_Insert(1);
	//tree.Element_Insert(3);
	//tree.Element_Insert(6);
	//tree.Element_Insert(5);
	//tree.Element_Insert(7);

	tree.Element_Insert_NonRecursive(4);
	tree.Element_Insert_NonRecursive(2);
	tree.Element_Insert_NonRecursive(1);
	tree.Element_Insert_NonRecursive(3);
	tree.Element_Insert_NonRecursive(6);
	tree.Element_Insert_NonRecursive(5);
	tree.Element_Insert_NonRecursive(7);


	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());

	auto node = tree.Node_Search(7);///查找测试
	if (node)
		std::cout << "Node Founded (√)" << std::endl;
	else
		throw std::logic_error("Node 7 is not in tree");

	tree.Element_Delete(2);
	std::cout << "After Delete 2" << std::endl;
	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());

	std::cout << std::endl;
	tree.Element_Delete(4);
	std::cout << "After Delete 4" << std::endl;
	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());

	std::cout << std::endl;
	std::cout << "Depth = " + std::to_string(tree.Get_Depth(tree.root)) << std::endl;
}

int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	BinarySearch();

	return EXIT_SUCCESS;
}