#include "Stack.hpp"

#include <iostream>



#include <QMessageBox>
void Stack::Element_Push()
{
	int element{ui.input_push->text().toInt()};

	try
	{
		painter.Element_Push(element);
		std::cout<<"Push: "+std::to_string(element);
		ui.view->viewport()->update();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
void Stack::Element_Pop()
{
	try
	{
		painter.Element_Pop();
		std::cout<<"Pop";
		ui.view->viewport()->update();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
void Stack::Element_Get_Top()
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

void Stack::Is_Empty()
{
	try{std::cout<<"Is Empty ? "<<std::boolalpha<<painter.Is_Empty();}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}

void Stack::Get_Size()
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

void Stack::Clear()
{
	try
	{
		painter.Clear();
		std::cout<<"Clear All Elements";
		ui.view->viewport()->update();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
