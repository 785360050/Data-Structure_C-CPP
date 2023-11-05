#pragma once

#include <concepts>
#include <functional>


// 所有的排序算法都是函数对象都是
template <typename Method, typename Compare = std::less<>>
concept Sort_Method = requires(Method method, std::vector<size_t> list) {
    // std::invocable<Method>;
    std::invoke(method, list);
};

// template <typename ElementType>
// void Swap_int(ElementType &x, ElementType &y)
// {
//     x = x ^ y;
//     y = x ^ y;
//     x = x ^ y;
// }
// template <typename ElementType>
// void Swap_other(ElementType &x, ElementType &y)
// {
//     auto temp = std::move(x);
//     x = std::move(y);
//     y = std::move(temp);
// }

template <typename ElementType>
void Swap(ElementType &x, ElementType &y)
{
    // // 仅integer类型适用
    // if(!std::is_integral<ElementType>::value)
    //     Swap_int<ElementType>(x, y);
    // else
    //     Swap_other<ElementType>(x, y);

    auto temp = std::move(x);
    x = std::move(y);
    y = std::move(temp);
}
