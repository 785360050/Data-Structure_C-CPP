#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>

inline std::unique_ptr<int[]> Make_MergeFindSet_Buffer(std::initializer_list<int> values)
{
    auto buffer = std::make_unique<int[]>(values.size());
    std::size_t index = 0;
    for (int value : values)
        buffer[index++] = value;
    return buffer;
}

template <typename SetType>
SetType Make_MergeFindSet(std::initializer_list<int> values)
{
    auto buffer = Make_MergeFindSet_Buffer(values);
    return SetType(buffer.release(), static_cast<int>(values.size()));
}

template <typename SetType>
void Check_MergeFindSet_Disconnected_And_Same_Group_Behaviour()
{
    auto set = Make_MergeFindSet<SetType>({0, 1, 2, 3});

    BOOST_CHECK(set.Find(0, 0));
    BOOST_CHECK(set.Find(1, 1));
    BOOST_CHECK(!set.Find(0, 1));
    BOOST_CHECK(!set.Find(2, 3));
}

template <typename SetType>
void Check_MergeFindSet_Merge_Behaviour()
{
    auto set = Make_MergeFindSet<SetType>({0, 1, 2, 3, 4});

    set.Merge(0, 2);
    BOOST_CHECK(set.Find(0, 2));

    set.Merge(4, 2);
    BOOST_CHECK(set.Find(0, 4));
    BOOST_CHECK(set.Find(2, 4));
    BOOST_CHECK(!set.Find(1, 4));
}

template <typename SetType>
void Check_MergeFindSet_Repeated_Merge_Behaviour()
{
    auto set = Make_MergeFindSet<SetType>({0, 1, 2});

    BOOST_CHECK_NO_THROW(set.Merge(0, 1));
    BOOST_CHECK_NO_THROW(set.Merge(0, 1));
    BOOST_CHECK_NO_THROW(set.Merge(1, 0));
    BOOST_CHECK(set.Find(0, 1));
    BOOST_CHECK(!set.Find(0, 2));
}

template <typename SetType>
void Check_MergeFindSet_Invalid_Element_Find_Is_Executable()
{
    auto set = Make_MergeFindSet<SetType>({0, 1, 2});

    BOOST_CHECK_NO_THROW((void)set.Find(99, 0));
    BOOST_CHECK(!set.Find(99, 0));
}

template <typename SetType>
void Run_MergeFindSet_Behaviour_Suite()
{
    Check_MergeFindSet_Disconnected_And_Same_Group_Behaviour<SetType>();
    Check_MergeFindSet_Merge_Behaviour<SetType>();
    Check_MergeFindSet_Repeated_Merge_Behaviour<SetType>();
    Check_MergeFindSet_Invalid_Element_Find_Is_Executable<SetType>();
}
