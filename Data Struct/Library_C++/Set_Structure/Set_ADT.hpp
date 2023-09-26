#pragma once




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
