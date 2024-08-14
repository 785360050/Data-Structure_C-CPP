#pragma once

#include <QGraphicsItem>
#include <QRandomGenerator>


namespace Painter
{
class Painter: public QGraphicsItem
{
private:
	QRect size;
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

	QRectF boundingRect() const override { return size; };
	// void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

}
