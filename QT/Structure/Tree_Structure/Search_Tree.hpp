#pragma once

#include "../../Painter/Painter.hpp"

#include "../../Data_Sturcture/C++/Tree_Structure/Tree/Tree_Binary/Tree_Binary_Search/Normal_Tree/Binary_Tree_Search_Normal.hpp"
// #include "../../Data_Sturcture/C++/Tree_Structure/Tree/HighOrder_Tree/Normal Tree/Tree_HighOrder_Child/Tree_HighOrder_Child.hpp"

#include "../../Painter/Tree.hpp"

namespace Adapter
{
	template <typename DataType, typename KeyType, typename NodeType = Node_Binary_Search_Normal<DataType, KeyType>>
	class Tree_Binary_Search : public Tree_Binary_Search_Normal<DataType, KeyType, NodeType>
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

	class Search_Tree : public Tree::Base<int, 2>
	{
		Adapter::Tree_Binary_Search<int, int> tree;

	public:
		Search_Tree();
		// ~Search_Tree(){};
	public:
		void Element_Delete(int key);
		void Element_Insert(int key, int element);
		Node_Binary_Search_Normal<int, int> *Node_Search(int key)
		{
			return tree.Node_Search(key);
		}
	};
}

#include "../Structure.hpp"

#include "Operation.hpp"

namespace View
{
	class Search_Tree : public Structure
	{
		Painter::Search_Tree painter;
		Operation::Search_Tree operation;

	public:
		Search_Tree()
		{
			Hook_Painter(&painter);
			Config_Operations();
		}
		~Search_Tree() {};

	public: // interactions
		void Config_Operations() override;

		void Handle_Element_Insert();
		void Handle_Element_Delete();
		void Handle_Node_Search();
	};
}
