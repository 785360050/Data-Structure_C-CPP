#pragma once

#include "../../Painter/Painter.hpp"

#include "../../Data_Sturcture/C++/Tree_Structure/Tree/Tree_Binary/Tree_Binary_Search/Normal_Tree/Binary_Tree_Search_Normal.hpp"
// #include "../../Data_Sturcture/C++/Tree_Structure/Tree/HighOrder_Tree/Normal Tree/Tree_HighOrder_Child/Tree_HighOrder_Child.hpp"

#include "../../Painter/Tree.hpp"


namespace Adapter
{
	template <typename DataType, typename KeyType, typename NodeType=Node_Binary_Search_Normal<DataType,KeyType>>
	class Tree_Binary_Search:public Tree_Binary_Search_Normal<DataType,KeyType,NodeType>
	{
	public:
		Painter::Tree::Serialized_Container<DataType,2> Capture_Snapshot()
		{
			Painter::Tree::Serialized_Container<DataType,2> container;
			// container.Set_Level(5);
			int current_level=this->Get_Depth(this->root);
			container.Set_Level(current_level);
			std::queue<NodeType*> queue;
			queue.push(this->root);

			for(int level{1};level<=current_level;++level)
			{
				std::queue<NodeType*> paint_buffer=std::move(queue);
				int level_count=paint_buffer.size();
				for(int index{0};index<level_count;++index)
				{
					auto node=paint_buffer.front();
					if(node)
					{
						container.Set(node,level,index);
						queue.push(node->left);
						queue.push(node->right);
					}
					else
					{
						// one null parent map 2(branch) of child node
						queue.push(nullptr);
						queue.push(nullptr);
					}
					paint_buffer.pop();
				}
			}
			return container;

		}

	};
};

namespace Painter
{
class Search_Tree : public Painter::Painter
{
	Adapter::Tree_Binary_Search<int,int> tree;
	// Storage::Tree_Normal_Child_Ordered<int,2> tree;
	// Tree<int,2> painter;
	Tree::Serialized_Container<int,2> container;
	Tree::Drawer<int,2> drawer;

protected:
	// QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
	{
		drawer.Update_Tree(container);
		drawer.Draw(painter,option,widget);
	}

public:
	Search_Tree();
	// ~Search_Tree(){};
public:
	void Element_Delete(int key)
	{
		tree.Element_Delete(key);
		container=tree.Capture_Snapshot();
		drawer.Update_Tree(container);
	}
	void Element_Insert(int key,int element)
	{
		tree.Element_Insert(key,element);
		container=tree.Capture_Snapshot();
		drawer.Update_Tree(container);
	}
	Node_Binary_Search_Normal<int,int>* Node_Search(int key)
	{
		return tree.Node_Search(key);
	}
};
}


#include "../Structure.hpp"

#include <QPushButton>
#include <QLineEdit>


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
		~Search_Tree() {};

	public: // interactions
		QPushButton *button_insert{new QPushButton("Insert Element")};
		QLineEdit *input_insert_key{new QLineEdit};
		QLineEdit *input_insert_element{new QLineEdit};
		QPushButton *button_delete{new QPushButton("Delete Element")};
		QLineEdit *input_delete_key{new QLineEdit};
		QPushButton *button_search{new QPushButton("Node Search")};
		QLineEdit *input_search_key{new QLineEdit};
		QPushButton *button_traverse_preorder{new QPushButton("Traverse Preorder")};
		QPushButton *button_traverse_inorder{new QPushButton("Traverse Inorder")};
		QPushButton *button_traverse_postorder{new QPushButton("Traverse Postorder")};
		QPushButton *button_traverse_levelorder{new QPushButton("Traverse Levelorder")};
		void Config_Operations() override
		{
			QHBoxLayout *line_push = new QHBoxLayout;
			input_insert_key->setPlaceholderText("key");
			input_insert_element->setPlaceholderText("element");
			line_push->addWidget(input_insert_key);
			line_push->addWidget(input_insert_element);
			line_push->addWidget(button_insert);

			QHBoxLayout *line_delete = new QHBoxLayout;
			input_delete_key->setPlaceholderText("key");
			line_delete->addWidget(input_delete_key);
			line_delete->addWidget(button_delete);

			QHBoxLayout *line_search = new QHBoxLayout;
			input_search_key->setPlaceholderText("key");
			line_search->addWidget(input_search_key);
			line_search->addWidget(button_search);

			QVBoxLayout *layout = new QVBoxLayout;
			layout->addLayout(line_push);
			layout->addLayout(line_delete);
			layout->addLayout(line_search);
			layout->addWidget(button_traverse_preorder);
			layout->addWidget(button_traverse_inorder);
			layout->addWidget(button_traverse_postorder);
			layout->addWidget(button_traverse_levelorder);

			ui.tab_operations->setLayout(layout);

			connect(button_insert, &QPushButton::clicked, this, &Search_Tree::Handle_Element_Insert);
			connect(button_delete, &QPushButton::clicked, this, &Search_Tree::Handle_Element_Delete);
			connect(button_search, &QPushButton::clicked, this, &Search_Tree::Handle_Node_Search);
		}

		void Handle_Element_Insert();
		void Handle_Element_Delete();
		void Handle_Node_Search();
	};
}
