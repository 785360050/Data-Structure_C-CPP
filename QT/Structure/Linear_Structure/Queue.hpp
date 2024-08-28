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

		}

	protected:
		void Draw_Element(QPainter* painter,const QPoint& pos,const QString& text={})
		{
			painter->setPen({Qt::white, 5});
			painter->drawRect(pos.x(),pos.y(),50,50);
			painter->drawText(QRect(pos.x(),pos.y(),50,50),Qt::AlignCenter,text);
		}
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
		{
			painter->setPen({Qt::gray, 5});
			static QFont font{"Cascadia Code",16};
			painter->setFont(font);

			auto copy_queue=queue;
			QPoint pos{-200,-60};
			painter->drawText(QRect(pos.x()-100,pos.y(),100,50),Qt::AlignCenter,"Front");
			while(!copy_queue.empty())
			{
				Draw_Element(painter,pos,QString::fromStdString(std::to_string(copy_queue.front())));
				copy_queue.pop();

				pos+=QPoint{50,0};
			}
			painter->drawText(QRect(pos.x()+25,pos.y(),50,50),Qt::AlignCenter,"Back");
		}

	public: // Interactions
		void Element_Push(const DataType &element) { queue.push(element);}
		void Element_Pop() { queue.pop();}
		int Get_Front() { return queue.front();}
		bool Is_Empty() { return queue.empty();}
		int Get_Size() { return queue.size(); }
		void Clear() { while(!queue.empty())queue.pop(); };
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
