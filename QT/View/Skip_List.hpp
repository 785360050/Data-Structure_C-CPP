#pragma once

#include "Structure.hpp"

#include "../Painter/Skip_List.hpp"


namespace View
{
class Skip_List : public Structure
{
	Painter::Skip_List painter;
public:
	Skip_List()
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

	void Config_Operations() override;
};
}
