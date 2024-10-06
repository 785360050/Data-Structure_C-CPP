#pragma once

#include "./ui_Window.h"

#include <QtWidgets/QMainWindow>
#include <QLabel>

#include <vector>

#include "Painter/Painter.hpp"
// #include "Painter/Stack.hpp"
// #include "Painter/Binary_Tree.hpp"

#include "Structure/Factory.hpp"

class Structure;

class Window : public QMainWindow
{
	Q_OBJECT

// private:
public:
	Ui::Window ui;

	// 状态栏上坐标信息
	QLabel *labViewCord;
	QLabel *labSceneCord;
	QLabel *labItemCord;

public:
	Window(QWidget *parent = nullptr);
	~Window();

private:
	std::map<std::string,Structure*> structure;
	std::map<std::string,Factory::Factory*> factory;

	template<typename StructureType>
	void Register_Factory(const std::string& name){factory[name]=new StructureType;}
private:
	void Handle_Select_Structure(QTreeWidgetItem *item,int column);
	void Handle_Export_Picture();

public:
	// Print a line of text on Window::console
	void Console_Log(const QString &text);

private slots:
	// 鼠标移动，point是 GraphicsView的坐标,物理坐标
	void do_mouseMovePoint(QPoint point_view,QPointF point_scene)
	{
		labViewCord->setText(QString::asprintf("View 坐标 [%d,%d]", point_view.x(), point_view.y()));
		// QPointF pointScene = ui.view->mapToScene(point); // 转换到Scene坐标
		labSceneCord->setText(QString::asprintf("Scene 坐标 [%.0f,%.0f]", point_scene.x(), point_scene.y()));
	}
	// // 鼠标单击
	// void do_mouseClicked(QPoint point)
	// {
	// 	QPointF pointScene = ui.view->mapToScene(point); // 转换到Scene坐标
	// 	QGraphicsItem *item = NULL;
	// 	item = scene->itemAt(pointScene, ui.view->transform()); // 获取光标下的绘图项
	// 	if (item != NULL)										// 有绘图项
	// 	{
	// 		QPointF pointItem = item->mapFromScene(pointScene); // 转换为绘图项的局部坐标
	// 		// labItemCord->setText(QString::asprintf("Item 坐标：%.0f,%.0f", pointItem.x(), pointItem.y()));
	// 	}
	// }


};
