

#define BOOST_TEST_MODULE Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <algorithm>

#include "Test_Case.hpp"
#include "Sort.hpp"



// g++ test.cpp -g -o test -lboost_unit_test_framework
BOOST_AUTO_TEST_SUITE(Sort)

BOOST_AUTO_TEST_CASE(EmptyStackTest)
{
    constexpr size_t min = 0, max = 10, count = 10;
    static_assert(Sort_Method<Sort::Insert_Directly<size_t>>);

    const Test_Case<size_t, count, min, max> list;
    // list.Show();

    std::vector<size_t> res{};
    res = list.Sort<Sort::Insert_Directly<size_t, std::greater<>>>();
    BOOST_CHECK(std::is_sorted(res.begin(), res.end(), std::greater<size_t>()));

    res = list.Sort<Sort::Insert_Directly<size_t, std::greater_equal<>>>();
    BOOST_CHECK(std::is_sorted(res.begin(), res.end(), std::greater<size_t>()));


    // 不清楚为什么非升序的结果使用greater_equal会检测失败，7(first)和7比较的时候失败了
    // BOOST_CHECK(std::is_sorted(res.begin(), res.end(), std::greater_equal<size_t>()));
    // list.Show_Result(res, "Insert Directly Sort");
}


BOOST_AUTO_TEST_SUITE_END()
