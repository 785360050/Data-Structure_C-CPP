#pragma once

#include "Painter.hpp"

#include "../../Data_Sturcture/C++/Tree_Structure/Tree/Tree_Binary/Tree_Binary_Search/Normal_Tree/Binary_Tree_Search_Normal.hpp"
// #include "../../Data_Sturcture/C++/Tree_Structure/Tree/HighOrder_Tree/Normal Tree/Tree_HighOrder_Child/Tree_HighOrder_Child.hpp"

#include "Tree.hpp"


namespace Adapter
{
	template <typename DataType, typename KeyType, typename NodeType=Node_Binary_Search_Normal<DataType,KeyType>>
	class Tree_Binary_Search:public Tree_Binary_Search_Normal<DataType,KeyType,NodeType>
	{
	public:
		Painter::Tree_Container<DataType,2> Capture_Snapshot()
		{
			Painter::Tree_Container<DataType,2> container;
			container.Set_Level(5);
			std::queue<NodeType*> queue;
			queue.push(this->root);

			for(int level{1};level<5;++level)
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
						queue.push(nullptr);
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
	Tree_Container<int,2> container;
	Tree_Drawer<int,2> drawer;

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

