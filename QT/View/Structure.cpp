#include "Structure.hpp"

#include <QGraphicsRectItem>
#include <QGraphicsView>

// 鼠标移动，point是 GraphicsView的坐标,物理坐标
void Structure::do_mouseMovePoint(QPoint point)
{
	// labViewCord->setText(QString::asprintf("View 坐标：%d,%d", point.x(), point.y()));
	QPointF pointScene = ui.view->mapToScene(point); // 转换到Scene坐标
	// labSceneCord->setText(QString::asprintf("Scene 坐标：%.0f,%.0f", pointScene.x(), pointScene.y()));
}
// 鼠标单击
void Structure::do_mouseClicked(QPoint point)
{
	QPointF pointScene = ui.view->mapToScene(point); // 转换到Scene坐标
	QGraphicsItem *item = NULL;
	item = scene->itemAt(pointScene, ui.view->transform()); // 获取光标下的绘图项
	if (item != NULL)										// 有绘图项
	{
		QPointF pointItem = item->mapFromScene(pointScene); // 转换为绘图项的局部坐标
		// labItemCord->setText(QString::asprintf("Item 坐标：%.0f,%.0f", pointItem.x(), pointItem.y()));
	}
}

// Structure::Structure(Painter::Painter* painter,QWidget *parent)
Structure::Structure(QWidget *parent)
	:QWidget(parent)
	// ,painter{painter}
{
	ui.setupUi(this);

	// Config Graphics View
	ui.view->setCursor(Qt::CrossCursor);				 // 十字光标
	ui.view->setMouseTracking(true);					 // 鼠标跟踪
	ui.view->setDragMode(QGraphicsView::RubberBandDrag); // 矩形选择框

	QRectF rect(-500, -250, 1000, 500);
	scene = new QGraphicsScene(rect, this); // scene逻辑坐标系定义
	// scene->setSceneRect(ui.view->rect());
	ui.view->setScene(scene);				// 为视图设置场景

	connect(ui.view, &GraphicsView::mouseMovePoint, this, &Structure::do_mouseMovePoint);
	connect(ui.view, &GraphicsView::mouseClicked, this, &Structure::do_mouseClicked);

	auto scene_edge = new QGraphicsRectItem(rect);
	scene_edge->setPen(QPen{Qt::gray, 5});
	scene->addItem(scene_edge);



}


