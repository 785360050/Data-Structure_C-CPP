#include "Red_Black_Tree.hpp"



void View::Tree_Binary_Search_RBT::Handle_Element_Insert()
{
	int key = input_insert_key->text().toInt();
	int element = input_insert_element->text().toInt();
	painter.Element_Insert(key, element);
	Refresh_View();
}

void View::Tree_Binary_Search_RBT::Handle_Element_Delete()
{

	int key = input_delete_key->text().toInt();
	painter.Element_Delete(key);
	Refresh_View();
}

void View::Tree_Binary_Search_RBT::Handle_Node_Search()
{
	int key = input_search_key->text().toInt();
	auto node = painter.Node_Search(key);
	if (node)
		std::cout << "node = " + node->name + " key = " + std::to_string(node->key);
	else
		std::cout << "node (key = " + std::to_string(key) + ") Not Found";
}
