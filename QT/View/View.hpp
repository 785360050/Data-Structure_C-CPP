#pragma once

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>



class View : public QGraphicsView
{
	Q_OBJECT
signals:
	void mouseMovePoint(QPoint point);
	void mouseClicked(QPoint point);

public:
	View(QWidget *parent = nullptr) : QGraphicsView{parent} {}

protected:
	void mouseMoveEvent(QMouseEvent *event) override
	{								 // 鼠标移动事件
		QPoint point = event->pos(); // QGraphicsView的坐标
		emit mouseMovePoint(point);	 // 释放信号
		QGraphicsView::mouseMoveEvent(event);
	}

	void mousePressEvent(QMouseEvent *event) override
	{ // 鼠标左键按下事件
		if (event->button() == Qt::LeftButton)
		{
			QPoint point = event->pos(); // QGraphicsView的坐标
			emit mouseClicked(point);	 // 释放信号
		}
		QGraphicsView::mousePressEvent(event);
	}

};
