#pragma once

#include "../../Painter/Painter.hpp"
#include "../../Painter/Tree.hpp"

#include "../../Data_Sturcture/C++/Tree_Structure/Tree/Tree_Binary/Tree_Binary_Search/AVL_Tree/Tree_Binary_Search_AVL.hpp"

namespace Adapter
{
	template <typename DataType, typename KeyType, typename NodeType = Node_Binary_Search_Balance<DataType, KeyType>>
	class AVL_Tree : public Storage::Tree_Binary_Search_AVL<DataType, KeyType, NodeType>
	{
	public:
		Painter::Tree::Serialized_Container<DataType, 2> Capture_Snapshot()
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

	class AVL_Tree : public Tree::Base<int, 2>
	{
		Adapter::AVL_Tree<int, int> tree;

	public:
		AVL_Tree();
		// ~Search_Tree(){};
	public:
		void Element_Insert(int key, int element);
		void Element_Delete(int key);
		Node_Binary_Search_Balance<int, int> *Node_Search(int key);
	};
}

#include "../Structure.hpp"

#include "Operation.hpp"

namespace View
{
	class AVL_Tree : public Structure
	{
		Painter::AVL_Tree painter;
		Operation::Search_Tree operation;

	public:
		AVL_Tree()
		{
			Hook_Painter(&painter);
			Config_Operations();
		}
		~AVL_Tree() {};

	public: // interactions
		void Config_Operations() override
		{
			auto layout = operation.Generate();
			ui.tab_operations->setLayout(layout);

			connect(operation.button_insert, &QPushButton::clicked, this, &AVL_Tree::Handle_Element_Insert);
			connect(operation.button_delete, &QPushButton::clicked, this, &AVL_Tree::Handle_Element_Delete);
			connect(operation.button_search, &QPushButton::clicked, this, &AVL_Tree::Handle_Node_Search);
		}

		void Handle_Element_Insert();
		void Handle_Element_Delete();
		void Handle_Node_Search();
	};

}
