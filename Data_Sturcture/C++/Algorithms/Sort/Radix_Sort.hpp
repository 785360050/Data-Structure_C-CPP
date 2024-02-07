#pragma once

#include "Global.hpp"

#include <string>
#include <string.h>

/// ============================================================================================================
/// 		以后再说，感觉实现出来意义不大，应用价值不高
/// ============================================================================================================

using ElementType = int;

size_t maxbit(const std::vector<ElementType> &data) // 辅助函数，求数据的最大位数
{
    int d = 1; // 保存最大的位数
    int p = 10;
    for (int i = 0; i < data.size(); ++i)
    {
        while (data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;
}
std::vector<ElementType> &sort(std::vector<ElementType> &list)
{
    int digits = maxbit(list); // 待排数据的最大位数
    size_t n = list.size();
    int *tmp = new int[n];
    int *count = new int[10]; // 计数器
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= digits; i++) // 最多几位数就排序几次
    {
        memset(count, 0, sizeof(int) * 10); // 每次分配前清空计数器
        for (j = 0; j < n; j++)
        {
            k = (list[j] / radix) % 10; // 统计每个桶中的记录数
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; // 将tmp中的位置依次分配给每个桶
        for (j = n - 1; j >= 0; j--)            // 将所有桶中记录依次收集到tmp中
        {
            k = (list[j] / radix) % 10;
            tmp[count[k] - 1] = list[j];
            count[k]--;
        }
        for (j = 0; j < n; j++) // 将临时数组的内容复制到list中
            list[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;

    return list;
};

namespace Sort
{

    /// @brief 基数排序
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
                i_left{index_left},     // 左序列起点
                i_right{index_mid + 1}; // mid+1是右序列的起点
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
            while (i_left <= index_mid)
                v.push_back(list[i_left++]);
            while (i_right <= index_right)
                v.push_back(list[i_right++]);

            // 重新写回原数组
            size_t i{index_left};
            for (const auto &e : v)
                list[i++] = std::move(e);
        }


    public:
        std::vector<ElementType> &operator()(std::vector<ElementType> &list)
        {
            int digits = maxbit(list);//待排数据的最大位数
            size_t n = list.size();
            int *tmp = new int[n];
            int *count = new int[10]; // 计数器
            int i, j, k;
            int radix = 1;
            for (i = 1; i <= digits; i++) // 进行d次排序
            {
                std::memset(count, 0, sizeof(int) * 10); // 每次分配前清空计数器
                for (j = 0; j < n; j++)
                {
                    k = (list[j] / radix) % 10; // 统计每个桶中的记录数
                    count[k]++;
                }
                for (j = 1; j < 10; j++)
                    count[j] = count[j - 1] + count[j]; // 将tmp中的位置依次分配给每个桶
                for (j = n - 1; j >= 0; j--)            // 将所有桶中记录依次收集到tmp中
                {
                    k = (list[j] / radix) % 10;
                    tmp[count[k] - 1] = list[j];
                    count[k]--;
                }
                for (j = 0; j < n; j++) // 将临时数组的内容复制到list中
                    list[j] = tmp[j];
                radix = radix * 10;
            }
            delete[] tmp;
            delete[] count;

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
