#pragma once

#include "Structure.hpp"

#include "../Painter/Binary_Tree.hpp"

class Binary_Tree : public Structure
{
	Painter::Binary_Tree painter;
public:
	Binary_Tree()
	{
		Hook_Painter(&painter);
		Config_Operations();
	}

public: // interactions
	// void Element_Push();
	// void Element_Pop();
	// void Element_Get_Top();
	// void Is_Empty();
	// void Get_Size();
	// void Clear()   ;

	void Config_Operations() override
	{// init interact buttons
		// connect(ui.button_push,&QPushButton::clicked,this,&Stack::Element_Push);
		// connect(ui.button_pop,&QPushButton::clicked,this,&Stack::Element_Pop);
		// connect(ui.button_get_top,&QPushButton::clicked,this,&Stack::Element_Get_Top);
		// connect(ui.button_get_size,&QPushButton::clicked,this,&Stack::Get_Size);
		// connect(ui.button_is_empty,&QPushButton::clicked,this,&Stack::Is_Empty);
		// connect(ui.button_clear,&QPushButton::clicked,this,&Stack::Clear);
	}
};

