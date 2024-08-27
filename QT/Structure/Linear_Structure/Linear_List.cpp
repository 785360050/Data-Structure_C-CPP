#include "Linear_List.hpp"

#include <iostream>

void View::Linear_List::Config_Operations()
{
	QHBoxLayout* line_insert=new QHBoxLayout;
	line_insert->addWidget(button_insert);
	line_insert->addWidget(input_insert_element);
	line_insert->addWidget(input_insert_pos);
	input_insert_element->setPlaceholderText("element");
	input_insert_pos->setPlaceholderText("position");

	QHBoxLayout* line_delete=new QHBoxLayout;
	line_delete->addWidget(button_delete);
	line_delete->addWidget(input_delete_pos);
	input_delete_pos->setPlaceholderText("position");

	QHBoxLayout* line_index=new QHBoxLayout;
	line_index->addWidget(button_index);
	line_index->addWidget(input_index);
	input_index->setPlaceholderText("index");

	QVBoxLayout* layout=new QVBoxLayout;
	layout->addLayout(line_insert);
	layout->addLayout(line_delete);
	layout->addLayout(line_index);
	layout->addWidget(button_get_size);
	layout->addWidget(button_is_empty);
	layout->addWidget(button_clear);

	ui.tab_operations->setLayout(layout);

	connect(button_insert,&QPushButton::clicked,this,&Linear_List::Element_Insert);
	connect(button_delete,&QPushButton::clicked,this,&Linear_List::Element_Delete);
	connect(button_index,&QPushButton::clicked,this,&Linear_List::Element_Get);
	connect(button_get_size,&QPushButton::clicked,this,&Linear_List::Get_Size);
	connect(button_is_empty,&QPushButton::clicked,this,&Linear_List::Is_Empty);
	connect(button_clear,&QPushButton::clicked,this,&Linear_List::Clear);
}

void View::Linear_List::Is_Empty()
{
	try
	{
		bool result=painter.Is_Empty();
		std::cout<<"Is Empty?";
		std::cout<<std::boolalpha<<result;
		Refresh_View();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}



void View::Linear_List::Element_Insert()
{
	int element{input_insert_element->text().toInt()};
	int position{input_insert_pos->text().toInt()};

	try
	{
		painter.Element_Insert(position,element);
		Refresh_View();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
void View::Linear_List::Element_Delete()
{
	int index{input_delete_pos->text().toInt()};
	try
	{
		painter.Element_Delete(index);
		Refresh_View();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
void View::Linear_List::Element_Get()
{
	int index{input_index->text().toInt()};
	try
	{
		auto element=painter[index];
		std::cout<<"Top = "+std::to_string(element);
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}

}

void View::Linear_List::Element_Update()
{
	try{std::cout<<"Is Empty ? "<<std::boolalpha<<painter.Is_Empty();}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}

void View::Linear_List::Get_Size()
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

void View::Linear_List::Clear()
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
