#pragma once

#include "Structure.hpp"

#include "../Painter/Stack.hpp"

class Stack : public Structure
{
	Painter::Stack painter;
public:
	Stack()
	{
		Hook_Painter(&painter);
		Config_Operations();
	}

public: // interactions
	void Element_Push();
	void Element_Pop();
	void Element_Get_Top();
	void Is_Empty();
	void Get_Size();
	void Clear()   ;

	void Config_Operations() override
	{// init interact buttons
		// Stack
		connect(ui.button_push,&QPushButton::clicked,this,&Stack::Element_Push);
		connect(ui.button_pop,&QPushButton::clicked,this,&Stack::Element_Pop);
		connect(ui.button_get_top,&QPushButton::clicked,this,&Stack::Element_Get_Top);
		connect(ui.button_get_size,&QPushButton::clicked,this,&Stack::Get_Size);
		connect(ui.button_is_empty,&QPushButton::clicked,this,&Stack::Is_Empty);
		connect(ui.button_clear,&QPushButton::clicked,this,&Stack::Clear);
	}
};

