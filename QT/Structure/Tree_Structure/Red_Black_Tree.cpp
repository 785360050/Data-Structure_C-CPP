#include "Red_Black_Tree.hpp"



Painter::Tree_Binary_Search_RBT::Tree_Binary_Search_RBT()
{
	tree.Element_Insert(8);
	tree.Element_Insert(5);
	tree.Element_Insert(15);
	tree.Element_Insert(12);///叔红 变色父、祖父、叔节点
	tree.Element_Insert(19);
	tree.Element_Insert(9);///叔红 变色父、祖父、叔节点
	tree.Element_Insert(13);
	tree.Element_Insert(23);
	///叔红->变色;切换视角为12节点 RL->右旋父节点+左旋祖父节点+变色父、祖父


	// tree.Element_Delete(15);
	// tree.Element_Delete(19);
	// tree.Element_Delete(13);
	// tree.Element_Delete(23);

	container=tree.Capture_Snapshot();
	drawer.Update_Tree(container);
	Update_Area_Size(drawer.Get_Area_Size());
}

void Painter::Tree_Binary_Search_RBT::Element_Delete(int key)
{
	tree.Element_Delete(key);
	container=tree.Capture_Snapshot();
	drawer.Update_Tree(container);
	Update_Area_Size(drawer.Get_Area_Size());
}

void Painter::Tree_Binary_Search_RBT::Element_Insert(int key, int element)
{
	tree.Element_Insert(key,element);
	container=tree.Capture_Snapshot();
	drawer.Update_Tree(container);
	Update_Area_Size(drawer.Get_Area_Size());
}



void View::Tree_Binary_Search_RBT::Config_Operations()
{
	auto layout=operation.Generate();

	ui.tab_operations->setLayout(layout);

	connect(operation.button_insert, &QPushButton::clicked, this, &Tree_Binary_Search_RBT::Handle_Element_Insert);
	connect(operation.button_delete, &QPushButton::clicked, this, &Tree_Binary_Search_RBT::Handle_Element_Delete);
	connect(operation.button_search, &QPushButton::clicked, this, &Tree_Binary_Search_RBT::Handle_Node_Search);
}

void View::Tree_Binary_Search_RBT::Handle_Element_Insert()
{
	int key = operation.input_insert_key->text().toInt();
	int element = operation.input_insert_element->text().toInt();
	painter.Element_Insert(key, element);
	Refresh_View(painter.boundingRect().size());
}

void View::Tree_Binary_Search_RBT::Handle_Element_Delete()
{

	int key = operation.input_delete_key->text().toInt();
	painter.Element_Delete(key);
	Refresh_View(painter.boundingRect().size());
}

void View::Tree_Binary_Search_RBT::Handle_Node_Search()
{
	int key = operation.input_search_key->text().toInt();
	auto node = painter.Node_Search(key);
	if (node)
		std::cout << "node = " + node->name + " key = " + std::to_string(node->key);
	else
		std::cout << "node (key = " + std::to_string(key) + ") Not Found";
}


