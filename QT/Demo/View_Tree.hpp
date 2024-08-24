#pragma once

#include "../Structure/Structure.hpp"


#include "Painter_Tree.hpp"

#include <QPushButton>
#include <QLineEdit>

namespace View
{

	template<typename DataType=int,int branch=2>
	class Tree : public Structure
	{
		Painter::Demo_Tree<DataType,branch> painter;
	public:
		Tree()
		{
			Hook_Painter(&painter);
			this->Config_Operations();
		}
		~Tree(){}

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
		// void Handle_();
		// void Handle_();
		// void Handle_();
		// void Handle_();
	};


}
