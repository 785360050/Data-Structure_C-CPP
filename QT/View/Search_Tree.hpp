#pragma once

#include "Structure.hpp"

#include <QPushButton>
#include <QLineEdit>

#include "../Painter/Search_Tree.hpp"

namespace View
{
class Search_Tree : public Structure
{
	Painter::Search_Tree painter;
public:
	Search_Tree()
	{
		Hook_Painter(&painter);
		Config_Operations();
	}
	~Search_Tree(){};

public: // interactions
	QPushButton* button_insert{new QPushButton("Insert Element")};
	QLineEdit* input_insert_key{new QLineEdit};
	QLineEdit* input_insert_element{new QLineEdit};
	QPushButton* button_delete{new QPushButton("Delete Element")};
	QLineEdit* input_delete_key{new QLineEdit};
	QPushButton* button_search{new QPushButton("Node Search")};
	QLineEdit* input_search_key{new QLineEdit};
	QPushButton* button_traverse_preorder{new QPushButton("Traverse Preorder")};
	QPushButton* button_traverse_inorder{new QPushButton("Traverse Inorder")};
	QPushButton* button_traverse_postorder{new QPushButton("Traverse Postorder")};
	QPushButton* button_traverse_levelorder{new QPushButton("Traverse Levelorder")};
	void Config_Operations() override
	{
		QHBoxLayout* line_push=new QHBoxLayout;
		input_insert_key->setPlaceholderText("key");
		input_insert_element->setPlaceholderText("element");
		line_push->addWidget(input_insert_key);
		line_push->addWidget(input_insert_element);
		line_push->addWidget(button_insert);

		QHBoxLayout* line_delete=new QHBoxLayout;
		input_delete_key->setPlaceholderText("key");
		line_delete->addWidget(input_delete_key);
		line_delete->addWidget(button_delete);

		QHBoxLayout* line_search=new QHBoxLayout;
		input_search_key->setPlaceholderText("key");
		line_search->addWidget(input_search_key);
		line_search->addWidget(button_search);

		QVBoxLayout* layout=new QVBoxLayout;
		layout->addLayout(line_push);
		layout->addLayout(line_delete);
		layout->addLayout(line_search);
		layout->addWidget(button_traverse_preorder);
		layout->addWidget(button_traverse_inorder);
		layout->addWidget(button_traverse_postorder);
		layout->addWidget(button_traverse_levelorder);


		ui.tab_operations->setLayout(layout);

		connect(button_insert,&QPushButton::clicked,this,&Search_Tree::Handle_Element_Insert);
		connect(button_delete,&QPushButton::clicked,this,&Search_Tree::Handle_Element_Delete);
		connect(button_search,&QPushButton::clicked,this,&Search_Tree::Handle_Node_Search);
	}

	void Handle_Element_Insert();
	void Handle_Element_Delete();
	void Handle_Node_Search();
};
}
