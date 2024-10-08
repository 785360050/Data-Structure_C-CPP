#include "AVL_Tree.hpp"



Painter::AVL_Tree::AVL_Tree()
{
	for (int i = 1; i <= 7; ++i)
		tree.Element_Insert(i);

	// tree.Element_Delete(8);
	// tree.Element_Delete(4);
	// tree.Element_Delete(6);
	// tree.Element_Delete(7);

	container=tree.Capture_Snapshot();
	drawer.Update_Tree(container);
	Update();
}

void Painter::AVL_Tree::Element_Delete(int key)
{
	tree.Element_Delete(key);
	container=tree.Capture_Snapshot();
	Update();
}

void Painter::AVL_Tree::Element_Insert(int key, int element)
{
	tree.Element_Insert(key,element);
	container=tree.Capture_Snapshot();
	Update();
}

Node_Binary_Search_Balance<int, int>* Painter::AVL_Tree::Node_Search(int key)
{
	return tree.Node_Search(key);
}


void View::AVL_Tree::Handle_Element_Insert()
{
	int key = operation.input_insert_key->text().toInt();
	int element = operation.input_insert_element->text().toInt();
	painter.Element_Insert(key, element);
	Refresh_View(painter.boundingRect().size());
}

void View::AVL_Tree::Handle_Element_Delete()
{

	int key = operation.input_delete_key->text().toInt();
	painter.Element_Delete(key);
	Refresh_View(painter.boundingRect().size());
}

void View::AVL_Tree::Handle_Node_Search()
{
	int key = operation.input_search_key->text().toInt();
	auto node = painter.Node_Search(key);
	if (node)
		std::cout << "node = " + node->name + " key = " + std::to_string(node->key);
	else
		std::cout << "node (key = " + std::to_string(key) + ") Not Found";
}


