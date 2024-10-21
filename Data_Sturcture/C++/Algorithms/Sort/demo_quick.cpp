#include "Swap_Sort.hpp"

#include <iostream>
int main(int argc, char const *argv[])
{
    Sort::Quick_Sort<size_t> quick_sort;
    auto res=quick_sort({7, 3, 2, 6, 5, 9, 8, 1, 4});
    for (const auto& e: res) 
        std::cout<<e<<' ';
    std::cout<<'\n';

    return 0;
}
