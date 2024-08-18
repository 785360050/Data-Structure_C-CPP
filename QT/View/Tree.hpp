#pragma once

#include "Structure.hpp"

#include "../Painter/Tree.hpp"

namespace View
{



class Tree : public Structure
{
	Painter::Tree painter;
public:
	Tree()
	{
		Hook_Painter(&painter);
		this->Config_Operations();
	}
	~Tree(){}

public: // interactions
	// void Element_Push();
	// void Element_Pop();
	// void Element_Get_Top();
	// void Is_Empty();
	// void Get_Size();
	// void Clear()   ;

	void Config_Operations() override
	{

	}
};


}
