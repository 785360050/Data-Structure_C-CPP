#pragma once

#include <iostream>

static int counter{};

template <typename DataType = int>
struct Element
{
public:
    // 被移动的元素id标记为负值，所有copy的元素id都相同
    int id{counter++};

public:
    DataType value{};
    // 对于所有构造、赋值都会默认申请空间。如果不在此处初始化，则下面的拷贝控制需要微调
    DataType *pointer{new DataType()}; // 指针

public:
    Element()
    {
        // std::cout << "Default Constructed " << id << std::endl;
    }
    Element(DataType value, DataType value_pointer) : value{value}
    {
        // std::cout << "Pramater Constructed " << id << std::endl;
        *pointer = value_pointer;
    }

    Element(const Element &other)
    {
        // std::cout << "Copy Constructed " << id << std::endl;
        if (this == &other)
            // return *this;
            throw std::logic_error("Self copy error");
        id = other.id;
        value = other.value;
        *pointer = *other.pointer; // copy
    }
    Element &operator=(const Element &other)
    {
        // std::cout << "Copy Assignment " << id << std::endl;
        if (this == &other)
            // return *this;
            throw std::logic_error("Self copy error");
        id = other.id;
        value = other.value;
        if (pointer && pointer != other.pointer)
            *pointer = *other.pointer; // copy
        return *this;
    }

    Element(Element &&other)
    {
        // std::cout << "Move Constructed " << id << std::endl;
        if (this == &other)
            // return *this;
            throw std::logic_error("Self Movement error");
        id = other.id;
        other.id = -id;
        value = other.value;
        pointer = other.pointer;
        other.pointer = nullptr;
    }
    Element &operator=(Element &&other)
    {
        // std::cout << "Move Assignment " << id << std::endl;
        if (this == &other)
            // return *this;
            throw std::logic_error("Self Movement error");
        id = other.id;
        other.id = -id;
        value = other.value;
        if (pointer && *pointer != *other.pointer)
        {
            delete pointer;
            pointer = other.pointer;
            other.pointer = nullptr;
        }
        return *this;
    }

    ~Element() noexcept
    {
        // std::cout << "Deconstructed " << id << std::endl;
        if (pointer)
            delete pointer;
    }

    bool operator==(const Element &other) const
    {
        return value == other.value && *pointer == *other.pointer;
    }

public:
};
template <typename T>
std::ostream &operator<<(std::ostream &os, const Element<T> &element)
{
    os << element.id << ':' << element.value << ',' << *element.pointer;
    return os;
}
