#pragma once

#include "Painter.hpp"

#include "../../Data_Sturcture/C++/Tree_Structure/Tree/Tree_Binary/Tree_Binary_Search/Normal_Tree/Binary_Tree_Search_Normal.hpp"

namespace Painter
{
class Search_Tree : public Painter::Painter
{
	Tree_Binary_Search_Normal<int,int> tree;
protected:
	// QRectF boundingRect() const override;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
	Search_Tree();
	// ~Search_Tree(){};
};
}

