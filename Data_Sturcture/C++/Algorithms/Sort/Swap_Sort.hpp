#pragma once

#include "Global.hpp"

namespace Sort
{

    /// @brief 经典冒泡排序
    ///     每轮将最大/小元素定位到最终位置
    ///     执行n-1轮
    ///     O(n^2)
    template <typename ElementType, typename Compare = std::less<>>
    struct Bubble_Sort
    {
        /// @brief 
        ///     每一轮遍历与相邻的元素比较并交换，
        ///     可以得到一个当前待排序列中的最大元素并移动到最终位置
        ///     所以下一轮的待排序列元素个数-1，直到集合中只有0/1个元素
        /// @param list 
        /// @return 
        std::vector<ElementType> &operator()(std::vector<ElementType> &list)
        {
            for (size_t round = 0; round < list.size(); round++)
            {
                for (size_t i = 0; i < list.size() - round - 1; i++)
                {
                    if (!Compare{}(list[i], list[i + 1]))
                        Swap(list[i], list[i + 1]);
                }
            }

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

    /// @brief 经典快速排序
    ///     每轮找基准值划分左右两个子序列，且每轮可以确定基准值的最终位置，
    ///     递归实现
    template <typename ElementType, typename Compare = std::less<>>
    struct Quick_Sort
    {
    private:
        /// @brief
        ///     修改指定范围内的元素以某一基准元素进行分割
        ///     默认以第一个元素作为基准值
        ///     1. 先将基准值与最后一个元素交换
        ///     2. 在除了最后一个基准值外的元素中，将满足条件的元素移动到左边集合
        ///         移动的过程类似插入排序，视左边一部分的集合为有序集合，然后遍历的时候不断扩充，
        ///         区别在于非有序集合而已
        ///     3. 划分完成后将基准值与左子序列的插入位置元素(也是右子序列的第一个元素)交换位置
        ///         此时基准值落在的最终的位置上，在后续的递归中不会再改变
        ///         
        /// 
        /// @param list 待排序集合
        /// @param index_start 指向收个元素的下标索引
        /// @param index_end 指向最后一个元素的下标索引
        /// @return 分割元素的下标索引
        /// @note 分割的算法可以有多种实现，所以用virtual修饰
        virtual size_t _Partition(std::vector<ElementType> &list, size_t index_start, size_t index_end)
        { // 单边划分，还有双向夹逼的方式，此处省略

            // 默认将收个元素作为基准值取出，此时首元素位置被空出
            ElementType datum = list[index_start];

            // 指向左边左子集划分区域的尾后位置，待划分的集合中的一类元素会被移动到这里
            size_t index_swap_to = index_start;

            Swap(list[index_start], list[index_end]); // 将基准值暂存于末尾

            // 将剩余集合元素与基准值进行比较,true的与index_swap_to所在的元素交换
            for (size_t i{index_start}; i < index_end; i++) 
            {
                // if (list[i] < datum)
                if (Compare{}(list[i], list[index_end])) // 将所有<基准值元素移动到基准值左边，
                {
                    Swap(list[index_swap_to], list[i]);
                    index_swap_to++;
                }
            }
            Swap(list[index_swap_to], list[index_end]); // 将基准值移动到最终分割的位置
            return index_swap_to;
        }

        /// @brief 就地排序版本的快排：参考   https://zh.wikipedia.org/wiki/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F
        ///     递归实现，每层在待排子序列中找一个基准值，
        ///     在基准值的左右两边划分两个子序列，然后递推地对子序列进行快排
        ///     直到子序列只剩一个元素或不存在时，递归终止
        /// @param list 待排子序列
        /// @param index_start 子序列的起始下标
        /// @param index_end 子序列的结束下标
        void Sort_Inplace(std::vector<ElementType> &list, size_t index_start, size_t index_end)
        {
            if(index_start<0 || index_end>=list.size())
                throw std::out_of_range("Index out of range");
            if (index_end - index_start + 1 < 2) // 递归终点，一个子集合中元素数量 < 2
                return;

            // 以基准值将大的和小的部分移动到基准值的左右两边
            size_t index_datum = _Partition(list, index_start, index_end);
            if(index_datum!=index_start)
                Sort_Inplace(list, index_start, index_datum - 1);         // 快排左子集
            if(index_datum!=index_end)
                Sort_Inplace(list, index_datum + 1, index_end);   // 快排右子集
        }

    public:
        std::vector<ElementType> &operator()(std::vector<ElementType> &list)
        {
            Sort_Inplace(list, 0, list.size() - 1);
            return list;
        };
        std::vector<ElementType> &operator()(std::vector<ElementType> &&list)
        {
            return operator()(list); // rvalue -> lvalue && return lvalue
        };
    };

} // namespace Sort
