#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDialog>

#include "Window.hpp"

#include "View/Stack.hpp"
#include "View/Binary_Tree.hpp"
#include "View/Skip_List.hpp"
#include "View/Tree.hpp"

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
				int cur=ui.tabWidget->addTab(stack,QString::asprintf("Table %d",ui.tabWidget->count()));
				ui.tabWidget->setCurrentIndex(cur);
			}
			else if(item->text(0).toStdString()=="Binary_Tree")
			{
				Binary_Tree* tree=new Binary_Tree;
				tree->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
				int cur=ui.tabWidget->addTab(tree,QString::asprintf("Table %d",ui.tabWidget->count()));
				ui.tabWidget->setCurrentIndex(cur);
			}
			else if(item->text(0).toStdString()=="Skip List")
			{
				class Skip_List* skip_list=new class Skip_List; // ?????
				skip_list->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
				int cur=ui.tabWidget->addTab(skip_list,QString::asprintf("Table %d",ui.tabWidget->count()));
				ui.tabWidget->setCurrentIndex(cur);
			}
			else if(item->text(0).toStdString()=="Tree")
			{
				View::Tree* tree=new View::Tree;
				tree->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
				int cur=ui.tabWidget->addTab(tree,QString::asprintf("Table %d",ui.tabWidget->count()));
				ui.tabWidget->setCurrentIndex(cur);
			}

		};
		// connect(ui.treeWidget,&QTreeWidget::itemSelectionChanged,this,select);
		// connect(ui.treeWidget, &QTreeWidget::currentItemChanged, this, select);
		connect(ui.treeWidget, &QTreeWidget::itemDoubleClicked, this, select);
		auto Close_Tab=[&](int index)
		{
			if (index<0)
				return;
			ui.tabWidget->widget(index)->close();
		};
		// ui.tabWidget->setTabsClosable(true);
		ui.tabWidget->setTabVisible(0,false);
		connect(ui.tabWidget, &QTabWidget::tabCloseRequested, this, Close_Tab);
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







