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

	// tree.Element_Delete(2);
	// tree.Element_Delete(4);
	std::cout << "Depth = " + std::to_string(tree.Get_Depth(tree.root)) << std::endl;

	container=tree.Capture_Snapshot();
	drawer.Update_Tree(container);

}


void View::Search_Tree::Handle_Element_Insert()
{
	int key = operation.input_insert_key->text().toInt();
	int element = operation.input_insert_element->text().toInt();
	painter.Element_Insert(key, element);
	Refresh_View();
}

void View::Search_Tree::Handle_Element_Delete()
{
	int key = operation.input_delete_key->text().toInt();
	painter.Element_Delete(key);
	Refresh_View();
}

void View::Search_Tree::Handle_Node_Search()
{
	int key = operation.input_search_key->text().toInt();
	auto node = painter.Node_Search(key);
	if (node)
		std::cout << "node = " + node->name + " key = " + std::to_string(node->key);
	else
		std::cout << "node (key = " + std::to_string(key) + ") Not Found";
}
