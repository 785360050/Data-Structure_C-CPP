#pragma once

#include <concepts>
#include <string>
#include <cassert>


/// ============================================================================================================
/// 		使用concept而不是template Abstratc的接口类的好处是
/// 1. 不需要接口类对所有不同的类型进行泛化，导致typename过多
/// 2. concept可控的颗粒度更灵活，相对比template接口类生成的代码量少(可能？)
/// 劣：
///     需要c++20
/// ============================================================================================================

// namespace ADT
// {


template <typename StructureType, typename ElementType>
concept Stack = requires
(StructureType adt, ElementType element, const std::string &string) 
{
    // 判断是否栈空
    adt.Check_Empty();
    // 返回栈顶元素
    adt.Get_Top();

    /// 元素操作
    // 元素入栈
    adt.Element_Push(element);
    // 元素出栈
    adt.Element_Pop();

    adt.Stack_Show(string);
};
// };


// 可以显示内部结构的类型
template <typename DataType,typename ADT>
concept Showable=requires
(ADT stk,const std::string& info)
{
    stk.Show(info);
};


template <typename DataType>
struct cls
{
    void Show(const std::string& ){}
};



// concept的最终应用：静态断言，此处是用于检查接口(用于确保编译时多态)
static_assert(Showable<int, cls<int>>,"Structure Not Showable");
