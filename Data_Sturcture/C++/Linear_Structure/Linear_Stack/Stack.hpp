#pragma once

#include "ADT.hpp"

// Stack 的完整 ADT 定义见：
// Document/ADT/Linear_Structure/Stack.md
//
// 当前项目约定：
// 1. 公共 ADT 只定义栈的逻辑 LIFO 语义
// 2. 非法空栈访问和空栈出栈应视为错误
// 3. 容量上限、存储方向、show 等能力不属于共享契约主体

namespace Logic
{

	template <typename ElementType>
	struct Stack
	{
	protected:
		size_t size{};
		// size_t maxsize{}; /// 元素上限,仅为顺序实现的特性
						  /// 注:若maxszie为size_t类时signed与unsigned类型比较会默认转为unsigned后再比较
	protected:
		Stack() = default;
		Stack(size_t size):size{size}{} 

		virtual ~Stack() noexcept = default;

	public: /// 栈操作
		// 清空栈
		virtual void Clear() = 0;
		// 判断是否栈空
		bool Is_Empty() const { return size == 0; }
		// 返回栈长度(元素个数)
		virtual size_t Get_Size() const { return size; }
		// 返回栈顶元素
		virtual ElementType& Get_Top() = 0;

	public: /// 元素操作
		// 元素入栈
		virtual void Element_Push(const ElementType& element) = 0;
		virtual void Element_Push(ElementType&& element) = 0;
		// 元素出栈
		virtual void Element_Pop() = 0;

	public:
		virtual void Stack_Show(const std::string &string="") = 0;
	};
};
static_assert(ADT::Linear_Stack<Logic::Stack<int>, int>, "Stack must meet the Stack concept");
