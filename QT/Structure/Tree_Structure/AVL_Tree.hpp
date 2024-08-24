#pragma once


#include "../../Painter/Painter.hpp"
#include "../../Painter/Tree.hpp"


#include "../../Data_Sturcture/C++/Tree_Structure/Tree/Tree_Binary/Tree_Binary_Search/AVL_Tree/Tree_Binary_Search_AVL.hpp"

namespace Adapter
{
	template <typename DataType, typename KeyType, typename NodeType=Node_Binary_Search_Balance<DataType,KeyType>>
	class AVL_Tree:public Storage::Tree_Binary_Search_AVL<DataType,KeyType,NodeType>
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
	class AVL_Tree : public Painter::Painter
	{
		Adapter::AVL_Tree<int,int> tree;
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
		AVL_Tree()
		{
			for (int i = 1; i <= 7; ++i)
				tree.Element_Insert(i);

			// tree.Element_Delete(8);
			// tree.Element_Delete(4);
			// tree.Element_Delete(6);
			// tree.Element_Delete(7);

			container=tree.Capture_Snapshot();
			drawer.Update_Tree(container);
		}
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
		Node_Binary_Search_Balance<int,int>* Node_Search(int key)
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
	class AVL_Tree : public Structure
	{
		Painter::AVL_Tree painter;

	public:
		AVL_Tree()
		{
			Hook_Painter(&painter);
			Config_Operations();
		}
		~AVL_Tree() {};

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

			connect(button_insert, &QPushButton::clicked, this, &AVL_Tree::Handle_Element_Insert);
			connect(button_delete, &QPushButton::clicked, this, &AVL_Tree::Handle_Element_Delete);
			connect(button_search, &QPushButton::clicked, this, &AVL_Tree::Handle_Node_Search);
		}

		void Handle_Element_Insert();
		void Handle_Element_Delete();
		void Handle_Node_Search();
	};


}
