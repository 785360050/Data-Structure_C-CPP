#include "Test_Element.hpp"

#define BOOST_TEST_MODULE Stack
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

template <typename DataType = int>
void Check_ID(const Element<DataType> &element, int id, int id_copy, int id_move)
{
    BOOST_CHECK(element.id == id);
    BOOST_CHECK(element.id_copy == id_copy);
    BOOST_CHECK(element.id_move == id_move);
}

template <typename DataType = int>
void Check_Value(const Element<DataType> &element, DataType value, DataType value_pointer, bool pointer_valid = true)
{
    BOOST_CHECK(element.value == value);
    BOOST_CHECK(element.pointer == (pointer_valid ? element.pointer : nullptr));
    if (pointer_valid)
        BOOST_CHECK(*element.pointer == value_pointer);
}

BOOST_AUTO_TEST_CASE(Element_CopyControl)
{
    Element<int> e;
    Check_ID(e, 0, 0, 0);
    Check_Value(e, 0, 0, false);

    Element<int> e1(1, 1);
    Check_ID(e1, 1, 0, 0);
    Check_Value(e1, 1, 1);

    Element<int> e_copy(e);
    Check_ID(e_copy, 0, 1, 0);
    Check_Value(e_copy, 0, 0, false);
    Check_ID(e, 0, 0, 0);
    Check_Value(e, 0, 0, false);

    Element<int> e_move(std::move(e1));
    Check_ID(e_move, 1, 0, 1);
    Check_Value(e_move, 1, 1);
    Check_ID(e1, 1, 0, 0);
    Check_Value(e1, 1, 0, false); // 被移动后资源丢失

    Element<int> e3;
    e3 = e_copy;
    Check_ID(e3, 0, 2, 0);
    Check_Value(e3, 0, 0, false);
    Check_ID(e_copy, 0, 1, 0);
    Check_Value(e_copy, 0, 0, false);

    Element<int> e4;
    e4 = std::move(e_move);
    Check_ID(e4, 1, 0, 2);
    Check_Value(e4, 1, 1);
    Check_ID(e_move, 1, 0, 1);
    Check_Value(e_move, 1, 0, false);
}

/// ============================================================================================================
/// 		Result Output
/// ============================================================================================================
// jevon@Kubuntu:/mnt/WorkSpace/GitHub/Data-Structure_C-CPP/Data_Sturcture/C++/Test/Unit_Test$ valgrind --leak-check=full ./Test_Element
// ==51737== Memcheck, a memory error detector
// ==51737== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
// ==51737== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
// ==51737== Command: ./Test_Element
// ==51737==
// Running 1 test case...
// Default Constructed [0-0-0]:{0,Null}
// Pramater Constructed [1-0-0]:{1,1}
// Copy Constructed [0-1-0]:{0,Null} from [0-0-0]:{0,Null}
// Move Constructed [1-0-1]:{1,1} from [1-0-0]:{1,Null}
// Default Constructed [2-0-0]:{0,Null}
// Copy Assignment [0-2-0]:{0,Null} from [0-1-0]:{0,Null}
// Default Constructed [2-0-0]:{0,Null}
// Move Assignment [1-0-2]:{1,1} from [1-0-1]:{1,Null}
// Deconstructed 1 pointer deleted
// Deconstructed 0
// Deconstructed 1
// Deconstructed 0
// Deconstructed 1
// Deconstructed 0

// *** No errors detected
// ==51737==
// ==51737== HEAP SUMMARY:
// ==51737==     in use at exit: 0 bytes in 0 blocks
// ==51737==   total heap usage: 3,002 allocs, 3,002 frees, 268,266 bytes allocated
// ==51737==
// ==51737== All heap blocks were freed -- no leaks are possible
// ==51737==
// ==51737== For lists of detected and suppressed errors, rerun with: -s
// ==51737== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

BOOST_AUTO_TEST_CASE(Element_Compare)
{
    Element<int> e1, e2(0, 0), e3(1, 0);
    BOOST_CHECK(e1 != e2);
    BOOST_CHECK(e2 != e3);
    BOOST_CHECK(e1 != e3);
    auto e4 = std::move(e3);
    e1.value = 1;
    // 如果一个指针有效一个无效，则不相同
    // e1.poiner==nullpter!=e4.pointer->(int)0
    BOOST_CHECK(e1 != e4);
    e1.pointer = new int(0);
    // 如果都无效，或都有效且指向元素值相同，则相同
    BOOST_CHECK(e1 == e4); // e1.poiner==int *0==e4.pointer->int *0
}