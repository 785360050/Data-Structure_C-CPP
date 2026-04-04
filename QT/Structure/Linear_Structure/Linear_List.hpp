#pragma once

#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QLabel>
#include <QTextBrowser>
#include <QTimer>

#include "../Structure.hpp"

#include <QPushButton>
#include <QLineEdit>

#include <vector>


#include "../Painter/Painter.hpp"

#include "../../Data_Sturcture/C++/Linear_Structure/Linear_List/Sequential_List/Sequential_List.hpp"

using DataType = int;
static const int capcity=10;

namespace Trace
{
	struct Linear_List_Slot
	{
		bool occupied{};
		DataType value{};
	};

	struct Linear_List_Frame
	{
		QString title;
		QString adt_message;
		QString impl_message;
		std::vector<Linear_List_Slot> slot_states;
		std::vector<int> highlight_indices;
	};

	// The builder derives frames from the public list semantics instead of
	// instrumenting the container internals, which keeps the MVP low-invasive.
	class Sequential_List_Static_TraceBuilder
	{
	public:
		static std::vector<Linear_List_Frame> Build_State(
			const std::vector<Linear_List_Slot>& slot_states,
			const QString& title,
			const QString& adt_message,
			const QString& impl_message);

		static std::vector<Linear_List_Frame> Build_Insert(
			const std::vector<Linear_List_Slot>& before,
			int size,
			int capacity,
			int position,
			DataType value);

		static std::vector<Linear_List_Frame> Build_Delete(
			const std::vector<Linear_List_Slot>& before,
			int size,
			int position);
	};
}

namespace Painter
{
	// Wrapper of Datastructure & QT
	// template<typename DataType>
	class Linear_List : public Painter
	{
		Sequential_List_Static<DataType,10> list;
		std::vector<Trace::Linear_List_Frame> trace_frames;
		int current_frame_index{};

	public:
		Linear_List();

	protected:
		void Draw_Element(
			QPainter* painter,
			const QPoint& pos,
			int index,
			const Trace::Linear_List_Slot& slot,
			bool highlighted) const;
		void Update_Area_Size();
		void Show_Current_State(
			const QString& title,
			const QString& adt_message,
			const QString& impl_message);
		std::vector<Trace::Linear_List_Slot> Capture_Slots();
		void Set_Trace_Frames(std::vector<Trace::Linear_List_Frame>&& frames);

	public:
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
	public: // Interactions
		bool Is_Empty() { return list.Is_Empty();}
		int Get_Size() { return list.Get_Size();}
		void Clear();
		// 在index位置插入element
		void Element_Insert(int index,const DataType& element);
		// 删除index位置的元素
		void Element_Delete(int index);
		// 获取index位置的元素
		DataType operator[](int index){return list[index];}
		// 设置index位置的元素为element
		void Element_Update(int index,DataType&&  element){list.Element_Update(index,std::forward<DataType>(element));};

		bool Move_To_Next_Frame();
		bool Move_To_Previous_Frame();
		void Reset_Trace_Playback();
		int Get_Current_Frame_Index() const;
		int Get_Total_Frame_Count() const;
		const Trace::Linear_List_Frame& Get_Current_Frame() const;
	};
}


namespace View
{
	class Linear_List : public Structure
	{
		Painter::Linear_List painter;
		QTimer playback_timer;

	protected:
		void Config_Operations() override;
		void Config_Monitor();
		void Refresh_Trace_Monitor();
		void Refresh_Trace_View();

	public:
		Linear_List()
		{
			Hook_Painter(&painter);
			Config_Operations();
			Config_Monitor();
			Refresh_Trace_Monitor();
			Refresh_View(painter.boundingRect().size());
		}

	public: // interactions
		QPushButton *button_insert{new QPushButton("Insert")};
		QLineEdit *input_insert_element{new QLineEdit};
		QLineEdit *input_insert_pos{new QLineEdit};
		QPushButton *button_delete{new QPushButton("Delete")};
		QLineEdit *input_delete_pos{new QLineEdit};
		QPushButton *button_index{new QPushButton("Index")};
		QLineEdit *input_index{new QLineEdit};
		QPushButton *button_get_size{new QPushButton("Get Size")};
		QPushButton *button_is_empty{new QPushButton("Is Empty?")};
		QPushButton *button_clear{new QPushButton("Clear")};
		QPushButton *button_trace_prev{new QPushButton("Prev Frame")};
		QPushButton *button_trace_next{new QPushButton("Next Frame")};
		QPushButton *button_trace_play{new QPushButton("Play")};
		QPushButton *button_trace_reset{new QPushButton("Reset")};
		QLabel *label_trace_status{new QLabel};
		QTextBrowser *browser_trace{new QTextBrowser};
		void Is_Empty();
		void Get_Size();
		void Clear();
		// 在index位置插入element
		void Element_Insert();
		// 删除index位置的元素
		void Element_Delete();
		// 获取index位置的元素
		void Element_Get();
		// 设置index位置的元素为element
		void Element_Update();
		void Handle_Trace_Previous();
		void Handle_Trace_Next();
		void Handle_Trace_Play();
		void Handle_Trace_Reset();
	};
}
