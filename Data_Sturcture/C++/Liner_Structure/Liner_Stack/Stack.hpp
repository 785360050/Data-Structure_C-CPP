#pragma once

#include "ADT.hpp"

namespace Logic
{

	/// ============================================================================================================
	/// 		仅实现静态空间的大小的线性栈,动态空间特性通常不会用栈
	/// ============================================================================================================
	template <typename ElementType>
	struct Stack
	{
	protected:
		size_t maxsize{}; /// 元素上限
		/// 注:若maxszie为size_t类时signed与unsigned类型比较会默认转为unsigned后再比较
	protected:
		Stack(size_t maxsize = 5)
		{
			// if (maxsize < 1)
			// 	throw std::invalid_argument("Stack Init Failed: maxsize must be greater than 1");
			static_assert(maxsize < 1, "Stack Init Failed: maxsize must be greater than 1");
			this->maxsize = maxsize;
		}
		virtual ~Stack() noexcept = default;

	public: /// 栈操作
		// 清空栈
		virtual void Clear() = 0;
		// 判断是否栈空
		virtual bool Is_Empty() const = 0;
		// 返回栈长度(元素个数)
		virtual size_t Get_Size() const = 0;
		// 返回栈顶元素
		virtual ElementType& Get_Top() const = 0;

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
static_assert(ADT::Liner_Stack<Logic::Stack<int>, int>, "Stack must meet the Stack concept");