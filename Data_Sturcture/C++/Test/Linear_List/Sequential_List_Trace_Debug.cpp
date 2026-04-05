#include <iostream>

#include "Linear_Structure/Linear_List/Sequential_List/Sequential_List.hpp"
#include "Trace/Linear_List_Trace.hpp"

namespace
{
	Trace::Linear_List_Snapshot<int> Capture_Debug_Snapshot(Sequential_List_Dynamic<int>& list)
	{
		Trace::Linear_List_Snapshot<int> snapshot(list.Get_Capcity());
		const size_t size = list.Get_Size();
		const size_t capacity = list.Get_Capcity();
		for (size_t index = 0; index < capacity; ++index)
		{
			if (index < size)
				snapshot[index] = {true, list[index + 1]};
			else
				snapshot[index] = {};
		}
		return snapshot;
	}

	void Record_Debug_State(
		Trace::Recorder<int>& trace_recorder,
		Sequential_List_Dynamic<int>& list,
		const std::string& title,
		const std::string& adt_message,
		const std::string& impl_message)
	{
		trace_recorder.Record_Debug(title, adt_message, impl_message, Capture_Debug_Snapshot(list));
	}

	void Dump_Operation_Header(const std::string& operation_name)
	{
		std::cout << "\n== " << operation_name << " ==\n";
	}

	void Dump_Trace(const Trace::Recorder<int>& trace_recorder, Trace::Output_Level output_level, const std::string& output_name)
	{
		std::cout << "-- " << output_name << " --\n";
		if (trace_recorder.Is_Empty())
		{
			std::cout << "[没有可输出的调试帧]\n";
			return;
		}

		Trace::Console<int>::Dump(trace_recorder, std::cout, output_level);
	}
}

int main()
{
	Sequential_List_Dynamic<int> list(2);
	Trace::Recorder<int> trace_recorder;

	{
		Trace::Session<int> trace_session(trace_recorder);

		trace_recorder.Clear();
		Record_Debug_State(trace_recorder, list, "操作前快照", "准备执行插入操作。", "当前记录的是插入前的整体状态。");
		list.Element_Insert(1, 10);
		Record_Debug_State(trace_recorder, list, "操作后快照", "插入操作已经完成。", "当前记录的是插入后的整体状态。");
		Dump_Operation_Header("在位置 1 插入 10");
		Dump_Trace(trace_recorder, Trace::Output_Level::All, "全部输出");

		trace_recorder.Clear();
		Record_Debug_State(trace_recorder, list, "操作前快照", "准备执行插入操作。", "当前记录的是插入前的整体状态。");
		list.Element_Insert(2, 20);
		Record_Debug_State(trace_recorder, list, "操作后快照", "插入操作已经完成。", "当前记录的是插入后的整体状态。");
		Dump_Operation_Header("在位置 2 插入 20");
		Dump_Trace(trace_recorder, Trace::Output_Level::All, "全部输出");

		trace_recorder.Clear();
		Record_Debug_State(trace_recorder, list, "操作前快照", "准备执行插入操作。", "当前记录的是插入前的整体状态。");
		list.Element_Insert(2, 99);
		Record_Debug_State(trace_recorder, list, "操作后快照", "插入操作已经完成。", "当前记录的是插入后的整体状态。");
		Dump_Operation_Header("在位置 2 插入 99");
		Dump_Trace(trace_recorder, Trace::Output_Level::Debug, "仅输出 Debug");
		Dump_Trace(trace_recorder, Trace::Output_Level::Trace, "仅输出 Trace");

		trace_recorder.Clear();
		Record_Debug_State(trace_recorder, list, "操作前快照", "准备执行删除操作。", "当前记录的是删除前的整体状态。");
		list.Element_Delete(2);
		Record_Debug_State(trace_recorder, list, "操作后快照", "删除操作已经完成。", "当前记录的是删除后的整体状态。");
		Dump_Operation_Header("删除位置 2 的元素");
		Dump_Trace(trace_recorder, Trace::Output_Level::All, "全部输出");

		trace_recorder.Clear();
		Record_Debug_State(trace_recorder, list, "操作前快照", "准备执行清空操作。", "当前记录的是清空前的整体状态。");
		list.List_Clear();
		Record_Debug_State(trace_recorder, list, "操作后快照", "清空操作已经完成。", "当前记录的是清空后的整体状态。");
		Dump_Operation_Header("清空顺序表");
		Dump_Trace(trace_recorder, Trace::Output_Level::All, "全部输出");
	}

	return 0;
}
