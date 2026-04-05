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
#include "../../Data_Sturcture/C++/Trace/Linear_List_Trace.hpp"

using DataType = int;
static const int capcity=10;

namespace Painter
{
	// Wrapper of Datastructure & QT
	// template<typename DataType>
	class Linear_List : public Painter
	{
		Trace::Recorder<DataType> trace_recorder;
		Sequential_List_Static<DataType,10> list;
		std::vector<Trace::Linear_List_Frame<DataType>> trace_frames;
		int current_frame_index{};

	public:
		Linear_List();

	protected:
		void Draw_Element(QPainter* painter, const QPoint& pos, int index, const Trace::Linear_List_Slot<DataType>& slot, bool highlighted) const;
		void Update_Area_Size();
		Trace::Linear_List_Snapshot<DataType> Capture_Snapshot();
		void Record_Current_State(const std::string& title, const std::string& adt_message, const std::string& impl_message);
		void Record_Insert_Trace(int index, const DataType& element);
		void Record_Delete_Trace(int index);
		void Record_Clear_Trace();
		void Sync_Trace_Frames();

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
		const Trace::Linear_List_Frame<DataType>& Get_Current_Frame() const;
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
