#include <iostream>
#include "Test_Element.hpp"
#include <string>

/// ============================================================================================================
/// 以下有4种重载用于检测转发后的类型 [左值、右值]和[const、非const]的四种组合
/// ============================================================================================================
void Check_Type(Element<int> &type) { std::cout << "\tLvalue reference" << std::endl; }
void Check_Type(const Element<int> &type) { std::cout << "\tconst Lvalue reference" << std::endl; }
void Check_Type(Element<int> &&type) { std::cout << "\tRvalue reference" << std::endl; }
/// ============================================================================================================
void Check_Type(const Element<int> &&type) { std::cout << "\tconst Rvalue reference" << std::endl; }
/// ↑ const &&可以定义，但是没有意义。右值的目的本来就是用于被夺走资源的，
/// const右值等于创建一个常亮临时对象，然后再删除。唯一的价值就是浪费资源
/// ============================================================================================================
/// 所以此时只剩三种 &,const &,&&类型的重载
/// 然后由于Non-const 可以隐式转换为const，所以除非特殊需要，&的重载可以不定义
/// ↓ 所以通常可以只定义const &用于拷贝 + &&用于移动 的两种重载就可以满足需求
// void Check_Type(const Element<int> &type) { std::cout << "\tconst Lvalue reference" << std::endl; }
// void Check_Type(Element<int> &&type) { std::cout << "\tRvalue reference" << std::endl; }
/// ============================================================================================================



/// ============================================================================================================
/// 该类用于测试转发的效果
/// 接受不同的构造参数，转发给不同调用检测类型
/// ============================================================================================================
/// 简化了重载：const & 接受&和const &的左值，&&接受右值，所以只需要重载两个版本就行
/// &&的完美转发解决了上方接受右值后调用左值Check_Type的问题
/// ============================================================================================================
template <typename ElementType>
class Class
{
public:
    /// @brief Class(const ElementType &element)左值重载的特化版，没有特殊需求一般不写
    Class(ElementType &element)
    { // 接受non-const的参数，转发给Check_Type也是non-const的参数
        std::cout << "Prameter Constructed LValue" << std::endl;
        Check_Type(element);
    }
    Class(const ElementType &element)
    { // 接受const &的参数，转发给Check_Type也是const &的参数
        std::cout << "Prameter Constructed const LValue" << std::endl;
        Check_Type(element);
    }
    Class(ElementType &&element)
    { // 接受 &&的参数，转发给Check_Type却是&左值的参数
        std::cout << "Prameter Constructed RValue" << std::endl;
        Check_Type(element);
    }
};

void Normal_Forward()
{
    Element<int> e{1, 1};
    Element<int> re{2, 2};
    const Element<int> ce{2, 2};

    Class<Element<int>> cls{e};                   // 拷贝构造 Lvalue reference
    Class<Element<int>> ccls{ce};                 // 拷贝构造 const Lvalue reference
    Class<Element<int>> rcls{Element<int>{1, 1}}; // 移动构造 Rvalue reference
    Class<Element<int>> xrcls{std::move(re)};     // 拷贝构造 Lvalue reference 因为接受参数后丢失了cv信息
    Class<Element<int>> crcls{std::move(ce)};     // 拷贝构造 const Lvalue reference
                                    // const 不能转为非const，所以即使是xvalue,也会被左值引用右值

   
}

template <typename ElementType>
class Class2
{
public:
    Class2(const ElementType &element)
    { // 接受const &和&的参数，转发给Check_Type是const &的参数
        std::cout << "Prameter Constructed const LValue" << std::endl;
        Check_Type(element);
    }
    Class2(ElementType &&element)
    { // 万能引用接受任意修饰的参数，转发给Check_Type对应的参数(&,const &,&&类型)
        // (仅ElementType为&&类型时，ElementType && &&推导为ElementType &&,所以传入给Check_Type右值，其余都是左值&)
        std::cout << "Prameter Constructed RValue" << std::endl;
        Check_Type(std::forward<ElementType>(element));
    }
};

void Perfect_Forward()
{
    Element<int> e{1, 1};
    Element<int> re{2, 2};
    const Element<int> ce{2, 2};

    Class2<Element<int>> cls{e};                   // 拷贝构造 const Lvalue reference(没定义&重载，所以被隐式转为const &)
    Class2<Element<int>> ccls{ce};                 // 拷贝构造 const Lvalue reference
    Class2<Element<int>> rcls{Element<int>{1, 1}}; // 移动构造 Rvalue reference
    Class2<Element<int>> xrcls{std::move(re)};     // 移动构造 Rvalue reference (完美转发)
    Class2<Element<int>> crcls{std::move(ce)};     // 拷贝构造 const Lvalue reference
                                                  // const 不能转为非const，所以即使是xvalue,也会被左值引用右值
}

int main(int argc, char const *argv[])
{
    // Normal_Forward();
    Perfect_Forward();
    return 0;
}