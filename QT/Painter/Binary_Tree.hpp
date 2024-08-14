#pragma once


#include "Painter.hpp"

struct BTNode
{
	QChar data;
	BTNode * lchild{nullptr};
	BTNode * rchild{nullptr};
};

class Binary_Tree : public Painter::Painter
{
	BTNode* root{nullptr};
protected:
	QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
	Binary_Tree();
	~Binary_Tree();
private:
	void drawNode(BTNode * node,QPainter & painter,QPoint dataCircleCenter);
};

