#pragma once

#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QMessageBox>

#include "../Structure.hpp"

#include <QPushButton>
#include <QLineEdit>


#include "../Painter/Painter.hpp"

#include <queue>
using DataType = int;

namespace Painter
{
	// Wrapper of Datastructure & QT
	// template<typename DataType>
	class Queue : public Painter
	{
		std::queue<DataType> queue;

	public:
		Queue()
		{
			for (int i = 10; i < 15; i++)
				queue.push(i);
			Update_Area_Size();

		}

	protected:
		void Draw_Element(QPainter* painter,const QPoint& pos,const QString& text={});
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

		void Update_Area_Size()
		{
			int width=queue.size()*50+200;
			this->area.setRect(-width/2,-25,width,50);
		}
	public: // Interactions
		void Element_Push(const DataType &element) { queue.push(element);Update_Area_Size();}
		void Element_Pop() { queue.pop();Update_Area_Size();}
		int Get_Front() { return queue.front();}
		bool Is_Empty() { return queue.empty();}
		int Get_Size() { return queue.size(); }
		void Clear() { while(!queue.empty())queue.pop(); Update_Area_Size();};
	};
}


namespace View
{
	class Queue : public Structure
	{
		Painter::Queue painter;

	protected:
		void Config_Operations() override;

	public:
		Queue()
		{
			Hook_Painter(&painter);
			Config_Operations();
		}

	public: // interactions
		QPushButton *button_push{new QPushButton("Push")};
		QPushButton *button_pop{new QPushButton("Pop")};
		QPushButton *button_get_front{new QPushButton("Get Top")};
		QPushButton *button_get_size{new QPushButton("Get Size")};
		QPushButton *button_is_empty{new QPushButton("Is Empty?")};
		QPushButton *button_clear{new QPushButton("Clear")};
		QLineEdit *input_push{new QLineEdit};
		void Element_Push();
		void Element_Pop();
		void Element_Get_Top();
		void Is_Empty();
		void Get_Size();
		void Clear();
	};
}
