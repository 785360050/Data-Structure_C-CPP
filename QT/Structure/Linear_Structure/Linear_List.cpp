#include "Linear_List.hpp"

#include <format>
#include <iostream>
#include <algorithm>

namespace
{
	constexpr int kSlotWidth = 72;
	constexpr int kSlotHeight = 56;
	constexpr int kSlotGap = 10;
	constexpr int kTextWidth = 960;
	constexpr int kTextHeight = 32;
	constexpr int kTopMessageY = -165;
	constexpr int kAdtMessageY = -125;
	constexpr int kImplMessageY = -88;
	constexpr int kSlotsY = -10;
}
Painter::Linear_List::Linear_List()
{
	for (int i = 1; i <= 5; ++i)
		list.Element_Insert(i, i);

	trace_recorder.Clear();
	Update_Area_Size();
	Record_Current_State(
		"初始状态",
		"线性表用于按顺序存储逻辑序列。",
		"当前使用固定容量的顺序存储实现。");
}

void Painter::Linear_List::Draw_Element(QPainter* painter, const QPoint& pos, int index, const Trace::Linear_List_Slot<DataType>& slot, bool highlighted) const
{
	QRect rect(pos.x(), pos.y(), kSlotWidth, kSlotHeight);

	QColor fill = slot.occupied ? QColor(31, 53, 78) : QColor(48, 48, 48);
	QPen pen(slot.occupied ? Qt::white : Qt::gray, 2);
	if (highlighted)
	{
		fill = QColor(176, 95, 25);
		pen = QPen(QColor(255, 220, 160), 3);
	}

	painter->save();
	painter->setBrush(fill);
	painter->setPen(pen);
	painter->drawRect(rect);

	if (slot.occupied)
		painter->drawText(rect, Qt::AlignCenter, QString::number(slot.value));

	painter->setPen(QPen(Qt::gray, 2));
	painter->drawText(
		QRect(pos.x(), pos.y() + kSlotHeight + 6, kSlotWidth, 24),
		Qt::AlignCenter,
		QString::number(index));
	painter->restore();
}

void Painter::Linear_List::Update_Area_Size()
{
	const int width = capcity * kSlotWidth + (capcity - 1) * kSlotGap + 80;
	const int height = 280;
	this->area.setRect(-width / 2, -height / 2, width, height);
}

Trace::Linear_List_Snapshot<DataType> Painter::Linear_List::Capture_Snapshot()
{
	Trace::Linear_List_Snapshot<DataType> snapshot(capcity);
	const int size = list.Get_Size();
	for (int index = 0; index < capcity; ++index)
	{
		if (index < size)
			snapshot[index] = {true, list[index + 1]};
		else
			snapshot[index] = {};
	}
	return snapshot;
}

void Painter::Linear_List::Sync_Trace_Frames()
{
	trace_frames = trace_recorder.Get_Frames();
	current_frame_index = 0;
}

void Painter::Linear_List::Record_Current_State(
	const std::string& title, const std::string& adt_message, const std::string& impl_message)
{
	trace_recorder.Clear();
	Trace::Push_Debug_Frame(trace_recorder, title, adt_message, impl_message, Capture_Snapshot());
	Sync_Trace_Frames();
}

void Painter::Linear_List::Record_Insert_Trace(int index, const DataType& element)
{
	trace_recorder.Clear();
	Trace::Push_Insert_Begin(trace_recorder, Capture_Snapshot(), index, element);

	const int size = list.Get_Size();
	auto snapshot = Capture_Snapshot();
	for (int current = size; current >= index; --current)
	{
		snapshot[current] = snapshot[current - 1];
		Trace::Push_Shift_Right(trace_recorder, snapshot, current, current + 1);
	}

	snapshot[index - 1] = {true, element};
	Trace::Push_Insert_Write(trace_recorder, snapshot, index);
	Trace::Push_Insert_End(trace_recorder, snapshot);
}

void Painter::Linear_List::Record_Delete_Trace(int index)
{
	trace_recorder.Clear();
	Trace::Push_Delete_Begin(trace_recorder, Capture_Snapshot(), index);

	const int size = list.Get_Size();
	auto snapshot = Capture_Snapshot();
	for (int current = index; current < size; ++current)
	{
		snapshot[current - 1] = snapshot[current];
		Trace::Push_Shift_Left(trace_recorder, snapshot, current + 1, current);
	}

	snapshot[size - 1] = {};
	Trace::Push_Debug_Frame(
		trace_recorder,
		"尾槽清理后",
		"删除操作后，末尾旧槽位已被清空。",
		std::format("末尾槽位 {} 已清理。", size),
		snapshot,
		{static_cast<size_t>(size)});
	Trace::Push_Delete_End(trace_recorder, snapshot);
}

