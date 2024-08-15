#include "Stack.hpp"

#include <QPainter>
#include <QPen>
#include <QRandomGenerator>


Painter::Stack::Stack()
{
	stack.Element_Push(1);
	stack.Element_Push(2);
	stack.Element_Push(3);

	// stack.push(1);
	// stack.push(2);
	// stack.push(3);
}



void Draw_Stack_Element(QPainter* painter,const QPoint& pos,const QString& text={})
{
	painter->drawRect(pos.x(),pos.y(),120,60);
	painter->drawText(QRect(pos.x(),pos.y(),120,60),Qt::AlignCenter,text);
}

void Painter::Stack::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	qDebug() << "paint";
	// // 绘制图形项
	// painter->setBrush(Qt::green);
	static QPen pen{Qt::gray, 5};
	painter->setPen(pen);
	static QFont font{"Cascadia Code",16};
	painter->setFont(font);

	auto copy_stack=stack;
	qDebug()<<&stack;
	QPoint pos{-60,-200};
	for(int i{5};i>0;--i)
	{
		auto size{copy_stack.Get_Size()};
		// auto size{copy_stack.size()};
		if(size!=i)
		{
			painter->setPen({Qt::gray, 5});
			Draw_Stack_Element(painter,pos);
		}
		else
		{
			painter->setPen({Qt::white, 5});
			Draw_Stack_Element(painter,pos,QString::fromStdString(std::to_string(copy_stack.Get_Top())));
			// Draw_Stack_Element(painter,pos,QString::fromStdString(std::to_string(copy_stack.top())));
			copy_stack.Element_Pop();
			// copy_stack.pop();
		}
		pos+=QPoint{0,60};
	}



}








