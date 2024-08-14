#pragma once

#include "./ui_Window.h"

#include <QtWidgets/QMainWindow>
#include <QLabel>

#include <vector>

#include "Painter/Painter.hpp"
// #include "Painter/Stack.hpp"
// #include "Painter/Binary_Tree.hpp"


enum Logic_Structure
{
	Linear_List=0,
	Stack_,
	Queue,
	Skip_List,

};


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


	// Stack* stack_view{new Stack};
	// Binary_Tree* tree_view{new Binary_Tree};
	// std::vector<Painter*> painters;

	// std::variant<int,float> current_page;//Store Page Classes, and only show one in a time
private:
	Window(QWidget *parent = nullptr);
	~Window();
public: // 单例阻止拷贝构造和拷贝赋值
	Window(const Window &) = delete;
	Window &operator= (const Window &) = delete;

	void do_changeTabTitle(QString title)
	{
		int index=ui.tabWidget->currentIndex();
		ui.tabWidget->setTabText(index,title);
	}
public:
	static Window &Instance()
	{ // 局部静态变量，线程安全
		static Window instance;
		return instance;
	};

public:
	// Print a line of text on Window::console
	void Console_Log(const QString &text);

	// void Draw_Items_On_Scene();

// public: // interactions
// 	void Element_Push();
// 	void Element_Pop();
// 	void Element_Get_Top();
// 	void Is_Empty();
// 	void Get_Size();
// 	void Clear()   ;
};
