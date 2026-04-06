#pragma once

#include "ADT.hpp"

// Queue 的完整 ADT 定义见：
// Document/ADT/Linear_Structure/Queue.md
//
// 当前项目约定：
// 1. 公共 ADT 只定义队列的逻辑 FIFO 语义
// 2. 非法空队访问和空队出队应视为错误
// 3. 容量上限、循环数组细节、show 等能力不属于共享契约主体

namespace Logic
{
// =std::numeric_limits<size_t>::max()
	template <typename ElementType>
	struct Queue
	{ /// 循环队列
	protected:
		size_t size{};

	protected:
		Queue() = default;
		Queue(size_t size) : size{size}{}
		virtual ~Queue() = default;
	protected:
		
		virtual ElementType &Get_Rear()  = 0;

	public:
		// 清空队列
		virtual void Clear() = 0;
		// 判断是否队空
		bool Is_Empty() const { return size==0; }
		// virtual bool Is_Full() const = 0;

		// 返回队列长度(元素个数)
		size_t Get_Size() const { return size; }
		// 返回队头
		virtual ElementType &Get_Front()  = 0;
		// 元素入队
		virtual void Element_Enqueue(const ElementType& element) = 0;
		virtual void Element_Enqueue(ElementType&& element) = 0;
		// 元素出队
		virtual void Element_Dequeue() = 0;
		// 显示整个队列信息
		virtual void Queue_Show(const std::string &string="") = 0;
	};

}
#if __cplusplus >= 202002L
static_assert(ADT::Linear_Queue<Logic::Queue<int>, int>);
#endif
