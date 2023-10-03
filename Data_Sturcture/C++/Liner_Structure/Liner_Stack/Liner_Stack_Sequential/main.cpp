
#include <vector>
#include <array>
// std::vector<int> vector;
// vector.push_back(1);
// vector.emplace_back(1);
#include "../../../Test/Unit_Test/Test_Element.hpp"

/// ============================================================================================================
/// 如果是堆分配的内存，使用placement new时需要手动调用析构函数
/// 栈分配的内存不需要手动调用析构函数，因为构造和析构是自动进行的
///     注意：栈上的元素不要再使用placement new进行构造,因为已经默认构造过了
///     再次构造会导致泄漏(元素持有的new资源会泄漏，如果没有，重复构造无影响，等价于赋值覆盖原有数据)
/// ============================================================================================================
/// 不要手动调用void *operator new(std::size_t, void *__p)，
/// 该函数是被placement new调用的,直接调用不会产生任何效果，因为源码直接返回__p
/// ============================================================================================================
void Test_Construct()
{

    // Element<int> stack_array[5];//定义在栈上的数组，自动调用默认构造

    // // /// 不能在栈上使用placement new进行构造,因为已经默认构造过了
    // // /// 所以对于栈空间，通常使用的是copy和move
    // // for (size_t i = 0; i < 5; i++)
    // //     new (&stack_array[i]) Element;

    // // std::vector<Element<int>> vector(5);
    // // std::array<Element<int>,5> std_array;

    // Element<int>* array=new Element<int>[5];
    
    void *memory = operator new(sizeof(Element<int>) * 5);//分配内存
    Element<int> *array = reinterpret_cast<Element<int> *>(memory); // 格式化内存
    // Element<int> *array = (Element<int> *)malloc(sizeof(Element<int>) * 5);
    for (size_t i = 0; i < 5; i++)
    {
        auto p = &array[i];
        new (p) Element(i, i);
    }

    // void *memory = operator new(sizeof(Element<int>) * 5);//分配内存
    // Element<int> *array = static_cast<Element<int> *>(memory); // 格式化内存
    // for (size_t i = 0; i < 5; i++)
    // {
    //     operator new(sizeof(Element<int>), &array[i]);
    //     // void * element=operator new(sizeof(Element<int>), &array[i]);
    //     // std::cout << std::boolalpha << (array[i] == *static_cast<Element<int> *>(element))<<std::endl;
    // }


    for (size_t i = 0; i < 5;i++)
        // (*static_cast<Element<int>*>(array + sizeof(Element<int>) * i)).~Element();
        array[i].~Element();
    
    // delete[] array;
    free(memory);

    // std::vector<Element<int>> vector(5);
    // std::array<Element<int>,5> std_array;
}

int main(int argc, char const *argv[])
{
    Test_Construct();
    return 0;
}
