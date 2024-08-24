#pragma once

#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QMessageBox>

#include "../Structure.hpp"

#include <QPushButton>
#include <QLineEdit>


// #include "../../Data_Sturcture/C++/Linear_Structure/Linear_Stack/Stack.hpp"
#include "../../Data_Sturcture/C++/Linear_Structure/Linear_Stack/Linear_Stack_Sequential/Sequential_Stack.hpp"

#include "../Painter/Painter.hpp"

#include <stack>
using DataType = int;

namespace Painter
{
	// Wrapper of Datastructure & QT
	// template<typename DataType>
	class Stack : public Painter
	{
		Sequential_Stack<int, 5> stack;
		// std::stack<DataType> stack;

	public:
		Stack();

	protected:
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

	public: // Interactions
		void Element_Push(const DataType &element) { stack.Element_Push(element); }
		void Element_Pop() { stack.Element_Pop(); }
		int Get_Top() { return stack.Get_Top(); }
		bool Is_Empty() { return stack.Is_Empty(); }
		int Get_Size() { return stack.Get_Size(); }
		void Clear() { stack.Clear(); };
		// void Element_Push(const DataType &element) { stack.push(element); }
		// void Element_Pop() { stack.pop(); }
		// int Get_Top()  { return stack.top(); }
		// bool Is_Empty() { return stack.empty(); }
		// int Get_Size() { return stack.size(); }
		// void Clear() { while(stack.size()){stack.pop();} };
	};
}


namespace View
{
	class Stack : public Structure
	{
		Painter::Stack painter;

	protected:
		void Config_Operations() override;

	public:
		Stack()
		{
			Hook_Painter(&painter);
			Config_Operations();
		}

	public: // interactions
		QPushButton *button_push{new QPushButton("Push")};
		QPushButton *button_pop{new QPushButton("Pop")};
		QPushButton *button_get_top{new QPushButton("Get Top")};
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
