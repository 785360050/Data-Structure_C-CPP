#pragma once

#include "Painter.hpp"

namespace Painter
{

class Skip_List : public Painter::Painter
{
public:
	Skip_List();
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;
};
}

