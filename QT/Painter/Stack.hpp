#pragma once

#include <iostream>

#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QMessageBox>

#include "../Window.hpp"

// #include "../Data_Sturcture/C++/Linear_Structure/Linear_Stack/Stack.hpp"
// #include "../Data_Sturcture/C++/Linear_Structure/Linear_Stack/Linear_Stack_Sequential/Sequential_Stack.hpp"

#include "Painter.hpp"



#include <stack>
using DataType = int;

namespace Painter
{



// Wrapper of Datastructure & QT
// template<typename DataType>
class Stack : public Painter
{
	// QRect size;
	// Sequential_Stack<int, 5> stack;
	std::stack<DataType> stack;

public:
	Stack();

protected:
	// QRectF boundingRect() const override { return size; };

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public: // Interactions
	// void Element_Push(const DataType &element) { stack.Element_Push(element); }
	void Element_Push(const DataType &element) { stack.push(element); }
	// void Element_Push()
	// {
	// 	int element{Window::Instance().ui.input_push->text().toInt()};

	// 	try
	// 	{
	// 		// stack.Element_Push(element);
	// 		stack.push(element);
	// 		std::cout<<"Push: "+std::to_string(element);
	// 		Window::Instance().ui.view->viewport()->update();
	// 	}
	// 	catch(const std::exception& e)
	// 	{
	// 		QMessageBox::critical(&Window::Instance(),{},e.what());
	// 	}
	// }
	// void Element_Pop() { stack.Element_Pop(); }
	// int Get_Top()  { return stack.Get_Top(); }
	// bool Is_Empty() { return stack.Is_Empty(); }
	// int Get_Size() { return stack.Get_Size(); }
	// void Clear() { stack.Clear(); };
	void Element_Pop() { stack.pop(); }
	int Get_Top()  { return stack.top(); }
	bool Is_Empty() { return stack.empty(); }
	int Get_Size() { return stack.size(); }
	void Clear() { while(stack.size()){stack.pop();} };


	// void Bind()
	// {
	// 	Window::Instance().connect(Window::Instance().ui.button_push,&QPushButton::clicked,&Stack::Element_Push);
	// 	Window::Instance().connect(Window::Instance().ui.button_pop,&QPushButton::clicked,&Stack::Element_Pop);
	// 	Window::Instance().connect(Window::Instance().ui.button_get_top,&QPushButton::clicked,&Stack::Get_Top);
	// 	Window::Instance().connect(Window::Instance().ui.button_get_size,&QPushButton::clicked,&Stack::Get_Size);
	// 	Window::Instance().connect(Window::Instance().ui.button_is_empty,&QPushButton::clicked,&Stack::Is_Empty);
	// 	Window::Instance().connect(Window::Instance().ui.button_clear,&QPushButton::clicked,&Stack::Clear);
	// }
};
}
