#include "Structure.hpp"

#include <QGraphicsRectItem>
#include <QGraphicsView>

#include "../Utilities/GraphicsView.hpp"

// 鼠标移动，point是 GraphicsView的坐标,物理坐标
void Structure::do_mouseMovePoint(QPoint point)
{
	// labViewCord->setText(QString::asprintf("View 坐标：%d,%d", point.x(), point.y()));
	QPointF pointScene = ui.view->mapToScene(point); // 转换到Scene坐标
	// labSceneCord->setText(QString::asprintf("Scene 坐标：%.0f,%.0f", pointScene.x(), pointScene.y()));
	emit Mouse_Move_Point(point,pointScene);
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

void Structure::Resize_View(QSizeF size)
{
	QRectF rect={{-size.width()/2,-size.height()/2},size};

	view_edge->setRect(rect);

	auto size_scene=rect.size();
	size_scene.setWidth(size_scene.width()+scene_x_offset);
	size_scene.setHeight(size_scene.height()+scene_y_offset);
	QRectF rect_scene={{-size_scene.width()/2,-size_scene.height()/2},size_scene};
	scene_edge->setRect(rect_scene);

	ui.view->setSceneRect(rect_scene);
}

void Structure::Resize_Scene(QSizeF size)
{
	// auto current_size=ui.view->sceneRect().size();
	auto current_size=ui.view->scene()->sceneRect();
	scene_x_offset=size.width()-current_size.width();
	scene_y_offset=size.height()-current_size.height();
	Resize_View(ui.view->size());

}
#include <QScrollBar>
Structure::Structure(QWidget *parent)
	:QWidget(parent)
{
	ui.setupUi(this);

	// Config Graphics View
	ui.view->setCursor(Qt::CrossCursor);				 // 十字光标
	ui.view->setMouseTracking(true);					 // 鼠标跟踪
	// ui.view->setDragMode(QGraphicsView::RubberBandDrag); // 矩形选择框

	QRectF rect(-500, -250, 1000, 500);
	scene = new QGraphicsScene(rect, this); // scene逻辑坐标系定义
	ui.view->setScene(scene);				// 为视图设置场景


	connect(ui.view, &GraphicsView::mouseMovePoint, this, &Structure::do_mouseMovePoint);
	connect(ui.view, &GraphicsView::mouseClicked, this, &Structure::do_mouseClicked);

	connect(ui.view,&GraphicsView::Resize,this,&Structure::Resize_View);

	scene_edge->setPen(QPen{Qt::green, 5});
	scene->addItem(scene_edge);
	view_edge->setPen(QPen{Qt::gray, 5});
	scene->addItem(view_edge);



	connect(ui.view->horizontalScrollBar(), &QScrollBar::valueChanged, ui.view->viewport(), [&](){ui.view->viewport()->update();});
	connect(ui.view->verticalScrollBar(), &QScrollBar::valueChanged, ui.view->viewport(), [&](){ui.view->viewport()->update();});



}


