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

void Painter::Search_Tree::Element_Delete(int key)
{
	tree.Element_Delete(key);
	container=tree.Capture_Snapshot();
	drawer.Update_Tree(container);
	Update_Area_Size(drawer.Get_Area_Size());
}

void Painter::Search_Tree::Element_Insert(int key, int element)
{
	tree.Element_Insert(key,element);
	container=tree.Capture_Snapshot();
	drawer.Update_Tree(container);
	Update_Area_Size(drawer.Get_Area_Size());
}


void View::Search_Tree::Config_Operations()
{
	auto layout=operation.Generate();

	ui.tab_operations->setLayout(layout);

	connect(operation.button_insert, &QPushButton::clicked, this, &Search_Tree::Handle_Element_Insert);
	connect(operation.button_delete, &QPushButton::clicked, this, &Search_Tree::Handle_Element_Delete);
	connect(operation.button_search, &QPushButton::clicked, this, &Search_Tree::Handle_Node_Search);
}

void View::Search_Tree::Handle_Element_Insert()
{
	int key = operation.input_insert_key->text().toInt();
	int element = operation.input_insert_element->text().toInt();
	painter.Element_Insert(key, element);
	Refresh_View(painter.boundingRect().size());
}

void View::Search_Tree::Handle_Element_Delete()
{
	int key = operation.input_delete_key->text().toInt();
	painter.Element_Delete(key);
	Refresh_View(painter.boundingRect().size());
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

