#include "Search_Tree.hpp"





Painter::Search_Tree::Search_Tree()
{
	tree.Element_Insert_NonRecursive(4);
	tree.Element_Insert_NonRecursive(2);
	tree.Element_Insert_NonRecursive(1);
	tree.Element_Insert_NonRecursive(3);
	tree.Element_Insert_NonRecursive(6);
	tree.Element_Insert_NonRecursive(5);
	tree.Element_Insert_NonRecursive(7);


	// tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());

	auto node = tree.Node_Search(7);///查找测试
	if (node)
		std::cout << "Node Founded (√)" << std::endl;
	else
		throw std::logic_error("Node 7 is not in tree");

	tree.Element_Delete(2);
	std::cout << "After Delete 2" << std::endl;
	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());
	tree.Element_Delete(4);
	std::cout << "After Delete 4" << std::endl;
	tree.Tree_Traverse_InOrder(tree.Tree_GetRoot());

}

void Painter::Search_Tree::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

}
