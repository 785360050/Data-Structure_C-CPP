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

    /// @brief 在原有数组上修改元素次序O(n^2)
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
            return this->operator()(list);
        };
    };

    /// @brief O(n^2)
    template <typename ElementType, typename Compare = std::less<>>
    struct Insert_Direct_Optimized
    {
        std::vector<ElementType> operator()(std::vector<ElementType> &list)
        {
            for (int index_target = 0; index_target < list.size(); index_target++)
            {
                ElementType target = list[index_target];
                int i = index_target;
                for (i; i > 0 && !Compare{}(list[i - 1], target); i--)
                    list[i] = std::move(list[i - 1]);
                list[i] = target;
            }
            return list;
        };
        std::vector<ElementType> operator()(std::vector<ElementType> &&list_move)
        {
            auto list = list_move;
            return this->operator()(list);
        };
    };

    /// @brief 默认的gap的缩减跨度为上一轮的1/2
    /// @tparam ElementType 
    /// @tparam Compare 
    template <typename ElementType, typename Compare = std::less<>>
    struct Insert_Shell
    {
        std::vector<ElementType> operator()(std::vector<ElementType> &list)
        { 
            // reoder element per step of gap
            for (int gap = list.size() / 2; gap > 0; gap /= 2)
            { // 每组元素进行插入排序
                for (int index_target = 0; index_target < list.size(); index_target++)
                {
                    ElementType target = list[index_target];
                    int i = index_target;
                    for (i; i > 0 && !Compare{}(list[i - 1], target); i--)
                        list[i] = std::move(list[i - 1]);
                    list[i] = target;
                }
            }
            return list;
        }
        std::vector<ElementType> operator()(std::vector<ElementType> &&list_move)
        { 
            auto list = list_move;
            return this->operator()(list);
        }
    };

} // namespace Sort
