#include "Window.hpp"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	// Window::Instance().show();
	Window window;
	window.show();
	return a.exec();
}
