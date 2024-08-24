#pragma once

#include <vector>
#include <cmath>

#include <QPoint>
#include <QSize>
#include <QRect>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "../../Data_Sturcture/C++/Tree_Structure/Tree/Tree_Node.hpp"

namespace Painter
{
	namespace Tree
	{
		template <int branch>
		struct Coordinate
		{
			QPoint left_top;
			int level{1};
			int width{};
			const QSize unit{50,50};
			const QSize half{unit/2};
			Coordinate()=delete;
			Coordinate(QPoint left_top,int level=1):left_top{left_top},level{level}
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

		template<typename DataType,int branch,typename NodeType=TreeNode<DataType>>
		struct Serialized_Container
		{
			std::vector<std::vector<NodeType*>> container;
			Serialized_Container()=default;
			Serialized_Container(int level)
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
		class Drawer
		{
			Coordinate<branch> coordinate{QPoint{-500, -250},4};
			Serialized_Container<DataType,branch> container;
			int level{0};
			QRect bound;
			const QSize node_size{50,50};

		public:
			Drawer()=default;
			Drawer(QSize node_size):node_size{node_size}
			{
				QRect bound;
				bound.setHeight((2*level-1)*node_size.height());
				int leaves_count=std::pow(branch,level-1);
				bound.setWidth(leaves_count*node_size.width());
				this->size=bound;

			}
			~Drawer(){}
		private:
			void Draw_Line(QPainter& painter,const QPoint& begin,const QPoint& end)
			{
				painter.setPen({Qt::white,5});
				painter.drawLine(begin,end);
			}
			void Draw_Node(QPainter& painter,const std::string& name,QRect location)
			{
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
			void Update_Tree(const Serialized_Container<DataType,branch>& container)
			{
				this->container=std::move(container);
				level=container.Get_Level();
				coordinate.Set_Level(level); // Update Coorinate Location Range

				bound.setHeight((2*level-1)*node_size.height());
				int leaves_count=std::pow(branch,level-1);
				bound.setWidth(leaves_count*node_size.width());
			}
			void Draw(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
			{
				static QFont font{"Cascadia Code",18};
				painter->setFont(font);
				painter->setRenderHint(QPainter::Antialiasing,true);

				Paint_In_Levelorder(*painter);
			}
		};

	}



}
