#include "Linear_List.hpp"

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

std::vector<Trace::Linear_List_Frame> Trace::Sequential_List_Static_TraceBuilder::Build_State(
	const std::vector<Linear_List_Slot>& slot_states,
	const QString& title,
	const QString& adt_message,
	const QString& impl_message)
{
	return {{
		title,
		adt_message,
		impl_message,
		slot_states,
		{}
	}};
}

std::vector<Trace::Linear_List_Frame> Trace::Sequential_List_Static_TraceBuilder::Build_Insert(
	const std::vector<Linear_List_Slot>& before,
	int size,
	int capacity,
	int position,
	DataType value)
{
	if (position < 1 || position > size + 1)
		throw std::out_of_range("List insert failed: Position out of range");
	if (size >= capacity)
		throw std::runtime_error("List insert failed: List is full");

	std::vector<Linear_List_Frame> frames;
	std::vector<Linear_List_Slot> slot_states = before;

	frames.push_back({
		"Before Insert",
		QString("ADT: insert %1 at logical position %2").arg(value).arg(position),
		"Implementation: sequential storage keeps elements in contiguous slots.",
		slot_states,
		{position}
	});

	for (int index = size; index >= position; --index)
	{
		slot_states[index] = slot_states[index - 1];
		frames.push_back({
			"Shift Right",
			QString("ADT: reserve position %1 for the new element").arg(position),
			QString("Implementation: move slot %1 to slot %2").arg(index).arg(index + 1),
			slot_states,
			{index, index + 1}
		});
	}

	slot_states[position - 1] = {true, value};
	frames.push_back({
		"Write New Value",
		QString("ADT: the new logical sequence now contains %1 at position %2").arg(value).arg(position),
		QString("Implementation: write %1 into slot %2").arg(value).arg(position),
		slot_states,
		{position}
	});

	frames.push_back({
		"After Insert",
		QString("ADT: insert completed, size becomes %1").arg(size + 1),
		"Implementation: all occupied slots remain contiguous after the write.",
		slot_states,
		{}
	});

	return frames;
}

std::vector<Trace::Linear_List_Frame> Trace::Sequential_List_Static_TraceBuilder::Build_Delete(
	const std::vector<Linear_List_Slot>& before,
	int size,
	int position)
{
	if (position < 1 || position > size)
		throw std::out_of_range("Position is out of range");

	std::vector<Linear_List_Frame> frames;
	std::vector<Linear_List_Slot> slot_states = before;

	frames.push_back({
		"Before Delete",
		QString("ADT: delete the element at logical position %1").arg(position),
		"Implementation: the removed slot will be filled by later elements.",
		slot_states,
		{position}
	});

	for (int index = position; index < size; ++index)
	{
		slot_states[index - 1] = slot_states[index];
		frames.push_back({
			"Shift Left",
			QString("ADT: keep the remaining logical order unchanged after removing position %1").arg(position),
			QString("Implementation: move slot %1 to slot %2").arg(index + 1).arg(index),
			slot_states,
			{index, index + 1}
		});
	}

	slot_states[size - 1] = {};
	frames.push_back({
		"Clear Tail Slot",
		QString("ADT: size decreases to %1").arg(size - 1),
		QString("Implementation: clear the old tail slot %1").arg(size),
		slot_states,
		{size}
	});

	frames.push_back({
		"After Delete",
		QString("ADT: delete completed, size becomes %1").arg(size - 1),
		"Implementation: occupied elements remain packed from left to right.",
		slot_states,
		{}
	});

	return frames;
}

Painter::Linear_List::Linear_List()
{
	for (int i = 1; i <= 5; ++i)
		list.Element_Insert(i, i);

	Update_Area_Size();
	Show_Current_State(
		"Initial State",
		"ADT: a linear list stores an ordered logical sequence.",
		"Implementation: Sequential_List_Static uses a fixed-capacity contiguous array.");
}

void Painter::Linear_List::Draw_Element(
	QPainter* painter,
	const QPoint& pos,
	int index,
	const Trace::Linear_List_Slot& slot,
	bool highlighted) const
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

std::vector<Trace::Linear_List_Slot> Painter::Linear_List::Capture_Slots()
{
	std::vector<Trace::Linear_List_Slot> slot_states(capcity);
	const int size = list.Get_Size();
	for (int index = 0; index < capcity; ++index)
	{
		if (index < size)
			slot_states[index] = {true, list[index + 1]};
		else
			slot_states[index] = {};
	}
	return slot_states;
}

void Painter::Linear_List::Set_Trace_Frames(std::vector<Trace::Linear_List_Frame>&& frames)
{
	trace_frames = std::move(frames);
	current_frame_index = 0;
}

void Painter::Linear_List::Show_Current_State(
	const QString& title,
	const QString& adt_message,
	const QString& impl_message)
{
	Set_Trace_Frames(Trace::Sequential_List_Static_TraceBuilder::Build_State(
		Capture_Slots(),
		title,
		adt_message,
		impl_message));
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
		frame.title);

	painter->setFont(body_font);
	painter->drawText(
		QRect(-kTextWidth / 2, kAdtMessageY, kTextWidth, kTextHeight),
		Qt::AlignCenter,
		frame.adt_message);
	painter->drawText(
		QRect(-kTextWidth / 2, kImplMessageY, kTextWidth, kTextHeight * 2),
		Qt::AlignCenter | Qt::TextWordWrap,
		frame.impl_message);

	for (int slot_index = 0; slot_index < capcity; ++slot_index)
	{
		const bool highlighted = std::find(
			frame.highlight_indices.begin(),
			frame.highlight_indices.end(),
			slot_index + 1) != frame.highlight_indices.end();

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
	Show_Current_State(
		"After Clear",
		"ADT: clear resets the linear list to an empty logical sequence.",
		"Implementation: all occupied slots are reset and the size becomes 0.");
}

void Painter::Linear_List::Element_Insert(int index, const DataType& element)
{
	auto frames = Trace::Sequential_List_Static_TraceBuilder::Build_Insert(
		Capture_Slots(),
		list.Get_Size(),
		capcity,
		index,
		element);

	list.Element_Insert(index, element);
	frames.back().slot_states = Capture_Slots();
	Set_Trace_Frames(std::move(frames));
}

void Painter::Linear_List::Element_Delete(int index)
{
	auto frames = Trace::Sequential_List_Static_TraceBuilder::Build_Delete(
		Capture_Slots(),
		list.Get_Size(),
		index);

	list.Element_Delete(index);
	frames.back().slot_states = Capture_Slots();
	Set_Trace_Frames(std::move(frames));
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

const Trace::Linear_List_Frame& Painter::Linear_List::Get_Current_Frame() const
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
		.arg(frame.title, frame.adt_message, frame.impl_message));
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
