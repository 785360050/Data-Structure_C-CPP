#pragma once

#if __cplusplus >= 202002L
#include <concepts>

namespace ADT
{
    /// index从1开始，非数组下标从0开始
    template <typename StructureType, typename KeyType,typename ElementType>
    concept B_Tree = requires(StructureType adt,KeyType&& key, ElementType &&element) {
        // 判断是否为空
        adt.Is_Empty();

        // 获取当前元素个数
        adt.Get_Size();
        // adt.Get_Capcity();//静态数组才有

        // 重置线性表为初始状态，清空所有元素(会析构所有元素)
        adt.Clear();

        // 在index位置插入element
        adt.Element_Insert(key,element);
        // 删除index位置的元素
        adt.Element_Delete(key);
        // 获取key对应的元素
        adt[key]; //ElementType&
        // // 设置index位置的元素为element
        // adt.Element_Update(key,element);
    };
};
#endif