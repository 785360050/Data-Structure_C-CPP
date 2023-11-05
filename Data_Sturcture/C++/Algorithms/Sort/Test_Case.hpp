#pragma once

#include <random>
#include <chrono>
#include <optional>
#include <map>
#include <vector>

#include "Global.hpp"

/// @tparam ElementType must be avaiable for std::uniform_int_distribution
/// @tparam count random value count
/// @tparam min random min value
/// @tparam max random max value
template <typename ElementType, size_t count, size_t min, size_t max>
struct Test_Case
{
    std::vector<ElementType> values; // 测试用例
    std::map<ElementType, size_t> counter;           // 统计每个元素出现的次数
    std::optional<std::chrono::nanoseconds> duration;//记录最后一次排序的运行时间,如果排序时没有计时，则不存在

public:
    Test_Case()
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<ElementType> distribution(min, max);

        values.reserve(count);
        for (int i = 0; i < count; ++i)
        {
            size_t value = distribution(generator);
            values.emplace_back(value);
            counter[value]++;
        }
    }

    // 拷贝待排序的数组给排序函数对象，处理完成后返回排序后的结果
    // @note 默认计时
    template <Sort_Method Method>
    std::vector<size_t> Sort(bool timing = true)  
    {
        if(duration.has_value()) //重置计时
            duration.reset();
        if (!timing)                                      //{}构造functor后调用对应的operator()
            return Method{}(std::vector<size_t>(values)); // copy array

        std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

        auto res = Method{}(std::vector<size_t>(values)); // copy array

        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        return res;
    }

    void Show() const
    {
        std::cout << "[ 待排序列 ]" << std::endl;
        for (const auto &num : values)
            std::cout << num << ' ';
        std::cout << std::endl;
        std::cout << "[ 各元素出现频率 ]" << std::endl;
        for (const auto &num : counter)
            std::cout << num.first << " : " << num.second << std::endl;
    }
    void Show_Result(std::vector<size_t> list, const std::string &info = "") const
    {
        if (!info.empty())
            std::cout << "[ " << info << " ]\t";
        if(duration.has_value())
            std::cout<< duration.value();
        std::cout<< std::endl;

        for (const auto &num : list)
            std::cout << num << ' ';
        std::cout << std::endl;
    };
};