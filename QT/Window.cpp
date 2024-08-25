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


	{//Register_Factory
		Register_Factory<Factory::Stack>("Stack");
		Register_Factory<Factory::Queue>("Queue");
		Register_Factory<Factory::Skip_List>("Skip_List");
		Register_Factory<Factory::Search_Tree>("Search_Tree");
		Register_Factory<Factory::AVL_Tree>("AVL_Tree");
		Register_Factory<Factory::Tree_Binary_Search_RBT>("Red_Black_Tree");
		Register_Factory<Factory::Heap>("Heap");

		Register_Factory<Factory::Tree>("Tree");
		Register_Factory<Factory::Binary_Tree>("Binary_Tree");
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


void Window::Handle_Select_Structure(QTreeWidgetItem *item,int column)
{
	auto selected_structure_name = item->text(0);

	ui.console->append(selected_structure_name); // auto enter
	ui.label_selected->setText(selected_structure_name);

	std::string logic_structure_name{selected_structure_name.toStdString()};
	if(factory.contains(logic_structure_name))
	{
		auto structure=factory[logic_structure_name]->Produce();
		// qDebug()<<structure;
		structure->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
		int current_tab_index=ui.tabWidget->addTab(structure,QString::fromStdString(logic_structure_name));
		ui.tabWidget->setCurrentIndex(current_tab_index);
	}
	else
		QMessageBox::information(this,{},QString("%1 Not Implemented Yet").arg(QString::fromStdString(logic_structure_name)));



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








