#pragma once

#include "../../Painter/Painter.hpp"

namespace Painter
{

	class Skip_List : public Painter::Painter
	{
	public:
		Skip_List();
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	};
}

#include "../Structure.hpp"


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
