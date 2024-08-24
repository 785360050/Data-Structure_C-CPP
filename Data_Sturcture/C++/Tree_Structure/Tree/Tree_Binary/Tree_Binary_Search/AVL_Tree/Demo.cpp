
#include "Tree_Binary_Search_AVL.hpp"

void BinarySearch_AVL()
{
	Storage::Tree_Binary_Search_AVL<int> tree;
	//tree.BinaryTree_Insert_AVL(8);
	//tree.BinaryTree_Insert_AVL(4);
	//tree.BinaryTree_Insert_AVL(2);
	//tree.BinaryTree_Insert_AVL(6);
	//tree.BinaryTree_Insert_AVL(9);
	//std::cout << Tree->num << std::endl;

	for (int i = 1; i <= 7; ++i)
		tree.Element_Insert(i);
	// tree.BinaryTree_Traversal_Inorder_AVL(tree.root);
	tree.Traverse_InOrder(tree.root);


	std::cout << std::endl;
	tree.Element_Delete(8);
	tree.Traverse_InOrder(tree.root);
	std::cout << std::endl;
	tree.Element_Delete(4);
	tree.Traverse_InOrder(tree.root);
	std::cout << std::endl;
	tree.Element_Delete(6);
	tree.Traverse_InOrder(tree.root);
	std::cout << std::endl;
	tree.Element_Delete(7);
	tree.Traverse_InOrder(tree.root);
	std::cout << std::endl;
	tree.Traverse_InOrder(tree.root);

	std::cout << std::endl;
	auto node=tree.Node_Search(10);
	if(node==nullptr)
		std::cout << "Node 10 Not Found (√)";
	else
		throw std::logic_error("node 10 is not in tree");

	std::cout << std::endl;
	node=tree.Node_Search(3);
	std::cout << "Node 3 has key: " + std::to_string(node->key)<<std::endl;

	std::cout << std::endl;
	std::cout << "Depth = " + std::to_string(tree.Get_Depth(tree.root)) << std::endl;
}

int main()
{
	// SetEncode(65001);//设置控制台为utf-8编码格式
	BinarySearch_AVL();

	return EXIT_SUCCESS;
}