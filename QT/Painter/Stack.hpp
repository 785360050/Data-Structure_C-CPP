#pragma once

#include <iostream>

#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QMessageBox>


// #include "../../Data_Sturcture/C++/Linear_Structure/Linear_Stack/Stack.hpp"
#include "../../Data_Sturcture/C++/Linear_Structure/Linear_Stack/Linear_Stack_Sequential/Sequential_Stack.hpp"


#include "Painter.hpp"



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
	// QRectF boundingRect() const override { return size; };

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public: // Interactions
	void Element_Push(const DataType &element) { stack.Element_Push(element); }
	void Element_Pop() { stack.Element_Pop(); }
	int Get_Top()  { return stack.Get_Top(); }
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
