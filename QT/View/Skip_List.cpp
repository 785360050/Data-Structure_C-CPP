#include "Skip_List.hpp"

#include <QPushButton>
#include <QLineEdit>

void View::Skip_List::Config_Operations()
{// init interact buttons

	QPushButton* button_insert=new QPushButton("Insert");
	QLineEdit* input_insert=new QLineEdit();
	QPushButton* button_delete=new QPushButton("Delete");
	QLineEdit* input_detele=new QLineEdit();
	QPushButton* button_search=new QPushButton("Search");
	QLineEdit* input_search=new QLineEdit();


	QHBoxLayout* line_insert=new QHBoxLayout;
	line_insert->addWidget(button_insert);
	line_insert->addWidget(input_insert);
	QHBoxLayout* line_delete=new QHBoxLayout;
	line_delete->addWidget(button_delete);
	line_delete->addWidget(input_detele);
	QHBoxLayout* line_search=new QHBoxLayout;
	line_search->addWidget(button_search);
	line_search->addWidget(input_search);

	QVBoxLayout* layout=new QVBoxLayout;
	layout->addLayout(line_insert);
	layout->addLayout(line_delete);
	layout->addLayout(line_search);

	ui.tab_operations->setLayout(layout);

	// connect(ui.button_push,&QPushButton::clicked,this,&Stack::Element_Push);
	// connect(ui.button_pop,&QPushButton::clicked,this,&Stack::Element_Pop);
	// connect(ui.button_get_top,&QPushButton::clicked,this,&Stack::Element_Get_Top);
	// connect(ui.button_get_size,&QPushButton::clicked,this,&Stack::Get_Size);
	// connect(ui.button_is_empty,&QPushButton::clicked,this,&Stack::Is_Empty);
	// connect(ui.button_clear,&QPushButton::clicked,this,&Stack::Clear);
}
