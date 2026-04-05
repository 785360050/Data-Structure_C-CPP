#pragma once

#include <algorithm>
#include <cstddef>
#include <format>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace Trace
{
	enum class Record_Level
	{
		Debug,
		Trace
	};

	enum class Output_Level
	{
		Debug,
		Trace,
		All
	};

	template <typename ElementType>
	struct Linear_List_Slot
	{
		bool occupied{};
		ElementType value{};
	};

	template <typename ElementType>
	using Linear_List_Snapshot = std::vector<Linear_List_Slot<ElementType>>;

	template <typename ValueType>
	std::string Stringify(const ValueType& value)
	{
		std::ostringstream stream;
		stream << value;
		return stream.str();
	}

	template <typename ElementType>
	struct Linear_List_Frame
	{
		Record_Level level{Record_Level::Trace};
		std::string title;
		std::string adt_message;
		std::string impl_message;
		std::vector<Linear_List_Slot<ElementType>> slot_states;
		std::vector<size_t> highlight_positions;
	};

	template <typename ElementType>
	Linear_List_Snapshot<ElementType> Capture_Snapshot(const ElementType* storage, size_t size, size_t capacity)
	{
		Linear_List_Snapshot<ElementType> snapshot(capacity);
		for (size_t index = 0; index < capacity; ++index)
		{
			if (index < size)
				snapshot[index] = {true, storage[index]};
			else
				snapshot[index] = {};
		}
		return snapshot;
	}

	template <typename ElementType>
	class Recorder final
	{
	public:
		using Snapshot = Linear_List_Snapshot<ElementType>;

	private:
		std::vector<Linear_List_Frame<ElementType>> frames;

	public:
		void Push_Frame(Linear_List_Frame<ElementType> frame)
		{
			frames.push_back(std::move(frame));
		}

		void Record_Frame(
			Record_Level level,
			std::string title,
			std::string adt_message,
			std::string impl_message,
			Snapshot snapshot,
			std::vector<size_t> highlight_positions = {})
		{
			frames.push_back({
				level,
				std::move(title),
				std::move(adt_message),
				std::move(impl_message),
				std::move(snapshot),
				std::move(highlight_positions)
			});
		}

		void Record_Debug(std::string title, std::string adt_message, std::string impl_message, Snapshot snapshot, std::vector<size_t> highlight_positions = {})
		{
			Record_Frame(Record_Level::Debug, std::move(title), std::move(adt_message), std::move(impl_message), std::move(snapshot), std::move(highlight_positions));
		}

		void Record_Trace(std::string title, std::string adt_message, std::string impl_message, Snapshot snapshot, std::vector<size_t> highlight_positions = {})
		{
			Record_Frame(Record_Level::Trace, std::move(title), std::move(adt_message), std::move(impl_message), std::move(snapshot), std::move(highlight_positions));
		}

		void Clear()
		{
			frames.clear();
		}

		const std::vector<Linear_List_Frame<ElementType>>& Get_Frames() const
		{
			return frames;
		}

		bool Is_Empty() const
		{
			return frames.empty();
		}
	};

	template <typename ElementType>
	class Console final
	{
		static const char* Level_Label(Record_Level level)
		{
			switch (level)
			{
			case Record_Level::Debug:
				return "Debug";
			case Record_Level::Trace:
				return "Trace";
			}
			return "Unknown";
		}

		static bool Should_Output(Record_Level level, Output_Level output_level)
		{
			if (output_level == Output_Level::All)
				return true;
			if (output_level == Output_Level::Debug)
				return level == Record_Level::Debug;
			return level == Record_Level::Trace;
		}

		static bool Is_Highlighted(const Linear_List_Frame<ElementType>& frame, size_t position)
		{
			return std::find(frame.highlight_positions.begin(), frame.highlight_positions.end(), position) != frame.highlight_positions.end();
		}

		static void Dump_Slots(const Linear_List_Frame<ElementType>& frame, std::ostream& output)
		{
			output << "槽位: ";
			for (size_t index = 0; index < frame.slot_states.size(); ++index)
			{
				const auto& slot = frame.slot_states[index];
				const bool highlighted = Is_Highlighted(frame, index + 1);
				if (highlighted)
					output << '*';
				output << std::format("[{}:{}]", index + 1, slot.occupied ? Stringify(slot.value) : "_");
				if (highlighted)
					output << '*';
				if (index + 1 < frame.slot_states.size())
					output << ' ';
			}
			output << '\n';
		}

	public:
		static void Dump(const Recorder<ElementType>& trace_recorder, std::ostream& output, Output_Level output_level = Output_Level::All)
		{
			const auto& frames = trace_recorder.Get_Frames();
			size_t displayed_index{};
			for (size_t index = 0; index < frames.size(); ++index)
			{
				const auto& frame = frames[index];
				if (!Should_Output(frame.level, output_level))
					continue;
				++displayed_index;
				output << std::format("[{} 第 {} 帧] {}\n", Level_Label(frame.level), displayed_index, frame.title);
				output << std::format("ADT层: {}\n", frame.adt_message);
				output << std::format("实现层: {}\n", frame.impl_message);
				Dump_Slots(frame, output);
				output << '\n';
			}
		}
	};

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Frame(
		Record_Level level,
		std::string title,
		std::string adt_message,
		std::string impl_message,
		Linear_List_Snapshot<ElementType> snapshot,
		std::vector<size_t> highlight_positions = {})
	{
		return {
			level,
			std::move(title),
			std::move(adt_message),
			std::move(impl_message),
			std::move(snapshot),
			std::move(highlight_positions)
		};
	}

	template <typename ElementType>
	void Push_Debug_Frame(
		Recorder<ElementType>& trace_recorder,
		std::string title,
		std::string adt_message,
		std::string impl_message,
		Linear_List_Snapshot<ElementType> snapshot,
		std::vector<size_t> highlight_positions = {})
	{
		trace_recorder.Push_Frame(Make_Frame<ElementType>(
			Record_Level::Debug,
			std::move(title),
			std::move(adt_message),
			std::move(impl_message),
			std::move(snapshot),
			std::move(highlight_positions)));
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Insert_Begin_Frame(Linear_List_Snapshot<ElementType> snapshot, size_t position, const ElementType& value)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"插入前",
			std::format("在逻辑位置 {} 插入元素 {}", position, Stringify(value)),
			"为新元素腾出插入位置。",
			std::move(snapshot),
			{position});
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Shift_Right_Frame(Linear_List_Snapshot<ElementType> snapshot, size_t from_position, size_t to_position)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"右移元素",
			"为插入操作保留目标位置。",
			std::format("将槽位 {} 移动到槽位 {}", from_position, to_position),
			std::move(snapshot),
			{from_position, to_position});
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Insert_Write_Frame(Linear_List_Snapshot<ElementType> snapshot, size_t position)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"写入新值",
			"新元素已经写入逻辑序列。",
			std::format("将新值写入槽位 {}", position),
			std::move(snapshot),
			{position});
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Insert_End_Frame(Linear_List_Snapshot<ElementType> snapshot)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"插入后",
			"插入完成。",
			"插入后，已占用槽位仍保持连续。",
			std::move(snapshot));
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Delete_Begin_Frame(Linear_List_Snapshot<ElementType> snapshot, size_t position)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"删除前",
			std::format("删除逻辑位置 {} 的元素。", position),
			"后续元素将左移以填补空位。",
			std::move(snapshot),
			{position});
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Shift_Left_Frame(Linear_List_Snapshot<ElementType> snapshot, size_t from_position, size_t to_position)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"左移元素",
			"删除后保持剩余元素的逻辑顺序不变。",
			std::format("将槽位 {} 移动到槽位 {}", from_position, to_position),
			std::move(snapshot),
			{from_position, to_position});
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Delete_End_Frame(Linear_List_Snapshot<ElementType> snapshot)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"删除后",
			"删除完成。",
			"删除后，已占用元素仍然从左到右紧密排列。",
			std::move(snapshot));
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Clear_Frame(Linear_List_Snapshot<ElementType> snapshot)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"清空后",
			"清空操作将逻辑序列重置为空。",
			"存储槽位被重置，长度变为 0。",
			std::move(snapshot));
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Expand_Begin_Frame(Linear_List_Snapshot<ElementType> snapshot, size_t capacity, size_t next_capacity)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"扩容前",
			"插入操作需要更多存储空间。",
			std::format("顺序存储空间从 {} 扩展到 {}", capacity, next_capacity),
			std::move(snapshot));
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Expand_End_Frame(Linear_List_Snapshot<ElementType> snapshot, size_t capacity)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"扩容后",
			"扩容后，逻辑序列保持不变。",
			std::format("存储空间重分配完成，新容量为 {}", capacity),
			std::move(snapshot));
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Shrink_Begin_Frame(Linear_List_Snapshot<ElementType> snapshot, size_t capacity, size_t next_capacity)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"缩容前",
			"删除操作减少了已存储元素的数量。",
			std::format("顺序存储空间从 {} 缩减到 {}", capacity, next_capacity),
			std::move(snapshot));
	}

	template <typename ElementType>
	Linear_List_Frame<ElementType> Make_Shrink_End_Frame(Linear_List_Snapshot<ElementType> snapshot, size_t capacity)
	{
		return Make_Frame<ElementType>(
			Record_Level::Trace,
			"缩容后",
			"缩容后，逻辑序列保持不变。",
			std::format("存储空间缩减完成，新容量为 {}", capacity),
			std::move(snapshot));
	}

	template <typename ElementType>
	void Push_Insert_Begin(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot, size_t position, const ElementType& value)
	{
		trace_recorder.Push_Frame(Make_Insert_Begin_Frame(std::move(snapshot), position, value));
	}

	template <typename ElementType>
	void Push_Shift_Right(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot, size_t from_position, size_t to_position)
	{
		trace_recorder.Push_Frame(Make_Shift_Right_Frame(std::move(snapshot), from_position, to_position));
	}

	template <typename ElementType>
	void Push_Insert_Write(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot, size_t position)
	{
		trace_recorder.Push_Frame(Make_Insert_Write_Frame(std::move(snapshot), position));
	}

	template <typename ElementType>
	void Push_Insert_End(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot)
	{
		trace_recorder.Push_Frame(Make_Insert_End_Frame(std::move(snapshot)));
	}

	template <typename ElementType>
	void Push_Delete_Begin(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot, size_t position)
	{
		trace_recorder.Push_Frame(Make_Delete_Begin_Frame(std::move(snapshot), position));
	}

	template <typename ElementType>
	void Push_Shift_Left(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot, size_t from_position, size_t to_position)
	{
		trace_recorder.Push_Frame(Make_Shift_Left_Frame(std::move(snapshot), from_position, to_position));
	}

	template <typename ElementType>
	void Push_Delete_End(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot)
	{
		trace_recorder.Push_Frame(Make_Delete_End_Frame(std::move(snapshot)));
	}

	template <typename ElementType>
	void Push_Clear(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot)
	{
		trace_recorder.Push_Frame(Make_Clear_Frame(std::move(snapshot)));
	}

	template <typename ElementType>
	void Push_Expand_Begin(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot, size_t capacity, size_t next_capacity)
	{
		trace_recorder.Push_Frame(Make_Expand_Begin_Frame(std::move(snapshot), capacity, next_capacity));
	}

	template <typename ElementType>
	void Push_Expand_End(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot, size_t capacity)
	{
		trace_recorder.Push_Frame(Make_Expand_End_Frame(std::move(snapshot), capacity));
	}

	template <typename ElementType>
	void Push_Shrink_Begin(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot, size_t capacity, size_t next_capacity)
	{
		trace_recorder.Push_Frame(Make_Shrink_Begin_Frame(std::move(snapshot), capacity, next_capacity));
	}

	template <typename ElementType>
	void Push_Shrink_End(Recorder<ElementType>& trace_recorder, Linear_List_Snapshot<ElementType> snapshot, size_t capacity)
	{
		trace_recorder.Push_Frame(Make_Shrink_End_Frame(std::move(snapshot), capacity));
	}

	template <typename ElementType>
	Recorder<ElementType>*& Current_Recorder()
	{
		static thread_local Recorder<ElementType>* trace_recorder{};
		return trace_recorder;
	}

	template <typename ElementType>
	class Session final
	{
		Recorder<ElementType>* previous_recorder{};

	public:
		explicit Session(Recorder<ElementType>& trace_recorder)
			: previous_recorder(Current_Recorder<ElementType>())
		{
			Current_Recorder<ElementType>() = &trace_recorder;
		}

		~Session()
		{
			Current_Recorder<ElementType>() = previous_recorder;
		}
	};

	template <typename ElementType>
	void Record_Frame(
		std::string title,
		std::string adt_message,
		std::string impl_message,
		const ElementType* storage,
		size_t size,
		size_t capacity,
		std::vector<size_t> highlight_positions = {})
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;

		trace_recorder->Record_Trace(
			std::move(title),
			std::move(adt_message),
			std::move(impl_message),
			Capture_Snapshot(storage, size, capacity),
			std::move(highlight_positions));
	}

	template <typename ElementType>
	void Insert_Begin(const ElementType* storage, size_t size, size_t capacity, size_t position, const ElementType& value)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Insert_Begin(*trace_recorder, Capture_Snapshot(storage, size, capacity), position, value);
	}

	template <typename ElementType>
	void Shift_Right(const ElementType* storage, size_t size, size_t capacity, size_t from_position, size_t to_position)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Shift_Right(*trace_recorder, Capture_Snapshot(storage, size, capacity), from_position, to_position);
	}

	template <typename ElementType>
	void Insert_Write(const ElementType* storage, size_t size, size_t capacity, size_t position)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Insert_Write(*trace_recorder, Capture_Snapshot(storage, size, capacity), position);
	}

	template <typename ElementType>
	void Insert_End(const ElementType* storage, size_t size, size_t capacity)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Insert_End(*trace_recorder, Capture_Snapshot(storage, size, capacity));
	}

	template <typename ElementType>
	void Delete_Begin(const ElementType* storage, size_t size, size_t capacity, size_t position)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Delete_Begin(*trace_recorder, Capture_Snapshot(storage, size, capacity), position);
	}

	template <typename ElementType>
	void Shift_Left(const ElementType* storage, size_t size, size_t capacity, size_t from_position, size_t to_position)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Shift_Left(*trace_recorder, Capture_Snapshot(storage, size, capacity), from_position, to_position);
	}

	template <typename ElementType>
	void Delete_End(const ElementType* storage, size_t size, size_t capacity)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Delete_End(*trace_recorder, Capture_Snapshot(storage, size, capacity));
	}

	template <typename ElementType>
	void Clear(const ElementType* storage, size_t size, size_t capacity)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Clear(*trace_recorder, Capture_Snapshot(storage, size, capacity));
	}

	template <typename ElementType>
	void Expand_Begin(const ElementType* storage, size_t size, size_t capacity, size_t next_capacity)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Expand_Begin(*trace_recorder, Capture_Snapshot(storage, size, capacity), capacity, next_capacity);
	}

	template <typename ElementType>
	void Expand_End(const ElementType* storage, size_t size, size_t capacity)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Expand_End(*trace_recorder, Capture_Snapshot(storage, size, capacity), capacity);
	}

	template <typename ElementType>
	void Shrink_Begin(const ElementType* storage, size_t size, size_t capacity, size_t next_capacity)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Shrink_Begin(*trace_recorder, Capture_Snapshot(storage, size, capacity), capacity, next_capacity);
	}

	template <typename ElementType>
	void Shrink_End(const ElementType* storage, size_t size, size_t capacity)
	{
		auto* trace_recorder = Current_Recorder<ElementType>();
		if (!trace_recorder)
			return;
		Push_Shrink_End(*trace_recorder, Capture_Snapshot(storage, size, capacity), capacity);
	}
}
