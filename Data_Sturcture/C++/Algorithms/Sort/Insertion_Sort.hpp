#pragma once

#include "Global.hpp"

namespace Sort
{

    /// @brief 直接插入排序
    /// 在原有数组上修改元素次序O(n^2)
    /// @tparam Compare 只能传入less或greater，equal的逻辑由算法稳定性决定
    /// 使用oprator!=对比为true后再调用comapre比较
    template <typename ElementType, typename Compare = std::less<>>
    struct Insert_Directly
    {
        std::vector<ElementType> operator()(std::vector<ElementType> &list)
        {
            
            if(list.size()<=1)//至少两个元素再排序
                return list;

            for (size_t index_target{1}; index_target < list.size(); index_target++)
            {
                ElementType target = std::move(list[index_target]);
                size_t i{index_target};
                while (i > 0 && !Compare{}(list[i - 1], target))
                {
                    list[i] = std::move(list[i - 1]);
                    --i;
                }
                list[i] = std::move(target);
            }
            return list;
        };
        std::vector<ElementType> operator()(std::vector<ElementType> &&list_move)
        {
            auto list = list_move;
            return this->operator()(list);
        };
    };

    /// @brief 每轮分组的gap默认取质数，缩减跨度为上一轮的1/2
    /// 默认使用直接插入排序对每组元素排序
    template <typename ElementType, typename Compare = std::less<>>
    struct Insert_Shell
    { 
    protected:
        constexpr size_t _Index_Previous_Element(const size_t index, size_t gap) noexcept
        {
            return index - gap;
        }
        constexpr size_t _Index_Next_Element(const size_t index, size_t gap) noexcept
        {
            return index + gap;
        }

    public:
        std::vector<ElementType> operator()(std::vector<ElementType> &list)
        {
            if(list.size()<1)
                return list;

            // 初始步长：Hibbard增量质数 2^n-1, 这里取log2(n+1)
            size_t _gap = static_cast<size_t>(std::log2(list.size() + 1));

            // 每轮按不同的步长分组，组内插入排序(可换排序方式)。下一轮步长减半(同为质数)
            // gap表示当前元素位置往后数的第gap个元素，组内两个元素之间间隔gap-1个元素
            for (size_t gap{_gap}; gap > 0; gap /= 2)
            {
                // 每一轮排序一组，每轮定位到组的开头元素
                for (size_t index_group{0}; index_group < gap; index_group++)
                {
                    size_t index_target{_Index_Next_Element(index_group, gap)};
                    if (index_target > list.size()) //组内只有一个元素,不需要排序
                        continue;

                    /// ============================================================================================================
                    /// 		插入排序部分
                    /// ============================================================================================================
                    for (; index_target < list.size();index_target=_Index_Next_Element(index_target, gap))
                    {
                        ElementType target = std::move(list[index_target]); // 插入的元素

                        size_t i{index_target}, index_previous{_Index_Previous_Element(i, gap)};
                        while (i >= gap && !Compare{}(list[index_previous], target))
                        { // 防止下溢出,溢出说明前面没有组内元素了
                            list[i] = std::move(list[index_previous]);
                            i = _Index_Previous_Element(i, gap);
                            index_previous = _Index_Previous_Element(i, gap);
                        }
                        list[i] = std::move(target);//插入到有序子序列的最终位置
                    }
                }
            }
            return list;
        }
        std::vector<ElementType> &operator()(std::vector<ElementType> &&list_move)
        {
            auto list = list_move;
            return this->operator()(list);
        }
    };

} // namespace Sort
