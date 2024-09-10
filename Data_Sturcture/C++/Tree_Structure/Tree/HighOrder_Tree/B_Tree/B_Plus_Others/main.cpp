
#include "Node_BPlus.hpp"
#include "B_Plus.hpp"

// #include <Windows.hpp>
// static bool  SetEncode(int EncodeId = 936)
// {
// 	/// <summary>
// 	/// EncodeId 是代码页，设置它等于设置我们指定的编码格式。
// 	///	默认936为unicode编码
// 	/// SetConsoleCP() 设置控制台输入时使用的编码。
// 	///	SetConsoleOutputCP() 设置控制台输出时使用的编码。
// 	/// </summary>
// 	/// <param name="EncodeId"></param>
// 	/// <returns></returns>
// 	return SetConsoleCP(EncodeId) && SetConsoleOutputCP(EncodeId);
// }

void Test_BPlus_Tree()
{
	Tree_BPlus<int, int>* tree = new Tree_BPlus<int, int>(5);
	for (int i = 1; i <= 22; ++i)
		tree->insert(i, i);
	//tree->scan();
	tree->display();

	//tree->erase(4);
	//std::cout << tree->find(4) << std::endl;
	//tree->display();

	tree->display();

	delete tree;

}

// #include "Tree_B+_Others.hpp"
// void Test_BPlus_Tree_Other()
// {
// 	BPTree<int, int> tree;
// 	for (int i = 1; i <= 22; ++i)
// 		tree.insert(i, i);
// 	//tree->scan();
// 	tree.display();

// 	//tree->erase(4);
// 	//std::cout << tree->find(4) << std::endl;
// 	//tree->display();

// 	tree.display();
// }


int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	Test_BPlus_Tree();
	// Test_BPlus_Tree_Other();
	return EXIT_SUCCESS;
}
