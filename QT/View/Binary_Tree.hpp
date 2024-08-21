#pragma once

#include "Structure.hpp"

#include "../Painter/Binary_Tree.hpp"

#include <QPushButton>
#include <QLineEdit>

namespace View
{

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
	// QPushButton* button_push{new QPushButton("Push")};
	// QPushButton* button_pop{new QPushButton("Pop")};
	// QPushButton* button_get_top{new QPushButton("Get Top")};
	// QPushButton* button_get_size{new QPushButton("Get Size")};
	// QPushButton* button_is_empty{new QPushButton("Is Empty?")};
	// QPushButton* button_clear{new QPushButton("Clear")};
	// QLineEdit* input_push{new QLineEdit};
	void Config_Operations() override
	{

	}

	// void Handle_Node_Insert(,int element,position);

};
}

