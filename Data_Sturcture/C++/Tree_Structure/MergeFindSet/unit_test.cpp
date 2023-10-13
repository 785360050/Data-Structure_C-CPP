
#include <iostream>

#include <boost/pending/disjoint_sets.hpp>

int main()
{
    int numElements = 5;
    std::vector<int> parent(numElements);  // 用于表示每个元素的父节点
    std::vector<int> rank(numElements, 0); // 用于表示每个集合的秩

    boost::disjoint_sets<int *, int *,boost::find_with_full_path_compression> ds(&parent[0], &rank[0]);

    // 初始化并查集
    for (int i = 0; i < numElements; i++)
        parent[i] = i;

    // 合并元素 1 和 2
    ds.union_set(1, 2);

    // 查找元素所属的集合
    int set1 = ds.find_set(1);
    int set2 = ds.find_set(2);

    // 检查元素 1 和 2 是否在同一集合
    if (set1 == set2)
    {
        std::cout << "Element 1 and 2 are in the same set." << std::endl;
    }
    else
    {
        std::cout << "Element 1 and 2 are in different sets." << std::endl;
    }

    return 0;
}