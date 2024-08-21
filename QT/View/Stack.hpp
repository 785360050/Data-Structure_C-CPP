#pragma once

#include "Structure.hpp"

#include "../Painter/Stack.hpp"

#include <QPushButton>
#include <QLineEdit>


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
	QPushButton* button_push{new QPushButton("Push")};
	QPushButton* button_pop{new QPushButton("Pop")};
	QPushButton* button_get_top{new QPushButton("Get Top")};
	QPushButton* button_get_size{new QPushButton("Get Size")};
	QPushButton* button_is_empty{new QPushButton("Is Empty?")};
	QPushButton* button_clear{new QPushButton("Clear")};
	QLineEdit* input_push{new QLineEdit};
	void Element_Push();
	void Element_Pop();
	void Element_Get_Top();
	void Is_Empty();
	void Get_Size();
	void Clear()   ;


};
}
