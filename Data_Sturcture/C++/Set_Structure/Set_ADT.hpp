#pragma once

// Set 的完整 ADT 定义见：
// Document/ADT/Set_Structure/Set.md
//
// 当前项目约定：
// 1. 公共 ADT 只定义集合成员关系和集合运算语义
// 2. 元素唯一性属于共享契约主体
// 3. 具体存储方式不属于共享契约主体




template <typename ElementType>
class Set
{
public:
    virtual void Insert(ElementType element)   = 0;
    virtual void Delete(ElementType element)   = 0;
    virtual void Has(ElementType element)      = 0;
    virtual void Has(Set subset)               = 0;
    virtual void Size()     = 0;
    virtual void Is_Empty() = 0;
    virtual void Clear() = 0;

public: //运算：交集、并集、差集

    virtual void Union(Set set)               = 0;
    virtual void Intersection(Set set)               = 0;
    virtual void Difference(Set set)               = 0;
};
