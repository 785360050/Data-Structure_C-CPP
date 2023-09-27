

#define BOOST_TEST_MODULE Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "Liner_List_Sequential.h"


// g++ test.cpp -g -o test -lboost_unit_test_framework
BOOST_AUTO_TEST_CASE(Con_Destruct)
{
    static_assert(ADT::Liner_Sequential_List<Sequential_List_Array<int>,int>);

    BOOST_CHECK(Sequential_List_Array<int>().List_CheckEmpty());
    BOOST_CHECK(!Sequential_List_Array<int>().List_Get_Maxsize());

    Sequential_List_Array<int> array(5);
    BOOST_CHECK(array.List_Get_Maxsize());
    BOOST_CHECK(array.List_CheckEmpty());
    array.Element_Insert(1, 0);
    BOOST_CHECK(!array.List_CheckEmpty());

    array.Element_Insert(10,10);
}
// BOOST_AUTO_TEST_CASE(Con/Destruct)
// {
    
// }
// 

