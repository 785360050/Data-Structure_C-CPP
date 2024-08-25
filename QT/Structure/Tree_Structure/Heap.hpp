#pragma once


#include "../../Painter/Painter.hpp"
#include "../../Painter/Tree.hpp"


#include "../../Data_Sturcture/C++/Tree_Structure/Heap/Binary_Heap.hpp"

namespace Adapter
{
	template <typename DataType>
	struct Node_Heap
	{
		std::string name{"N/A"};
		Node_Heap(DataType element):name{std::to_string(element)}{}
	};

	template <typename DataType, size_t maxsize>
	class Heap:public Binary_Heap<DataType,maxsize>
	{
	public:
		Painter::Tree::Serialized_Container<DataType,2,Adapter::Node_Heap<DataType>> Capture_Snapshot()
		{
			Painter::Tree::Serialized_Container<DataType,2,Adapter::Node_Heap<DataType>> container;
			int current_level=std::floor(std::log2(this->size))+1;
			container.Set_Level(current_level);

			int heap_index{};
			for(int level{1};level<=current_level;++level)
			{
				int level_node_count=std::pow(2,level-1);
				for(int i{0};i<level_node_count;++i)
				{
					container.Set(new Adapter::Node_Heap<DataType>(this->storage[heap_index]),level,i);
					++heap_index;
					if(heap_index>=this->size)
						break;
				}
			}
			return container;
		}

	};
};

namespace Painter
{
	class Heap : public Painter::Painter
	{
		Adapter::Heap<int,10> heap;
		Tree::Serialized_Container<int,2,Adapter::Node_Heap<int>> container;
		Tree::Drawer<int,2,Adapter::Node_Heap<int>> drawer;

	protected:
		// QRectF boundingRect() const override;
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
		{
			drawer.Update_Tree(container);
			drawer.Draw(painter,option,widget);
		}

	public:
		Heap()
		{
			for (int i = 1; i <= 10; ++i)
				heap.Push(i);


			for (int i = 0; i < 5; ++i)
				heap.Pop();

			container=heap.Capture_Snapshot();
			drawer.Update_Tree(container);
		}
		// ~Search_Tree(){};
	public:
		void Element_Push(int element)
		{
			heap.Push(element);
			container=heap.Capture_Snapshot();
			drawer.Update_Tree(container);
		}
		void Element_Pop()
		{
			heap.Pop();
			container=heap.Capture_Snapshot();
			drawer.Update_Tree(container);
		}
		int Get_Top()
		{
			return heap.Get_Top();
		}
	};
}


#include "../Structure.hpp"

#include <QPushButton>
#include <QLineEdit>


namespace View
{
	class Heap : public Structure
	{
		Painter::Heap painter;

	public:
		Heap()
		{
			Hook_Painter(&painter);
			Config_Operations();
		}
		~Heap() {};

	public: // interactions
		QPushButton *button_push{new QPushButton("Push")};
		QLineEdit *input_push{new QLineEdit};
		QPushButton *button_pop{new QPushButton("Pop")};
		QPushButton *button_get_top{new QPushButton("Get Top")};
		QPushButton *button_get_size{new QPushButton("Get Size")};
		QPushButton *button_is_empty{new QPushButton("Is Empty?")};
		QPushButton *button_clear{new QPushButton("Clear")};
		void Config_Operations() override
		{
			QHBoxLayout* line_push=new QHBoxLayout;
			line_push->addWidget(button_push);
			line_push->addWidget(input_push);

			QHBoxLayout* line_delete=new QHBoxLayout;
			line_delete->addWidget(button_pop);

			QVBoxLayout* layout=new QVBoxLayout;
			layout->addLayout(line_push);
			layout->addLayout(line_delete);
			layout->addWidget(button_get_top);
			layout->addWidget(button_is_empty);
			layout->addWidget(button_get_size);
			layout->addWidget(button_clear);

			ui.tab_operations->setLayout(layout);

			connect(button_push,&QPushButton::clicked,this,&Heap::Handle_Element_Push);
			connect(button_pop,&QPushButton::clicked,this,&Heap::Handle_Element_Pop);
			connect(button_get_top,&QPushButton::clicked,this,&Heap::Handle_Get_Top);
			// connect(button_get_size,&QPushButton::clicked,this,&Heap::Get_Size);
			// connect(button_is_empty,&QPushButton::clicked,this,&Heap::Is_Empty);
			// connect(button_clear,&QPushButton::clicked,this,&Heap::Clear);
		}

		void Handle_Element_Push()
		{
			int element = input_push->text().toInt();
			painter.Element_Push(element);
			Refresh_View();
		}
		void Handle_Element_Pop()
		{
			painter.Element_Pop();
			Refresh_View();
		}
		void Handle_Get_Top()
		{

			std::cout <<painter.Get_Top();
		}
	};


}
