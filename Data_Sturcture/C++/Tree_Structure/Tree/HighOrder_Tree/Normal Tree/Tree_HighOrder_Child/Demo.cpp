
#include <iostream>

#include "Tree_HighOrder_Child.hpp"

int main()
{

	// Storage::Tree_Normal_Child<bool, 3> tree;
	Storage::Tree_Normal_Child_Ordered<bool,3> tree;

	//Bugs↓
	// Tree_Normal<bool, TreeNode_HighOrder_Child<bool>> *tree = new Tree_Advanced_Child<bool>(3);
	// Tree_Normal<bool, TreeNode_HighOrder_ChildSibling<bool>> *tree = new Tree_HighOrder_ChildSibling<bool>(3);
	

	auto a = tree.Node_Create("A");
	auto b = tree.Node_Create("B");
	auto c = tree.Node_Create("C");
	auto d = tree.Node_Create("D");
	auto e = tree.Node_Create("E");
	auto f = tree.Node_Create("F");
	auto g = tree.Node_Create("G");
	auto h = tree.Node_Create("H");
	auto i = tree.Node_Create("I");
	auto j = tree.Node_Create("J");
	auto k = tree.Node_Create("K");

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

	//std::cout << "当前树深度为: " << tree->Tree_GetDepth() << std::endl;

	// std::cout << "LEVEL: \n";
	// tree.Traverse_LevelOrder(tree.Get_Root());
	// std::cout << std::endl << std::endl;
	// std::cout << "D[L->R]: \n";
	// tree.Traverse_PreOrder(tree.Get_Root());
	// std::cout << std::endl << std::endl << "[L->R]D: \n";
	// tree.Traverse_PostOrder(tree.Get_Root());
	// std::cout << std::endl;


	tree.Show();
}

