#include <vector>
#include <iostream>


#include "Sort.hpp"
#include "Test_Case.hpp"
// #include "Global.hpp"



int main(int argc, char const *argv[])
{
    constexpr size_t min = 0, max = 10, count = 10;
    static_assert(Sort_Method<Sort::Insert_Directly<size_t>>);

    const Test_Case<size_t, count, min, max> list;
    list.Show();

    auto res = list.Sort<Sort::Insert_Directly<size_t,std::greater_equal<>>>();
    list.Show_Result(res, "Insert Directly Sort");

    // demo
    std::vector<int> arr{1, 2, 3, 4, 5, 6};
    // // 使用左值对象时，排序算法会保存内部状态，
    // // 但是一旦调用operator()排序完成后，内部状态就废弃了，
    // // 所以没必要用左值，也就是说复用价值不高
    // Sort::Insert_Directly<int,std::greater<>> method;
    // auto result = method(std::vector<int>(arr));

    // 如果使用右值，有两个括号，第一个构造，第二个调用operator()
    auto result = Sort::Insert_Directly<int, std::greater<>>()(std::vector<int>(arr));
    for (const auto &x : result)
        std::cout << x << ' ';
    std::cout << std::endl;
    return 0;
}