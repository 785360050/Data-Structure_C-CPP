
#include "Tree_Binary_Search_AVL.h"

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


void BinarySearch_AVL()
{
	Tree_Binary_Search_AVL<int> tree;
	//tree.BinaryTree_Insert_AVL(8);
	//tree.BinaryTree_Insert_AVL(4);
	//tree.BinaryTree_Insert_AVL(2);
	//tree.BinaryTree_Insert_AVL(6);
	//tree.BinaryTree_Insert_AVL(9);
	//std::cout << Tree->num << std::endl;

	for (int i = 1; i <= 7; ++i)
		tree.BinaryTree_Insert_AVL(i);
	tree.BinaryTree_Traversal_Inorder_AVL(tree.root);
	//tree.BinaryTree_AVL_Delete(tree.root, 8);
	std::cout << std::endl;
	tree.BinaryTree_AVL_Delete(tree.root, 8);
	tree.BinaryTree_Traversal_Inorder_AVL(tree.root);
	std::cout << std::endl;
	tree.BinaryTree_AVL_Delete(tree.root, 4);
	tree.BinaryTree_Traversal_Inorder_AVL(tree.root);
	std::cout << std::endl;
	tree.BinaryTree_AVL_Delete(tree.root, 6);
	tree.BinaryTree_Traversal_Inorder_AVL(tree.root);
	std::cout << std::endl;
	tree.BinaryTree_AVL_Delete(tree.root, 7);
	tree.BinaryTree_Traversal_Inorder_AVL(tree.root);
	std::cout << std::endl;
	tree.BinaryTree_Traversal_Inorder_AVL(tree.root);
}



void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	BinarySearch_AVL();
}