#pragma once

#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QMessageBox>

#include "../Structure.hpp"

#include <QPushButton>
#include <QLineEdit>


#include "../Painter/Painter.hpp"

#include "../../Data_Sturcture/C++/Linear_Structure/Linear_List/Sequential_List/Sequential_List.hpp"

using DataType = int;
static const int capcity=10;

namespace Painter
{
	// Wrapper of Datastructure & QT
	// template<typename DataType>
	class Linear_List : public Painter
	{
		// std::array<DataType,10> list;
		Sequential_List_Static<DataType,10> list;

	public:
		Linear_List()
		{
			for (int i = 1; i <= 5; i++)
				list.Element_Insert(i, i);
		}

	protected:
		void Draw_Element(QPainter* painter,const QPoint& pos,int index,const QString& text={})
		{
			painter->drawRect(pos.x(),pos.y(),50,50);
			painter->drawText(QRect(pos.x(),pos.y(),50,50),Qt::AlignCenter,text);

			// tag list index
			painter->setPen({Qt::gray, 5});
			painter->drawText(QRect(pos.x(),pos.y()+50,50,50),Qt::AlignCenter,QString::fromStdString(std::to_string(index)));
		}
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
		{
			painter->setPen({Qt::white, 5});
			static QFont font{"Cascadia Code",16};
			painter->setFont(font);

			QPoint pos{200,-60};
			int count{};
			int size=list.Get_Size();
			// for(int i{1};i<=capcity;++i)
			for(int i{capcity};i>0;--i)
			{
				if(i<=size)
				{
					painter->setPen({Qt::white, 5});
					Draw_Element(painter,pos,i,QString::fromStdString(std::to_string(list[i])));
				}
				else
				{
					painter->setPen({Qt::gray, 5});
					Draw_Element(painter,pos,i);
				}
				pos+=QPoint{-50,0};
			}
		}

	public: // Interactions
		bool Is_Empty() { return list.Is_Empty();}
		int Get_Size() { return list.Get_Size();}
		void Clear() { list.List_Clear();};
		// 在index位置插入element
		void Element_Insert(int index,const DataType& element){list.Element_Insert(index,element);}
		// 删除index位置的元素
		void Element_Delete(int index){list.Element_Delete(index);}
		// 获取index位置的元素
		DataType operator[](int index){return list[index];}
		// 设置index位置的元素为element
		void Element_Update(int index,DataType&&  element){list.Element_Update(index,std::forward<DataType>(element));};
	};
}


namespace View
{
	class Linear_List : public Structure
	{
		Painter::Linear_List painter;

	protected:
		void Config_Operations() override;

	public:
		Linear_List()
		{
			Hook_Painter(&painter);
			Config_Operations();
		}

	public: // interactions
		QPushButton *button_insert{new QPushButton("Insert")};
		QLineEdit *input_insert_element{new QLineEdit};
		QLineEdit *input_insert_pos{new QLineEdit};
		QPushButton *button_delete{new QPushButton("Delete")};
		QLineEdit *input_delete_pos{new QLineEdit};
		QPushButton *button_index{new QPushButton("Index")};
		QLineEdit *input_index{new QLineEdit};
		QPushButton *button_get_size{new QPushButton("Get Size")};
		QPushButton *button_is_empty{new QPushButton("Is Empty?")};
		QPushButton *button_clear{new QPushButton("Clear")};
		void Is_Empty();
		void Get_Size();
		void Clear();
		// 在index位置插入element
		void Element_Insert();
		// 删除index位置的元素
		void Element_Delete();
		// 获取index位置的元素
		void Element_Get();
		// 设置index位置的元素为element
		void Element_Update();
	};
}