void Painter::Linear_List::Record_Clear_Trace()
{
	trace_recorder.Clear();
	Trace::Push_Clear(trace_recorder, Capture_Snapshot());
}

void Painter::Linear_List::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setPen(QPen(Qt::white, 2));

	QFont title_font{"Cascadia Code", 16, QFont::Bold};
	QFont body_font{"Cascadia Code", 12};

	const auto& frame = Get_Current_Frame();
	const int total_width = capcity * kSlotWidth + (capcity - 1) * kSlotGap;
	const int start_x = -total_width / 2;

	painter->setFont(title_font);
	painter->drawText(
		QRect(-kTextWidth / 2, kTopMessageY, kTextWidth, kTextHeight),
		Qt::AlignCenter,
		QString::fromStdString(frame.title));

	painter->setFont(body_font);
	painter->drawText(
		QRect(-kTextWidth / 2, kAdtMessageY, kTextWidth, kTextHeight),
		Qt::AlignCenter,
		QString::fromStdString(frame.adt_message));
	painter->drawText(
		QRect(-kTextWidth / 2, kImplMessageY, kTextWidth, kTextHeight * 2),
		Qt::AlignCenter | Qt::TextWordWrap,
		QString::fromStdString(frame.impl_message));

	for (int slot_index = 0; slot_index < capcity; ++slot_index)
	{
		const bool highlighted = std::find(
			frame.highlight_positions.begin(),
			frame.highlight_positions.end(),
			static_cast<size_t>(slot_index + 1)) != frame.highlight_positions.end();

		QPoint pos{
			start_x + slot_index * (kSlotWidth + kSlotGap),
			kSlotsY
		};
		Draw_Element(painter, pos, slot_index + 1, frame.slot_states[slot_index], highlighted);
	}
}

void Painter::Linear_List::Clear()
{
	list.List_Clear();
	Record_Clear_Trace();
	Sync_Trace_Frames();
}

void Painter::Linear_List::Element_Insert(int index, const DataType& element)
{
	Record_Insert_Trace(index, element);
	list.Element_Insert(index, element);
	Sync_Trace_Frames();
}

void Painter::Linear_List::Element_Delete(int index)
{
	Record_Delete_Trace(index);
	list.Element_Delete(index);
	Sync_Trace_Frames();
}

bool Painter::Linear_List::Move_To_Next_Frame()
{
	if (current_frame_index + 1 >= static_cast<int>(trace_frames.size()))
		return false;
	++current_frame_index;
	return true;
}

bool Painter::Linear_List::Move_To_Previous_Frame()
{
	if (current_frame_index == 0)
		return false;
	--current_frame_index;
	return true;
}

void Painter::Linear_List::Reset_Trace_Playback()
{
	current_frame_index = 0;
}

int Painter::Linear_List::Get_Current_Frame_Index() const
{
	return current_frame_index;
}

int Painter::Linear_List::Get_Total_Frame_Count() const
{
	return static_cast<int>(trace_frames.size());
}

const Trace::Linear_List_Frame<DataType>& Painter::Linear_List::Get_Current_Frame() const
{
	return trace_frames.at(current_frame_index);
}

void View::Linear_List::Config_Operations()
{
	QHBoxLayout* line_insert=new QHBoxLayout;
	line_insert->addWidget(button_insert);
	line_insert->addWidget(input_insert_element);
	line_insert->addWidget(input_insert_pos);
	input_insert_element->setPlaceholderText("element");
	input_insert_pos->setPlaceholderText("position");

	QHBoxLayout* line_delete=new QHBoxLayout;
	line_delete->addWidget(button_delete);
	line_delete->addWidget(input_delete_pos);
	input_delete_pos->setPlaceholderText("position");

	QHBoxLayout* line_index=new QHBoxLayout;
	line_index->addWidget(button_index);
	line_index->addWidget(input_index);
	input_index->setPlaceholderText("index");

	QVBoxLayout* layout=new QVBoxLayout;
	layout->addLayout(line_insert);
	layout->addLayout(line_delete);
	layout->addLayout(line_index);
	layout->addWidget(button_get_size);
	layout->addWidget(button_is_empty);
	layout->addWidget(button_clear);

	ui.tab_operations->setLayout(layout);

	connect(button_insert,&QPushButton::clicked,this,&Linear_List::Element_Insert);
	connect(button_delete,&QPushButton::clicked,this,&Linear_List::Element_Delete);
	connect(button_index,&QPushButton::clicked,this,&Linear_List::Element_Get);
	connect(button_get_size,&QPushButton::clicked,this,&Linear_List::Get_Size);
	connect(button_is_empty,&QPushButton::clicked,this,&Linear_List::Is_Empty);
	connect(button_clear,&QPushButton::clicked,this,&Linear_List::Clear);
}

