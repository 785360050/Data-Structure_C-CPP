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
	template<typename DataType,int branch>
	class Tree : public Painter
	{
		Storage::Tree_Normal_Child_Ordered<int,branch> tree;

		int level{0};
		// const int branch{2};
		const QSize node_size{50,50};

		Tree_Coordinate<branch> coordinate{QPoint{-500, -250},4};
	public:
		Tree()
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
			this->size=bound;

		}
		~Tree(){}
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


	template<typename DataType,int branch,typename NodeType=TreeNode<DataType>>
	struct Tree_Container
	{
		std::vector<std::vector<NodeType*>> container;
		Tree_Container()=default;
		Tree_Container(int level)
		{
			for(int i{1};i<=level;++i)
				container[i].resize(Level_Node_Count(level));
		}

		int Level_Node_Count(int level) const {return std::pow(branch,level-1);}
		void Set_Level(int level)
		{
			int current_level{container.size()};
			if(current_level==level)
				return;
			container.resize(level);
			for(int i{1};i<=level;++i)
			{
				auto count=Level_Node_Count(i);
				container[i-1].resize(count);
			}
		}
		int Get_Level() const {return container.size();}
		std::vector<NodeType*> Get_Level_Node(int level) const {return container[--level];}
		std::pair<int,int> Parent_Index(int level,int index) const {return {--level,index/branch};}

		bool Has_parent(int level,int index)
		{
			if(level<=1)
				return false;

			auto [parent_level,parent_index]=Parent_Index(level,index);
			if(!at(parent_level,parent_index))
				return false;

			return true;
		}
		NodeType* at(int level,int index)
		{
			return container.at(--level).at(index);
		}

		void Set(NodeType* node,int level,int index){container[--level][index]=node;}
	};

	template<typename DataType,int branch>
	class Tree_Drawer
	{
		Tree_Coordinate<branch> coordinate{QPoint{-500, -250},4};
		Tree_Container<DataType,branch> container;
		int level{0};
		const QSize node_size{50,50};

	public:
		Tree_Drawer()=default;
		Tree_Drawer(QSize node_size):node_size{node_size}
		{
			QRect bound;
			bound.setHeight((2*level-1)*node_size.height());
			int leaves_count=std::pow(branch,level-1);
			bound.setWidth(leaves_count*node_size.width());
			this->size=bound;

		}
		~Tree_Drawer(){}
	private:
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
		void Paint_In_Levelorder(QPainter& painter)
		{
			// iterate from bottom to top to keep line under the node
			for(int level{container.Get_Level()};level>=1;--level)
			{
				auto level_node=container.Get_Level_Node(level);
				for(int index{};index<level_node.size();++index)
				{
					// Then Draw Node Cover on line
					auto node=container.at(level,index);
					if(!node)
						continue;

					// Draw Line Fisrt
					if(container.Has_parent(level,index))
					{
						auto [parent_level,parent_index]=container.Parent_Index(level,index);
						auto point_begin=coordinate.Locate_Center(parent_level,parent_index);
						auto point_end=coordinate.Locate_Center(level,index);
						Draw_Line(painter,point_begin,point_end);
					}

					Draw_Node(painter,node->name,coordinate.Locate_Rectangle(level,index));
				}
			}
		}
	public:
		void Update_Tree(const Tree_Container<DataType,branch>& container){this->container=std::move(container);}
		void Draw(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
		{
			static QFont font{"Cascadia Code",18};
			painter->setFont(font);
			painter->setRenderHint(QPainter::Antialiasing,true);

			Paint_In_Levelorder(*painter);


		}
	};


}
