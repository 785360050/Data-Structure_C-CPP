#pragma once

#include "ui_Structure.h"

#include <QGraphicsScene>

#include "../Painter/Painter.hpp"




class Structure : public QWidget
{
	Q_OBJECT
private slots:
	void do_mouseMovePoint(QPoint point); // 鼠标移动时处理
	void do_mouseClicked(QPoint point);	  // 鼠标左键单击时处理
protected:
	Ui::Structure ui;
	QGraphicsScene *scene;

	// Painter::Painter* painter{nullptr};
	void Refresh_View(){ui.view->viewport()->update();}

public:
	// explicit Structure(Painter::Painter* painter,QWidget *parent = nullptr);
	explicit Structure(QWidget *parent = nullptr);
public:
	virtual void Config_Operations(){};
	void Hook_Painter(Painter::Painter* painter){scene->addItem(painter);}



};


