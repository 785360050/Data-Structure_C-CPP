#pragma once


#include "Global.hpp"



namespace Sort
{
    // //最终的排序结果要么升序要么降序
    // enum struct Order : bool
    // {
    //     Ascending,
    //     Descending,
    // };
    // struct Property
    // {
    //     Order order{};
    //     Property(Order order) : order{order} {};
    // };

    /// @brief 在原有数组上修改元素次序
    /// @tparam Compare 只能传入less或greater，equal的逻辑由算法稳定性决定
    /// 使用oprator!=对比为true后再调用comapre比较
    template <typename ElementType, typename Compare = std::less<>>
    struct Insert_Directly
    {
        std::vector<ElementType> operator()(std::vector<ElementType> &list)
        {
            for (int i = 1; i < list.size(); i++)
                for (int n = i; n > 0; --n)
                    if (list[n - 1] != list[n] && !Compare{}(list[n - 1], list[n]))
                        Swap(list[n - 1], list[n]);
            return list;
        };
        std::vector<ElementType> operator()(std::vector<ElementType> &&list_move)
        {
            auto list = list_move;
            for (int i = 1; i < list.size(); i++)
                for (int n = i; n > 0; --n)
                    if (list[n - 1] != list[n] && !Compare{}(list[n - 1], list[n]))
                        Swap(list[n - 1], list[n]);
            return list;
        };
    };

} // namespace Sort



