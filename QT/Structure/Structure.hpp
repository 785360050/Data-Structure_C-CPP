#pragma once

#include "ui_Structure.h"

#include <QGraphicsScene>

#include "../Painter/Painter.hpp"


#include <QWidget>


class Structure : public QWidget
{
	Q_OBJECT
signals:
	void Size_Update(QSize size);
	void Mouse_Move_Point(QPoint point_view,QPointF point_scene);
private slots:
	void do_mouseMovePoint(QPoint point); // 鼠标移动时处理
	void do_mouseClicked(QPoint point);	  // 鼠标左键单击时处理
	void Resize_View(QSizeF size);
	void Resize_Scene(QSizeF size);

protected:
	Ui::Structure ui;
	QGraphicsScene *scene;

	// used to update scene size
	double scene_x_offset;
	double scene_y_offset;
	QGraphicsRectItem* view_edge{new QGraphicsRectItem(QRect{-500, -250, 1000, 500})};//for debug
	QGraphicsRectItem* scene_edge{new QGraphicsRectItem(QRect{-500, -250, 1000, 500})};//for debug

	// Painter::Painter* painter{nullptr};
	void Refresh_View(QSizeF size=QSizeF{})
	{
		Resize_Scene(size);
		ui.view->viewport()->update();
	}


public:
	// explicit Structure(Painter::Painter* painter,QWidget *parent = nullptr);
	explicit Structure(QWidget *parent = nullptr);
public:
	virtual void Config_Operations(){};
	void Hook_Painter(Painter::Painter* painter){scene->addItem(painter);}

	QPixmap Grab_Picture()const{return ui.view->grab();}

};


