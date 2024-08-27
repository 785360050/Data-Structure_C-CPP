#include "Skip_List.hpp"

#include "../../Data_Sturcture/C++/Linear_Structure/Linear_List/Link_List/Skip_List.hpp"

Painter::Skip_List::Skip_List()
{
	// test Element_Insert
	skip_list.Element_Insert(2);
	skip_list.Element_Insert(10);
	skip_list.Element_Insert(12);
	skip_list.Element_Insert(8);
	skip_list.Element_Insert(1);
	skip_list.Element_Insert(6);

	// skip_list.Element_Delete(1);
	// skip_list.Element_Delete(2);
	// skip_list.Element_Delete(6);
	// skip_list.Element_Delete(12);
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

void Draw_Node(QPainter* painter,const std::string& name,QRect location)
{
	// painter.setBrush(Qt::gray);
	// painter.setPen({Qt::white,5});
	// // painter.drawEllipse(rect);
	// painter.drawEllipse(location);
	// painter.setPen(QPen(Qt::black,5));
	// painter.drawText(location,Qt::AlignCenter,QString::fromStdString(name));

	static const QBrush brush_header{Qt::red};
	painter->setBrush(brush_header);
	painter->drawRect(location);
	painter->drawText(location,Qt::AlignCenter,QString::fromStdString(name));
}

void Painter::Skip_List::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	qDebug() << "paint";
	static QFont font{"Cascadia Code",12};
	static QPen pen{Qt::white, 5};
	static QBrush brush_element{Qt::blue};

	painter->setPen(pen);
	painter->setFont(font);


	static QSize block(50,50);
	static constexpr int half_size=25;


	std::vector<Adapter::Skip_List::Node *> storage=skip_list.Get_Storage();


	QPoint pos_left_top{-200,-60};

	const int current_level{skip_list.Get_Current_Level()};
	auto container=skip_list.Get_Container();

	for(int level{current_level-1};level>=0;--level)
	{
		QPoint pos=pos_left_top-QPoint{0,level*50};
		painter->drawText(pos-QPoint{100,-25},QString::fromStdString("Level "+std::to_string(level)));
		for(const auto& node:container[level])
		{
			if(node)
				Draw_Node(painter,std::to_string(node->element),QRect(pos.x(),pos.y(),50,50));
			else
			{

			}
			pos+=QPoint{50,0};
		}
	}


	// for(int level{0};level<current_level;++level)
	// {
	// 	QPoint pos=pos_left_top+QPoint{0,level*50};
	// 	painter->drawText(pos,QString::fromStdString("Level "+std::to_string(level)));

	// 	auto node=storage[level];
	// 	while(node)
	// 	{
	// 		// Draw_Arrow(*painter,{0-half_size,0},{0+block.width()/3*2,0});

	// 		// QRect rect(0-1*block.width(),0-half_size,block.width(),block.height());
	// 		auto element=node->element;
	// 		Draw_Node(painter,std::to_string(element),QRect(pos.x(),pos.y(),50,50));
	// 		node=node->next[level];
	// 		pos+=QPoint{50,0};
	// 	}
	// 	painter->drawText(0+1*block.width(),0,"nullptr");

	// }

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
