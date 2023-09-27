
#include <iostream>
#include <vector>
#include "Test_Case.hpp"
#include "Sort.hpp"


void Simple_Sort()
{
    std::vector<int> arr{1, 2, 3, 4, 5, 6};

    // 使用右值，有两个括号，第一个构造，第二个调用operator()
    auto result = Sort::Insert_Directly<int, std::greater<>>()(std::vector<int>(arr));
    for (const auto &x : result)
        std::cout << x << ' ';
    std::cout << std::endl;

    // // 如果使用左值对象时，排序算法会保存内部状态，
    // // 但是一旦调用operator()排序完成后，内部状态就废弃了，
    // // 所以没必要用左值，也就是说复用价值不高
    // Sort::Insert_Directly<int,std::greater<>> method;
    // auto result = method(std::vector<int>(arr));
}

struct Element
{
    int key{};
    int value{};
    Element(int key,int value=0):key{key},value{value}{}

    bool operator!=(const Element& other)
    {
        return key != other.key;
    }
    struct Compare
    {
        bool operator()(const Element &lhs, const Element &rhs)
        {
            return lhs.key < rhs.key;
        }
    };
};

void Custom_Sort()
{
    std::vector<Element> vector;
    for (size_t i = 0; i < 10; i++)
        vector.emplace_back(i * ((i % 2)?1:-1));

    std::cout << "Current Elements in vector" << std::endl;
    for (const auto &x : vector)
        std::cout << x.key << ' ';
    std::cout << std::endl;

    auto result = Sort::Insert_Directly<Element, Element::Compare>()(std::vector<Element>(vector));
    std::cout << "Elements after sorted in vector" << std::endl;
    for (const auto &x : result)
        std::cout << x.key << ' ';
    std::cout << std::endl;
    
}

int main(int argc, char const *argv[])
{
    Simple_Sort();
    Custom_Sort();
    return 0;
}
