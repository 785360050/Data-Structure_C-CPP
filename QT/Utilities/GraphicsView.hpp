#pragma once

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>






class GraphicsView : public QGraphicsView
{
	Q_OBJECT
signals:
	void mouseMovePoint(QPoint point);
	void mouseClicked(QPoint point);
	void Resize(QSize size);

public:
	GraphicsView(QWidget *parent = nullptr) : QGraphicsView{parent} {}

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
protected:
	void resizeEvent(QResizeEvent *event) override
	{

		QGraphicsView::resizeEvent(event); // 调用基类的 resizeEvent 保持默认行为

		auto size=this->size();
		emit Resize(this->size());

		QRect rect={{-size.width()/2,-size.height()/2},size};
		fitInView(rect, Qt::KeepAspectRatio);  // 保持宽高比自适应视图




	}
};

