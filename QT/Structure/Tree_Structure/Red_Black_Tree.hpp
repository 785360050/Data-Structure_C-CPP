#pragma once

#include "../../Painter/Painter.hpp"
#include "../../Painter/Tree.hpp"

#include "../../Data_Sturcture/C++/Tree_Structure/Tree/Tree_Binary/Tree_Binary_Search/Red_Black_Tree/Tree_Binary_Search_BRT.hpp"

namespace Adapter
{
	template <typename DataType, typename KeyType, typename NodeType = Node_Binary_Search_RB<DataType, KeyType>>
	class RB_Tree : public Storage::Tree_Binary_Search_RBT<DataType, KeyType, NodeType>
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
	class Tree_Binary_Search_RBT : public Tree::Base<int,2>
	{
		Adapter::RB_Tree<int, int> tree;
	public:
		Tree_Binary_Search_RBT();
		// ~Search_Tree(){};
	public:
		void Element_Delete(int key);
		void Element_Insert(int key, int element);
		Node_Binary_Search_RB<int, int> *Node_Search(int key)
		{
			return tree.Node_Search(key);
		}
	};
}

#include "../Structure.hpp"
#include "Operation.hpp"

namespace View
{
	class Tree_Binary_Search_RBT : public Structure
	{
		Painter::Tree_Binary_Search_RBT painter;
		Operation::Search_Tree operation;

	public:
		Tree_Binary_Search_RBT()
		{
			Hook_Painter(&painter);
			Config_Operations();
		}
		~Tree_Binary_Search_RBT() {};

	public: // interactions
		void Config_Operations() override;

		void Handle_Element_Insert();
		void Handle_Element_Delete();
		void Handle_Node_Search();
	};

}
