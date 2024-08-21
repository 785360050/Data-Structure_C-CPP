
#include "Tree_Binary_Search_BRT.hpp"

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

void BinarySearch_RBT()
{
	Tree_Binary_Search_RBT<int> tree;

	tree.Element_Insert(8);
	tree.Element_Insert(5);
	tree.Element_Insert(15);
	tree.Element_Insert(12);///叔红 变色父、祖父、叔节点
	tree.Element_Insert(19);
	tree.Element_Insert(9);///叔红 变色父、祖父、叔节点
	tree.Element_Insert(13);
	tree.Element_Insert(23);
	///叔红->变色;切换视角为12节点 RL->右旋父节点+左旋祖父节点+变色父、祖父

	std::cout << "\nDLR:";
	tree.Tree_Traverse_PreOrder(tree.root);

	tree.Element_Delete(15);
	tree.Element_Delete(19);
	tree.Element_Delete(13);
	tree.Element_Delete(23);



	std::cout << std::endl << "After Delete 15 19 13 23" << std::endl;
	std::cout << "\nDLR:";
	tree.Tree_Traverse_PreOrder(tree.root);
	std::cout << "\nLDR:";
	tree.Tree_Traverse_InOrder(tree.root);

	std::cout << std::endl << "\n搜索节点9：目标节点值为" << tree.Node_Search(9)->element<<std::endl;



}

int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	BinarySearch_RBT();
	return EXIT_SUCCESS;
}