#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDialog>

#include "Window.hpp"



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

		// connect(ui.treeWidget,&QTreeWidget::itemSelectionChanged,this,select);
		// connect(ui.treeWidget, &QTreeWidget::currentItemChanged, this, select);
		connect(ui.treeWidget, &QTreeWidget::itemDoubleClicked, this, &Window::Handle_Select_Structure);

		// ui.tabWidget->setTabsClosable(true);
		ui.tabWidget->setTabVisible(0,false);
		auto Close_Tab=[&](int index)
		{
			if (index<0)
				return;
			ui.tabWidget->widget(index)->close();
		};
		connect(ui.tabWidget, &QTabWidget::tabCloseRequested, this, Close_Tab);
	}

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

	connect(ui.button_export, &QPushButton::clicked, this, &Window::Handle_Export_Picture);

}

// #include "View/Stack.hpp"
#include "Structure/Linear_Structure/Stack.hpp"
#include "Structure/Linear_Structure/Queue.hpp"
#include "Demo/View_Binary_Tree.hpp"
#include "Structure/Linear_Structure/Skip_List.hpp"
// #include "View/Tree.hpp"
#include "Demo/View_Tree.hpp"
#include "Structure/Tree_Structure/Search_Tree.hpp"
#include "Structure/Tree_Structure/AVL_Tree.hpp"
#include "Structure/Tree_Structure/Red_Black_Tree.hpp"
#include "Structure/Tree_Structure/Heap.hpp"
void Window::Handle_Select_Structure(QTreeWidgetItem *item,int column)
{
	// auto selected_structure_name = current->text(0);
	auto selected_structure_name = item->text(0);

	ui.console->append(selected_structure_name); // auto enter
	ui.label_selected->setText(selected_structure_name);
	std::string logic_structure_name{item->text(0).toStdString()};

	static auto Create_View=[&](Structure* structure,const std::string& name)
	{
		structure->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
		int current_tab_index=ui.tabWidget->addTab(structure,QString::fromStdString(name));
		ui.tabWidget->setCurrentIndex(current_tab_index);
	};

	if(logic_structure_name=="Stack")
		Create_View(new View::Stack,"Stack");
	else if(logic_structure_name=="Queue")
		Create_View(new View::Queue,"Queue");
	else if(logic_structure_name=="Binary_Tree")
		Create_View(new View::Binary_Tree,"Binary_Tree");
	else if(logic_structure_name=="Skip_List")
		Create_View(new View::Skip_List,"Skip_List");
	else if(logic_structure_name=="Tree")
		Create_View(new View::Tree<int,2>,"Tree");
	else if(logic_structure_name=="Search_Tree")
		Create_View(new View::Search_Tree,"Search_Tree");
	else if(logic_structure_name=="AVL_Tree")
		Create_View(new View::AVL_Tree,"AVL_Tree");
	else if(logic_structure_name=="Red_Black_Tree")
		Create_View(new View::Tree_Binary_Search_RBT,"Red_Black_Tree");
	else if(logic_structure_name=="Heap")
		Create_View(new View::Heap,"Heap");
}

void Window::Handle_Export_Picture()
{
	// auto pixmap=ui.view->grab();
	Structure* current=dynamic_cast<Structure*>(ui.tabWidget->currentWidget());
	auto pixmap=current->Grab_Picture();
	QDialog *dialog=new QDialog;

	dialog->setWindowTitle("图片展示");

	QHBoxLayout *layout=new QHBoxLayout;
	QLabel *label=new QLabel;
	label->resize(pixmap.size());
	pixmap=pixmap.scaled(label->width(),label->height());
	label->setPixmap(pixmap);
	layout->addWidget(label);

	dialog->setLayout(layout);
	dialog->show();
	dialog->exec();

	delete dialog;
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

Window::~Window()
{
}







