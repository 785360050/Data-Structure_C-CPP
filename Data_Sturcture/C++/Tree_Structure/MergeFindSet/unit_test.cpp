#include <iostream>
#include <vector>
#include <map>
#include <boost/pending/disjoint_sets.hpp>

int main()
{
    // 创建一组元素，例如：{0, 1, 2, 3, 4, 5}
    std::vector<int> elements(6);
    for (int i = 0; i < 6; ++i)
    {
        elements[i] = i;
    }

    // 创建并查集对象
    boost::disjoint_sets<
        boost::associative_property_map<std::map<int, int>>,
        boost::associative_property_map<std::map<int, int>>>
        ds(elements.begin(), elements.end());

    // 初始化并查集
    for (int i = 0; i < 6; ++i)
    {
        ds.make_set(i);
    }

    // 合并元素的集合
    ds.union_set(0, 1);
    ds.union_set(2, 3);
    ds.union_set(4, 5);
    ds.union_set(1, 3); // 这将连接整个集合 {0, 1, 2, 3, 4, 5}

    // 查找元素所在的集合的代表元素
    int representative = ds.find_set(4); // 代表元素应为0或1

    // 输出每个元素的代表元素
    for (int i = 0; i < 6; ++i)
    {
        std::cout << "Element " << i << " is in the set with representative " << ds.find_set(i) << std::endl;
    }

    return 0;
}
