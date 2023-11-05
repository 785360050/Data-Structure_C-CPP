#pragma once

#include "Global.hpp"

namespace Sort
{

    /// @brief 经典归并排序
    /// @tparam ElementType
    /// @tparam Compare
    template <typename ElementType, typename Compare = std::less<>>
    struct Merge_Sort
    {
    private:
        /// @brief 递归版的合并实现
        /// @param list 整体待排序列
        /// @param index_left 左子序列起始下标
        /// @param index_mid 中间下标
        /// @param index_right 右子序列终止下标
        /// @note 两个子序列的范围
        ///     left∈[index_left,index_mid],
        ///     right∈[index_mid+1,index_right]
        void Merge(
            std::vector<ElementType> &list,
            size_t index_left,
            size_t index_mid,
            size_t index_right)
        {
            std::vector<ElementType> v;
            // 两顺序表合并算法，写入临时数组
            size_t 
                i_left{index_left}, //左序列起点
                i_right{index_mid+1};//mid+1是右序列的起点
            while (i_left <= index_mid && i_right <= index_right)
            {
                if (Compare{}(list[i_left], list[i_right]))
                    v.push_back(std::move(list[i_left++]));
                else
                    v.push_back(std::move(list[i_right++]));
            }
            // 此时必定有其中一个序列已遍历完
            // 若某一序列未遍历完,则直接将剩余元素全部加入临时数组
            // 下方的两个while最多只会执行其中一个
            while(i_left<=index_mid)
                v.push_back(list[i_left++]);
            while(i_right<=index_right)
                v.push_back(list[i_right++]);

            // 重新写回原数组
            size_t i{index_left};
            for (const auto& e: v) 
                list[i++] = std::move(e);
        }

        /// @brief 分治法
        ///     递 = 分割
        ///     归 = 排序
        ///
        /// @param list
        /// @param index_left 起始元素下标
        /// @param index_right 终止元素下标
        void BinaryMerge(std::vector<ElementType> &list, size_t index_left, size_t index_right)
        {
            if (index_left >= index_right) // 至少两个元素
                return;                    /// 递归终止
            const size_t mid = (index_left + index_right) / 2;

            BinaryMerge(list, index_left, mid);
            BinaryMerge(list, mid + 1, index_right);
            /// 递	拆分所有元素为独立的有序数组
            /// ——————————————————————
            /// 归	合并有序数组，真正实现排序的部分
            Merge(list, index_left, mid, index_right);
        }

    public:
        std::vector<ElementType> &operator()(std::vector<ElementType> &list)
        {
            BinaryMerge(list, 0, list.size() - 1);

            return list;
        };
        std::vector<ElementType> &operator()(std::vector<ElementType> &&list)
        {
            return operator()(list); // rvalue -> lvalue && return lvalue
        };
    };

    namespace Optimized
    {

    } // namespace Optimized

} // namespace Sort
