

#define BOOST_TEST_MODULE Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Sequential_List.hpp"

// g++ unit_test.cpp -g -o unit_test -lboost_unit_test_framework
BOOST_AUTO_TEST_CASE(Con_Destruct)
{
    Sequential_List_Array<int> array(5);

    BOOST_CHECK(array.List_GetLength() == 0);
    BOOST_CHECK(array.List_Get_Maxsize() == 5);
    BOOST_CHECK(array.List_CheckEmpty());

}

#include <limits>
BOOST_AUTO_TEST_CASE(Operations)
{
    using ElementType = int;
    Sequential_List_Array<ElementType> array(5);

    array.Element_Insert(1, std::numeric_limits<ElementType>::max());
    ElementType value = array.List_GetData(1);
    BOOST_CHECK(value = std::numeric_limits<ElementType>::max());
}

// BOOST_AUTO_TEST_CASE(Con/Destruct)
// {
    
// }
// 

