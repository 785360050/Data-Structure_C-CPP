#pragma once

#include "Global.hpp"

namespace Sort
{

    template <typename ElementType, typename Compare = std::less<>>
    struct Select_Directly
    {
        /// @brief
        // 在未排序序列中找到最小（大）元素，存放到排序序列的起始位置，
        // 然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
        // 以此类推，直到所有元素均排序完毕。
        // 选择排序的主要优点与数据移动有关。
        // 如果某个元素位于正确的最终位置上，则它不会被移动。
        // 选择排序每次交换一对元素，它们当中至少有一个将被移到其最终位置上，因此对
        // 在所有的完全依靠交换去移动元素的排序方法中，选择排序属于非常好的一种。
        /// @param list
        /// @return
        std::vector<ElementType> &operator()(std::vector<ElementType> &list)
        {
            // 遍历所有位置，左侧为有序集合，当前和右侧为待排序集合
            // 每轮在当前位置上与待排序集合中最小的元素交换
            for (size_t i = 0; i < list.size(); i++)
            {
                size_t index_min = i;
                // 找到待排序的集合中最小的元素
                for (size_t index = i + 1; index < list.size(); index++)
                {
                    if (!Compare{}(list[index_min], list[index]))
                        index_min = index;
                }

                // 如果落在最终位置上，则不做任何操作
                // 否则与待排序集合中最小元素交换
                if (index_min != i)
                    Swap(list[i], list[index_min]);
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

    template <typename ElementType, typename Compare = std::less<>>
    struct Heap_Sort
    {

        std::vector<ElementType> &operator()(std::vector<ElementType> &list)
        {

            return list;
        };
        std::vector<ElementType> &operator()(std::vector<ElementType> &&list)
        {
            return operator()(list); // rvalue -> lvalue && return lvalue
        };
    };

} // namespace Sort

#include <algorithm>
#include <queue>
#include <iostream>

/// @brief 补充的实现方式
namespace Sort_Extention
{
    static void Show_Heap(const std::vector<int> &ivec, const std::string &msg = "")
    {
        if(!msg.empty())
            std::cout << msg << std::endl;
        for (int i = 0; i < ivec.size(); ++i)
            std::cout << ivec[i] << " ";
        std::cout << std::endl;
    }
    /// @brief STL中有heap相关的算法，但是只能以大根堆实现
    void Heap_Sort_ByAlgorithm()
    {
        std::cout << "[STL堆算法实现的堆排序]" << std::endl;
        std::vector<int> ivec{0, 1, 2, 3, 4, 8, 9, 3, 5};

        std::make_heap(ivec.begin(), ivec.end());
        std::vector<int> result;
        while (!ivec.empty())
        {
            std::pop_heap(ivec.begin(), ivec.end());
            result.push_back(ivec[ivec.size() - 1]);
            ivec.pop_back();
        }

        Show_Heap(result);
    }

    void Heap_Sort_ByPriorityQueue()
    {
        std::cout << "[STL::priority_queue实现的堆排序]" << std::endl;
        std::priority_queue<int, std::vector<int>, std::greater<>> heap; // 小根堆
        for (const auto e : {0, 1, 2, 3, 4, 8, 9, 3, 5})
            heap.push(e);
        std::vector<int> result;
        while (!heap.empty())
        {
            result.push_back(heap.top());
            heap.pop();
        }
        Show_Heap(result);
    }
}
