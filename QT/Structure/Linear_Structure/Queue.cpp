#include "Queue.hpp"

#include <iostream>

void View::Queue::Config_Operations()
{
	QHBoxLayout* line_push=new QHBoxLayout;
	line_push->addWidget(button_push);
	line_push->addWidget(input_push);

	QHBoxLayout* line_delete=new QHBoxLayout;
	line_delete->addWidget(button_pop);

	QVBoxLayout* layout=new QVBoxLayout;
	layout->addLayout(line_push);
	layout->addLayout(line_delete);
	layout->addWidget(button_get_front);
	layout->addWidget(button_is_empty);
	layout->addWidget(button_get_size);
	layout->addWidget(button_clear);

	ui.tab_operations->setLayout(layout);

	connect(button_push,&QPushButton::clicked,this,&Queue::Element_Push);
	connect(button_pop,&QPushButton::clicked,this,&Queue::Element_Pop);
	connect(button_get_front,&QPushButton::clicked,this,&Queue::Element_Get_Top);
	connect(button_get_size,&QPushButton::clicked,this,&Queue::Get_Size);
	connect(button_is_empty,&QPushButton::clicked,this,&Queue::Is_Empty);
	connect(button_clear,&QPushButton::clicked,this,&Queue::Clear);
}



void View::Queue::Element_Push()
{
	int element{input_push->text().toInt()};

	try
	{
		painter.Element_Push(element);
		std::cout<<"Push: "+std::to_string(element);
		Refresh_View(painter.boundingRect().size());
		// painter.boundingRect().size();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
void View::Queue::Element_Pop()
{
	try
	{
		painter.Element_Pop();
		std::cout<<"Pop";
		Refresh_View(painter.boundingRect().size());
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
void View::Queue::Element_Get_Top()
{
	try
	{
		auto element=painter.Get_Front();
		std::cout<<"Top = "+std::to_string(element);
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}

}

void View::Queue::Is_Empty()
{
	try{std::cout<<"Is Empty ? "<<std::boolalpha<<painter.Is_Empty();}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}

void View::Queue::Get_Size()
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

void View::Queue::Clear()
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
