#include "Skip_List.hpp"

#include "../../Data_Sturcture/C++/Linear_Structure/Linear_List/Link_List/Skip_List.hpp"

Painter::Skip_List::Skip_List()
{
	Storage::Skip_List<int,0.5f> list;

	// test Element_Insert
	list.Element_Insert(2);
	// list.List_Show("插入2");
	list.Element_Insert(10);
	// list.List_Show("插入10");
	list.Element_Insert(12);
	// list.List_Show("插入12");
	list.Element_Insert(8);
	// list.List_Show("插入8");
	list.Element_Insert(1);
	// list.List_Show("插入1");
	list.Element_Insert(6);
	// list.List_Show("插入6");
	std::cout << "插入6个元素后,size =  " << list.Get_Size() ;

	// test Search
	std::cout << "Element Search 1 = " << list.Element_Search(1).value_or(-1) ;
	std::cout << "Element Search 2 = " << list.Element_Search(2).value_or(-1) ;
	std::cout << "Element Search 6 = " << list.Element_Search(6).value_or(-1) ;
	std::cout << "Element Search 10 = " << list.Element_Search(10).value_or(-1) ;
	std::cout << "Element Search 12 = " << list.Element_Search(12).value_or(-1) ;

	std::cout << "Element Search 111 = " << list.Element_Search(111).value_or(-1) ;
	std::cout << "Element Search 0 = " << list.Element_Search(0).value_or(-1) ;

	// test Element_Delete
	list.Element_Delete(1);
	// list.List_Show("删除1");
	list.Element_Delete(2);
	// list.List_Show("删除2");
	list.Element_Delete(6);
	// list.List_Show("删除6");
	list.Element_Delete(12);
	// list.List_Show("删除12");
	std::cout << "删除4个元素后,size =  " << list.Get_Size() ;
}

#include <QPainter>
#include <QFont>
#include <QPen>


void Draw_Arrow(QPainter& painter, QPoint start, QPoint end)
{
	static QPen pen{Qt::white, 5};
	painter.setRenderHint(QPainter::Antialiasing, true);

	qreal arrowSize = 15;
	painter.setPen(pen);
	painter.setBrush(pen.color());

	QLineF line(end, start);

	double angle = std::atan2(-line.dy(), line.dx());
	QPointF arrowP1 = line.p1() + QPointF(sin(angle + M_PI / 3) * arrowSize,
										  cos(angle + M_PI / 3) * arrowSize);
	QPointF arrowP2 = line.p1() + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
										  cos(angle + M_PI - M_PI / 3) * arrowSize);

	QPolygonF arrowHead;
	arrowHead.clear();
	arrowHead << line.p1() << arrowP1 << arrowP2;
	painter.drawLine(line);
	painter.drawPolygon(arrowHead);

}

void Painter::Skip_List::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	qDebug() << "paint";
	static QFont font{"Cascadia Code",12};
	static QPen pen{Qt::white, 5};
	static QBrush brush_element{Qt::blue};
	static QBrush brush_header{Qt::red};
	painter->setPen(pen);
	painter->setFont(font);


	static QSize block(50,50);
	static constexpr int half_size=25;

	painter->drawText(0-half_size-2*block.width(),0,"Level 0");

	painter->setBrush(brush_header);
	painter->drawRect(0-1*block.width(),0-half_size,block.width(),block.height());

	// painter->drawLine(0-half_size,0,0+half_size,0);
	Draw_Arrow(*painter,{0-half_size,0},{0+block.width()/3*2,0});

	painter->drawText(0+1*block.width(),0,"nullptr");


}

#include "Skip_List.hpp"

#include <QPushButton>
#include <QLineEdit>

void View::Skip_List::Config_Operations()
{ // init interact buttons

	QPushButton *button_insert = new QPushButton("Insert");
	QLineEdit *input_insert = new QLineEdit();
	QPushButton *button_delete = new QPushButton("Delete");
	QLineEdit *input_detele = new QLineEdit();
	QPushButton *button_search = new QPushButton("Search");
	QLineEdit *input_search = new QLineEdit();

	QHBoxLayout *line_insert = new QHBoxLayout;
	line_insert->addWidget(button_insert);
	line_insert->addWidget(input_insert);
	QHBoxLayout *line_delete = new QHBoxLayout;
	line_delete->addWidget(button_delete);
	line_delete->addWidget(input_detele);
	QHBoxLayout *line_search = new QHBoxLayout;
	line_search->addWidget(button_search);
	line_search->addWidget(input_search);

	QVBoxLayout *layout = new QVBoxLayout;
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
