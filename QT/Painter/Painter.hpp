#pragma once

#include <QGraphicsItem>
#include <QRandomGenerator>

#include <QPainter>
#include <QBrush>
#include <QPen>


namespace Painter
{
class Painter: public QGraphicsItem
{
protected:
	QRect area;
protected:
	QColor getRandomColor()
	{
		return QColor(QRandomGenerator::global()->bounded(255),
					  QRandomGenerator::global()->bounded(255),
					  QRandomGenerator::global()->bounded(255));
	}
public:
	Painter()
	{

	}
	virtual ~Painter()
	{

	}

	QRectF boundingRect() const override { return area; };
	// void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


};

}
