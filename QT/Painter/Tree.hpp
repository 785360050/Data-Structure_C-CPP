#pragma once

#include "Painter.hpp"


#include "../../Data_Sturcture/C++/Tree_Structure/Tree/HighOrder_Tree/Normal Tree/Tree_HighOrder_Child/Tree_HighOrder_Child.hpp"


template <int branch>
struct Tree_Coordinate
{
	QPoint left_top;
	int level{1};
	int width{};
	const QSize unit{50,50};
	const QSize half{unit/2};
	Tree_Coordinate()=delete;
	Tree_Coordinate(QPoint left_top,int level=1):left_top{left_top},level{level}
	{
		Update_Width();

		int offset=-(left_top.x())-width/2;
		this->left_top.setX(this->left_top.x()+offset);
	}

	void Update_Width()
	{
		width=std::pow(branch,level-1)*unit.width();
	}

	void Set_Level(int level)
	{
		this->level=level;
		Update_Width();
		Update();
	}

	void Update()
	{
		static std::vector<std::vector<QPoint>> position;
		for(int level{1};level<this->level;++level)
		{
			int level_node_count=std::pow(branch,level-1);
			std::vector<QPoint> level_position(level_node_count);
			position.push_back(level_position);
		}
		// ...
	}

	// Used to draw Nodes
	QRect Locate_Rectangle(int level,int index)
	{
		if(level<1)
			throw std::invalid_argument("level begin with 1");

		int level_node_count=std::pow(branch,level-1);
		if(index<0 or index > level_node_count)
			throw std::invalid_argument("level "+std::to_string(level)+" has index up to "+std::to_string(level_node_count));

		QPoint left_top;//LCD Coordinate Offset
		int unit_x=width/level_node_count;
		int x_middle_of_index=unit_x*(index+1)-unit_x/2;
		left_top.setX(x_middle_of_index-unit.width());
		left_top.setY((level-1)*(2*unit.height()));
		return QRect(left_top+this->left_top,unit);
	}

	// Used to draw Lines
	QPoint Locate_Center(int level,int index)
	{
		auto rect=Locate_Rectangle(level,index);
		return {rect.x()+half.width(),rect.y()+half.height()};
	}
};


namespace Painter
{
	using DataType=int;
	static const int branch{2};
	// template<typename DataType,int branch>
	class Tree : public Painter
	{
		Storage::Tree_Normal_Child_Ordered<int,2> tree;

		int level{0};
		const int branch{2};
		const QSize node_size{50,50};

		Tree_Coordinate<2> coordinate{QPoint{-500, -250},4};
	public:
		Tree();
		~Tree(){}
	private:
		void Update_Coordinate()
		{
			auto level=tree.Get_Depth(tree.Get_Root());
			if(level>coordinate.level)
			coordinate.Set_Level(level);
		}
		void Draw_Node(QPainter& painter,const std::string& name,QRect location);
		void LevelOrder_Traverse(TreeNode_HighOrder_Child_Ordered<int,2>* node,QPainter& painter);
	public:
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	};

}
