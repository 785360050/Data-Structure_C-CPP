#include <vector>
#include <iostream>

#include "Test_Case.hpp"
#include "Insertion_Sort.hpp"
#include "Swap_Sort.hpp"
#include "Selection_Sort.hpp"
#include "Merge_Sort.hpp"
// #include "Global.hpp"

/// ============================================================================================================
/// 	所有的排序函数对象，Compare模板参数默认为std::less
///     语义与这些比较函数对象相同
///     例：
///     std::less是升序，因为元素比较时，如果 满足 left < right == true,
/// greater是降序，其他的暂未试过
/// ============================================================================================================
int main(int argc, char const *argv[])
{
    constexpr size_t min = 0, max = 10, count = 10;

    // 驱动类，随机生成待排序数据，每次调用排序函数时拷贝一份数据操作
    // 随机数使用默认的生成引擎 + 均匀分布
    Test_Case<size_t, count, min, max> list;
    list.Show();

    std::vector<size_t> res(count, {}); // 暂存排序结果

    // 1. 检查排序算法函数接口
    // 2. 调用对应函数对象
    // 3. 显示排序结果

    { // 插入排序
        static_assert(Sort_Method<Sort::Insert_Directly<size_t>>);
        res = list.Sort<Sort::Insert_Directly<size_t, std::greater_equal<>>>();
        list.Show_Result(res, "Insert Directly Sort");

        static_assert(Sort_Method<Sort::Insert_Direct_Optimized<size_t>>);
        res = list.Sort<Sort::Insert_Direct_Optimized<size_t, std::greater<>>>();
        list.Show_Result(res, "Insert Directly Sort Optimized");

        static_assert(Sort_Method<Sort::Insert_Shell<size_t>>);
        res = list.Sort<Sort::Insert_Shell<size_t, std::greater<>>>();
        list.Show_Result(res, "Insert Shell");
    }


    { // 交换排序
        static_assert(Sort_Method<Sort::Bubble_Sort<size_t>>);
        res = list.Sort<Sort::Bubble_Sort<size_t, std::less<>>>();
        list.Show_Result(res, "Swap Bubble");

        static_assert(Sort_Method<Sort::Quick_Sort<size_t>>);
        res = list.Sort<Sort::Quick_Sort<size_t, std::less<>>>();
        list.Show_Result(res, "Swap QuickSort");
    }


    { // 选择排序
        static_assert(Sort_Method<Sort::Select_Directly<size_t>>);
        res = list.Sort<Sort::Select_Directly<size_t, std::less<>>>();
        list.Show_Result(res, "Select Directly");

        // Heap_Sort暂略，见以下两种利用STL实现的堆排

        Sort_Extention::Heap_Sort_ByAlgorithm();     // stl算法实现的堆排序，只有大根堆
        Sort_Extention::Heap_Sort_ByPriorityQueue(); // stl::priority实现的堆排序，可自定义比较顺序
    }

    { // 归并排序

        static_assert(Sort_Method<Sort::Merge_Sort<size_t>>);
        res = list.Sort<Sort::Merge_Sort<size_t, std::less<>>>();
        list.Show_Result(res, "Merge Sort");
    }

    return 0;
}