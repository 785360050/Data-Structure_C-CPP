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


#include <iostream>

#include <QMessageBox>

void View::Stack::Config_Operations()
{// init interact buttons


	QHBoxLayout* line_push=new QHBoxLayout;
	line_push->addWidget(button_push);
	line_push->addWidget(input_push);

	QHBoxLayout* line_delete=new QHBoxLayout;
	line_delete->addWidget(button_pop);

	QVBoxLayout* layout=new QVBoxLayout;
	layout->addLayout(line_push);
	layout->addLayout(line_delete);
	layout->addWidget(button_get_top);
	layout->addWidget(button_is_empty);
	layout->addWidget(button_get_size);
	layout->addWidget(button_clear);

	ui.tab_operations->setLayout(layout);

	connect(button_push,&QPushButton::clicked,this,&Stack::Element_Push);
	connect(button_pop,&QPushButton::clicked,this,&Stack::Element_Pop);
	connect(button_get_top,&QPushButton::clicked,this,&Stack::Element_Get_Top);
	connect(button_get_size,&QPushButton::clicked,this,&Stack::Get_Size);
	connect(button_is_empty,&QPushButton::clicked,this,&Stack::Is_Empty);
	connect(button_clear,&QPushButton::clicked,this,&Stack::Clear);
}

void View::Stack::Element_Push()
{
	int element{input_push->text().toInt()};

	try
	{
		painter.Element_Push(element);
		std::cout<<"Push: "+std::to_string(element);
		Refresh_View();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
void View::Stack::Element_Pop()
{
	try
	{
		painter.Element_Pop();
		std::cout<<"Pop";
		Refresh_View();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
void View::Stack::Element_Get_Top()
{
	try
	{
		auto element=painter.Get_Top();
		std::cout<<"Top = "+std::to_string(element);
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}

}

void View::Stack::Is_Empty()
{
	try{std::cout<<"Is Empty ? "<<std::boolalpha<<painter.Is_Empty();}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}

void View::Stack::Get_Size()
{
	try
	{
		std::cout<<"Size = "+std::to_string(painter.Get_Size());
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}

void View::Stack::Clear()
{
	try
	{
		painter.Clear();
		std::cout<<"Clear All Elements";
		Refresh_View();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}








