#pragma once

#include <random>
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
    std::vector<size_t> values;
    std::map<size_t, size_t> counter;

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
    template <Sort_Method Method>
    std::vector<size_t> Sort() const
    {                                                 //{}构造functor，()调用operator()
        return Method{}(std::vector<size_t>(values)); // copy array
    }
    void Show() const
    {
        for (const auto &num : values)
            std::cout << num << ' ';
        std::cout << std::endl;
        for (const auto &num : counter)
            std::cout << num.first << " : " << num.second << std::endl;
    }
    void Show_Result(std::vector<size_t> list, const std::string &info = "") const
    {
        if (!info.empty())
            std::cout << "[ " << info << " ]" << std::endl;
        for (const auto &num : list)
            std::cout << num << ' ';
        std::cout << std::endl;
    };
};