void View::Linear_List::Config_Monitor()
{
	auto* line_controls = new QHBoxLayout;
	line_controls->addWidget(button_trace_prev);
	line_controls->addWidget(button_trace_next);
	line_controls->addWidget(button_trace_play);
	line_controls->addWidget(button_trace_reset);

	label_trace_status->setWordWrap(true);
	browser_trace->setReadOnly(true);

	auto* layout = new QVBoxLayout;
	layout->addLayout(line_controls);
	layout->addWidget(label_trace_status);
	layout->addWidget(browser_trace);
	ui.tab_monitor->setLayout(layout);

	playback_timer.setInterval(700);
	connect(&playback_timer, &QTimer::timeout, this, [this]()
	{
		if (!painter.Move_To_Next_Frame())
		{
			playback_timer.stop();
			button_trace_play->setText("Play");
		}
		Refresh_Trace_View();
	});

	connect(button_trace_prev, &QPushButton::clicked, this, &Linear_List::Handle_Trace_Previous);
	connect(button_trace_next, &QPushButton::clicked, this, &Linear_List::Handle_Trace_Next);
	connect(button_trace_play, &QPushButton::clicked, this, &Linear_List::Handle_Trace_Play);
	connect(button_trace_reset, &QPushButton::clicked, this, &Linear_List::Handle_Trace_Reset);
}

void View::Linear_List::Refresh_Trace_Monitor()
{
	const auto& frame = painter.Get_Current_Frame();
	label_trace_status->setText(QString("Frame %1 / %2")
		.arg(painter.Get_Current_Frame_Index() + 1)
		.arg(painter.Get_Total_Frame_Count()));

	browser_trace->setText(QString(
		"<b>%1</b><br/><br/>"
		"<b>ADT</b><br/>%2<br/><br/>"
		"<b>Implementation</b><br/>%3")
		.arg(QString::fromStdString(frame.title),
			QString::fromStdString(frame.adt_message),
			QString::fromStdString(frame.impl_message)));
}

void View::Linear_List::Refresh_Trace_View()
{
	Refresh_Trace_Monitor();
	Refresh_View(painter.boundingRect().size());
}

void View::Linear_List::Is_Empty()
{
	try
	{
		bool result=painter.Is_Empty();
		std::cout<<"Is Empty?";
		std::cout<<std::boolalpha<<result;
		Refresh_View(painter.boundingRect().size());
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}



void View::Linear_List::Element_Insert()
{
	int element{input_insert_element->text().toInt()};
	int position{input_insert_pos->text().toInt()};

	try
	{
		painter.Element_Insert(position,element);
		button_trace_play->setText("Pause");
		playback_timer.start();
		Refresh_Trace_View();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
void View::Linear_List::Element_Delete()
{
	int index{input_delete_pos->text().toInt()};
	try
	{
		painter.Element_Delete(index);
		button_trace_play->setText("Pause");
		playback_timer.start();
		Refresh_Trace_View();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}
void View::Linear_List::Element_Get()
{
	int index{input_index->text().toInt()};
	try
	{
		auto element=painter[index];
		std::cout<<"Top = "+std::to_string(element);
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}

}

void View::Linear_List::Element_Update()
{
	try{std::cout<<"Is Empty ? "<<std::boolalpha<<painter.Is_Empty();}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}

void View::Linear_List::Get_Size()
{
	try
	{
		std::cout<<"Size = "+std::to_string(painter.Get_Size());
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}

void View::Linear_List::Clear()
{
	try
	{
		playback_timer.stop();
		button_trace_play->setText("Play");
		painter.Clear();
		std::cout<<"Clear All Elements";
		Refresh_Trace_View();
	}
	catch(const std::exception& e)
	{
		QMessageBox::critical(this,{},e.what());
	}
}

void View::Linear_List::Handle_Trace_Previous()
{
	playback_timer.stop();
	button_trace_play->setText("Play");
	painter.Move_To_Previous_Frame();
	Refresh_Trace_View();
}

void View::Linear_List::Handle_Trace_Next()
{
	playback_timer.stop();
	button_trace_play->setText("Play");
	painter.Move_To_Next_Frame();
	Refresh_Trace_View();
}

void View::Linear_List::Handle_Trace_Play()
{
	if (playback_timer.isActive())
	{
		playback_timer.stop();
		button_trace_play->setText("Play");
		return;
	}

	if (painter.Get_Current_Frame_Index() + 1 >= painter.Get_Total_Frame_Count())
		painter.Reset_Trace_Playback();

	playback_timer.start();
	button_trace_play->setText("Pause");
	Refresh_Trace_View();
}

void View::Linear_List::Handle_Trace_Reset()
{
	playback_timer.stop();
	button_trace_play->setText("Play");
	painter.Reset_Trace_Playback();
	Refresh_Trace_View();
}
