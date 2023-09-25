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

    std::vector<size_t> res(count, {});
    res = list.Sort<Sort::Insert_Directly<size_t, std::greater_equal<>>>();
    list.Show_Result(res, "Insert Directly Sort");

    res = list.Sort<Sort::Insert_Direct_Optimized<size_t, std::greater<>>>();
    list.Show_Result(res, "Insert Directly Sort Optimized");

    res = list.Sort<Sort::Insert_Shell<size_t, std::greater<>>>();
    list.Show_Result(res, "Insert Shell");

    return 0;
}