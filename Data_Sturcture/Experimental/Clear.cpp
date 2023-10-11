
#include <iostream>

/// ============================================================================================================
/// 该demo用于演示Clear清空栈上所有模板类型的元素(包括栈元素、堆元素)，[不完整]
/// 用if constexpr判断,不能用if判断，否则会导致所有类型都以同一个类型进行清空，如Int 、int* 都被判定为int 类型
/// ============================================================================================================

constexpr size_t size = 5;

template <typename ElementType>
void List_Clear(std::initializer_list<ElementType> list) 
{
    ElementType storage[size]{};
    for (const auto& e: list) 
    {
        static size_t i = 0;
        storage[i] = e;
        i++;
    }

    // 如果存指针的话要delete的操作
    if constexpr (std::is_pointer<ElementType>::value)
    {
        std::cout << "_Destroy_PointerElements" << std::endl;
        for (size_t i = 0; i < size; i++)
        {
            if constexpr (!std::is_array<ElementType>::value)
            {
                std::cout << "_Destroy_PointerElements_NonArray" << std::endl;
                delete storage[i];
            }
            else
            {
                std::cout << "_Destroy_PointerElements_Array" << std::endl;
                delete[] storage[i];
            }
        }
    }
    else
    { // 栈上的元素不要手动调用析构函数，退栈时系统会自动调用
        std::cout << "_Destroy_NonPointerElements" << std::endl;
        for (size_t i = 0; i < size; i++)
            storage[i] = ElementType{};
    }

}

int main(int argc, char const *argv[])
{
    List_Clear<int>({1,2,3});
    List_Clear<int*>({new int(1), new int(2), new int(3)});
    // List_Clear<int[2]>({{1, 2}, {3, 4}, {5, 6}});
    return 0;
}
