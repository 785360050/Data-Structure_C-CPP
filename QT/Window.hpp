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


};
