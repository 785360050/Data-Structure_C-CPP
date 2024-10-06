#pragma once

#include "../Painter/Painter.hpp"
#include "../Painter/Tree.hpp"



#include "../../Data_Sturcture/C++/Tree_Structure/Tree/HighOrder_Tree/Normal Tree/Tree_HighOrder_Child/Tree_HighOrder_Child.hpp"


namespace Painter
{



template<typename DataType,int branch>
class Demo_Tree : public Painter
{
	Storage::Tree_Normal_Child_Ordered<int,branch> tree;

	int level{0};
	// const int branch{2};
	const QSize node_size{50,50};

	Tree::Coordinate<branch> coordinate{QPoint{-500, -250},4};
public:
	Demo_Tree()
	{
		// Update_Cooridate();

		auto a = tree.Node_Create("A");
		auto b = tree.Node_Create("B");
		auto c = tree.Node_Create("C");
		auto d = tree.Node_Create("D");
		auto e = tree.Node_Create("E");
		auto f = tree.Node_Create("F");
		auto g = tree.Node_Create("G");
		auto h = tree.Node_Create("H");
		// auto i = tree.Node_Create("I");
		auto j = tree.Node_Create("J");
		// auto k = tree.Node_Create("K");
		auto l = tree.Node_Create("L");
		auto m = tree.Node_Create("M");
		// auto n = tree.Node_Create("N");
		auto o = tree.Node_Create("O");

		tree.Tree_Set_Root(a);

		tree.Node_Insert(b, a, 1);
		tree.Node_Insert(c,a,2);
		tree.Node_Insert(d,b,1);
		tree.Node_Insert(e,b,2);
		tree.Node_Insert(f,c,1);
		tree.Node_Insert(g,c,2);
		tree.Node_Insert(h,d,1);
		// tree.Node_Insert(i,d,2);
		tree.Node_Insert(j,e,1);
		// tree.Node_Insert(k,e,2);
		tree.Node_Insert(l,f,1);
		tree.Node_Insert(m,f,2);
		// tree.Node_Insert(n,g,1);
		tree.Node_Insert(o,g,2);


		QRect bound;
		bound.setHeight((2*level-1)*node_size.height());
		int leaves_count=std::pow(branch,level-1);
		bound.setWidth(leaves_count*node_size.width());
		this->area=bound;

	}
	~Demo_Tree(){}
private:
	void Update_Coordinate()
	{
		auto level=tree.Get_Depth(tree.Get_Root());
		if(level>coordinate.level)
		coordinate.Set_Level(level);
	}
	void Draw_Line(QPainter& painter,const QPoint& begin,const QPoint& end)
	{
		painter.setPen({Qt::white,5});
		painter.drawLine(begin,end);
	}
	void Draw_Node(QPainter& painter,const std::string& name,QRect location)
	{

		static QPoint offsetPoint{20,20};
		static QPoint dataCircleCenter(0,-200);
		// static QPen whitePen{Qt::white,5};
		QRect rect = QRect(dataCircleCenter - offsetPoint,dataCircleCenter + offsetPoint);

		painter.setBrush(Qt::gray);
		painter.setPen({Qt::white,5});
		// painter.drawEllipse(rect);
		painter.drawEllipse(location);
		painter.setPen(QPen(Qt::black,5));
		painter.drawText(location,Qt::AlignCenter,QString::fromStdString(name));
	}
	void LevelOrder_Traverse(TreeNode_HighOrder_Child_Ordered<int,branch>* node,QPainter& painter)
	{
		std::queue<TreeNode_HighOrder_Child_Ordered<int,2>*> queue;
		queue.push(node);

		int level{1};
		// draw Nodes per level
		while(queue.size())
		{
			std::queue<TreeNode_HighOrder_Child_Ordered<int,2>*> paint_buffer=std::move(queue);
			int level_count=paint_buffer.size();
			for(int index{0};index<level_count;++index)
			{
				auto node=paint_buffer.front();

				if(node)
				{
					for(int i{0};i<node->children.size();++i)
					{
						if(!node->Has_Child(i))
						{
							queue.push(nullptr);
							continue;
						}
						auto index_child=node->children[i];// belone to Storage::Tree_Normals
						queue.push(tree.vertex[index_child]);

						QPoint node_position_current=coordinate.Locate_Center(level,index);
						QPoint node_position_child=coordinate.Locate_Center(level+1,index*branch+i);
						Draw_Line(painter,node_position_current,node_position_child);
					}

					Draw_Node(painter,node->name,coordinate.Locate_Rectangle(level,index));
				}
				paint_buffer.pop();
			}
			++level;
		}
	}
public:
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
	{
		static QFont font{"Cascadia Code",18};
		// QPaintDevice
		// QPainter painter{view};
		painter->setFont(font);
		painter->setRenderHint(QPainter::Antialiasing,true);

		LevelOrder_Traverse(tree.Get_Root(),*painter);


	}
};
}
