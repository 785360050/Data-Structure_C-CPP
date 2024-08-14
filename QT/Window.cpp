#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDialog>

#include "Window.hpp"

#include "View/Stack.hpp"

#include "QT_Stream_Buffer.hpp"
static std::shared_ptr<QT_Stream_Buffer> buffer;



Window::Window(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	{// Config Status Bar
		// 状态栏设计
		labViewCord = new QLabel("View 坐标：", this);
		labViewCord->setMinimumWidth(150);
		ui.statusbar->addWidget(labViewCord);

		labSceneCord = new QLabel("Scene 坐标：", this);
		labSceneCord->setMinimumWidth(150);
		ui.statusbar->addWidget(labSceneCord);

		labItemCord = new QLabel("Item 坐标：", this);
		labItemCord->setMinimumWidth(150);
		ui.statusbar->addWidget(labItemCord);

	}

	{ // Config Tree Widget
		ui.treeWidget->expandAll();
		// ui.treeWidget->collapseAll();

		// auto select = [&](QTreeWidgetItem *current, QTreeWidgetItem *previous)
		auto select = [&](QTreeWidgetItem *item,int column)
		{
			// auto selected_structure_name = current->text(0);
			auto selected_structure_name = item->text(0);

			ui.console->append(selected_structure_name); // auto enter
			ui.label_selected->setText(selected_structure_name);

			if(item->text(0).toStdString()=="Stack")
			{
				Stack* stack=new Stack();
				stack->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
				int cur=ui.tabWidget->addTab(stack,
											  QString::asprintf("Table %d",ui.tabWidget->count()));
				ui.tabWidget->setCurrentIndex(cur);
				ui.tabWidget->setVisible(true);

			}
		};
		// connect(ui.treeWidget,&QTreeWidget::itemSelectionChanged,this,select);
		// connect(ui.treeWidget, &QTreeWidget::currentItemChanged, this, select);
		connect(ui.treeWidget, &QTreeWidget::itemDoubleClicked, this, select);
	}

	// Draw_Items_On_Scene();

	{ // Config Console
		connect(ui.button_clear_console, &QPushButton::clicked, this, [&](){ ui.console->clear(); });

		// redirect std::cout > ui.textBrowser
		buffer = std::make_shared<QT_Stream_Buffer>(this);
		new (&std::cout) std::ostream(buffer.get()); // placement new

		std::cout << "test std::cout";
		// qDebug()<<"qDebug";
	}

	ui.tabWidget->tabBar()->setDocumentMode(true); // tab zi dong shi ying kuan du
	connect(ui.button_redo, &QPushButton::clicked, this, [&](){ std::cout << "button cout"; });

	// {// init interact buttons
	// 	// Stack
	// 	connect(ui.button_push,&QPushButton::clicked,this,&Window::Element_Push);
	// 	connect(ui.button_pop,&QPushButton::clicked,this,&Window::Element_Pop);
	// 	connect(ui.button_get_top,&QPushButton::clicked,this,&Window::Element_Get_Top);
	// 	connect(ui.button_get_size,&QPushButton::clicked,this,&Window::Get_Size);
	// 	connect(ui.button_is_empty,&QPushButton::clicked,this,&Window::Is_Empty);
	// 	connect(ui.button_clear,&QPushButton::clicked,this,&Window::Clear);
	// }

	// auto Export_Picture=[&]()
	// {
	// 	auto pixmap=ui.view->grab();
	// 	QDialog *dialog=new QDialog;

	// 	dialog->setWindowTitle("图片展示");

	// 	QHBoxLayout *layout=new QHBoxLayout;
	// 	QLabel *label=new QLabel;
	// 	label->resize(800,480);
	// 	pixmap=pixmap.scaled(label->width(),label->height());
	// 	label->setPixmap(pixmap);
	// 	layout->addWidget(label);

	// 	dialog->setLayout(layout);
	// 	dialog->show();
	// 	dialog->exec();

	// 	delete dialog;
	// };
	// connect(ui.button_export, &QPushButton::clicked, this, Export_Picture);

}

Window::~Window()
{
}

void Window::Console_Log(const QString& text)
{
	// static QString textbuf;
	// textbuf += text;
	// ui.console->append(textbuf);
	// ui.console->setCursor(QCursor::setPos())

	// ui.console->insertPlainText(text); // no \n
	ui.console->append(text);
}






// void Window::Draw_Items_On_Scene()
// {
// 	// scene->addItem(stack_view);
// 	// scene->addItem(tree_view);


// 	Stack* stack_view{new Stack};
// 	Binary_Tree* tree_view{new Binary_Tree};
// 	painters.push_back(stack_view);
// 	painters.push_back(tree_view);
// 	// Switch_Display();

// 	for(Painter* painter:painters)
// 		scene->addItem(painter);
// }



// #include <QMessageBox>
// void Window::Element_Push()
// {
// 	auto stack_view=dynamic_cast<Stack*>(painters[0]);
// 	int element{ui.input_push->text().toInt()};

// 	try
// 	{
// 		stack_view->Element_Push(element);
// 		std::cout<<"Push: "+std::to_string(element);
// 		ui.view->viewport()->update();
// 	}
// 	catch(const std::exception& e)
// 	{
// 		QMessageBox::critical(this,{},e.what());
// 	}
// }
// void Window::Element_Pop()
// {
// 	auto stack_view=dynamic_cast<Stack*>(painters[0]);
// 	try
// 	{
// 		stack_view->Element_Pop();
// 		std::cout<<"Pop";
// 		ui.view->viewport()->update();
// 	}
// 	catch(const std::exception& e)
// 	{
// 		QMessageBox::critical(this,{},e.what());
// 	}
// }
// void Window::Element_Get_Top()
// {
// 	auto stack_view=dynamic_cast<Stack*>(painters[0]);
// 	try
// 	{
// 		auto element=stack_view->Get_Top();
// 		std::cout<<"Top = "+std::to_string(element);
// 	}
// 	catch(const std::exception& e)
// 	{
// 		QMessageBox::critical(this,{},e.what());
// 	}

// }

// void Window::Is_Empty()
// {
// 	auto stack_view=dynamic_cast<Stack*>(painters[0]);
// 	try{std::cout<<"Is Empty ? "<<std::boolalpha<<stack_view->Is_Empty();}
// 	catch(const std::exception& e)
// 	{
// 		QMessageBox::critical(this,{},e.what());
// 	}
// }

// void Window::Get_Size()
// {
// 	auto stack_view=dynamic_cast<Stack*>(painters[0]);
// 	try
// 	{
// 		std::cout<<"Size = "+std::to_string(stack_view->Get_Size());
// 	}
// 	catch(const std::exception& e)
// 	{
// 		QMessageBox::critical(this,{},e.what());
// 	}
// }

// void Window::Clear()
// {
// 	auto stack_view=dynamic_cast<Stack*>(painters[0]);
// 	try
// 	{
// 		stack_view->Clear();
// 		std::cout<<"Clear All Elements";
// 		ui.view->viewport()->update();
// 	}
// 	catch(const std::exception& e)
// 	{
// 		QMessageBox::critical(this,{},e.what());
// 	}
// }
