#pragma once

#include <iostream>

static int counter{}; // 用于标记Element的id，拷贝和移动操作不计入

template <typename DataType = int>
struct Element
{
public:
    // 所有copy和move的元素id都相同,区别于id_copy和id_move
    int id{counter++};
    int id_copy{0}; // 记录copy次数，被拷贝的原始id_copy为0，每拷贝一次+1，用于区分相同id的不同拷贝副本
    int id_move{0}; // 记录move次数，被移动的原始id_move为0，移动一次后，移动目标的id_move+1

public:
    DataType value{};
    // 对于所有构造、赋值都会默认申请空间。如果不在此处初始化，则下面的拷贝控制需要微调

    // 拷贝控制时双方指针内容的判定逻辑(以copy为例)
    // 1. 双方都没有，无操作
    // 2. 对方有，我方没有，我方申请空间并拷贝
    // 3. 对方没有，我方有，我方释放空间
    // 4. 双方都有,我方直接覆盖指针内容
    DataType *pointer{nullptr}; // 指针

public:
    Element()
    {
        std::cout << "Default Constructed " << *this << std::endl;
    }
    Element(DataType value, DataType value_pointer) : value{value}
    {
        pointer = new DataType(value_pointer);
        std::cout << "Pramater Constructed " << *this << std::endl;
    }

    Element(const Element &other)
    {
        if (this == &other)
            // return *this;
            throw std::logic_error("Self copy error");

        id = other.id;
        counter--; // 取消本次的构造计数
        id_copy = other.id_copy + 1;
        id_move = other.id_move;
        value = other.value;

        if (!other.pointer && this->pointer)
        {
            delete this->pointer;
            this->pointer = nullptr;
        }
        else if (!other.pointer && !this->pointer)
        {
            std::cout << "Copy Constructed " << *this << " from " << other << std::endl;
            return;
        }
        else if (other.pointer && this->pointer)
            *pointer = *other.pointer;
        else if (other.pointer && !this->pointer)
            pointer = new DataType(*other.pointer);
        else
            throw std::logic_error("Copy Control Logic Error");
        std::cout << "Copy Constructed " << *this << " from " << other << std::endl;
    }
    Element &operator=(const Element &other)
    {
        if (this == &other)
            // return *this;
            throw std::logic_error("Self copy error");

        id = other.id;
        counter--; // 取消本次的构造计数
        id_copy = other.id_copy + 1;
        id_move = other.id_move;
        value = other.value;

        if (!other.pointer && this->pointer)
        {
            delete this->pointer;
            this->pointer = nullptr;
        }
        else if (!other.pointer && !this->pointer)
        {
            std::cout << "Copy Assignment " << *this << " from " << other << std::endl;
            return *this;
        }
        else if (other.pointer && this->pointer)
            *pointer = *other.pointer;
        else if (other.pointer && !this->pointer)
            pointer = new DataType(*other.pointer);
        else
            throw std::logic_error("Copy Control Logic Error");

        std::cout << "Copy Assignment " << *this << " from " << other << std::endl;
        return *this;
    }

    /// ============================================================================================================
    /// 		移动语义的日志显示from Element时仅显示被移动后的结果
    /// 如要要显示被移动前的数据需要保存temp,涉及到一次拷贝构造，影响日志输出，所以没加
    /// ============================================================================================================

    Element(Element &&other)
    {
        if (this == &other)
            // return *this;
            throw std::logic_error("Self Movement error");

        // auto temp = other; // 用于输出日志，会导致一次拷贝构造
        id = other.id;
        counter--; // 取消本次的构造计数
        id_copy = other.id_copy;
        id_move = other.id_move + 1;
        // other.id = -id;
        value = other.value;

        if (!other.pointer && this->pointer)
        {
            delete this->pointer;
            this->pointer = nullptr;
        }
        else if (!other.pointer && !this->pointer)
        {
            std::cout << "Move Constructed " << *this << " from " << other << std::endl;
            return;
        }
        else if (other.pointer && this->pointer)
        {
            delete pointer;
            pointer = other.pointer;
            other.pointer = nullptr;
        }
        else if (other.pointer && !this->pointer)
        {
            pointer = other.pointer;
            other.pointer = nullptr;
        }
        else
            throw std::logic_error("Copy Control Logic Error");
        std::cout << "Move Constructed " << *this << " from " << other << std::endl;
    }
    Element &operator=(Element &&other)
    {

        if (this == &other)
            // return *this;
            throw std::logic_error("Self Movement error");

        // auto temp = other; // 用于输出日志，会导致一次拷贝构造
        id = other.id;
        counter--; // 取消本次的构造计数
        // other.id = -id;
        id_copy = other.id_copy;
        id_move = other.id_move + 1;
        value = other.value;

        if (!other.pointer && this->pointer)
        {
            delete this->pointer;
            this->pointer = nullptr;
        }
        else if (!other.pointer && !this->pointer)
        {
            std::cout << "Move Assignment " << *this << " from " << other << std::endl;
            return *this;
        }
        else if (other.pointer && this->pointer)
        {
            delete pointer;
            pointer = other.pointer;
            other.pointer = nullptr;
        }
        else if (other.pointer && !this->pointer)
        {
            pointer = other.pointer;
            other.pointer = nullptr;
        }
        else
            throw std::logic_error("Copy Control Logic Error");

        std::cout << "Move Assignment " << *this << " from " << other << std::endl;
        return *this;
    }

    ~Element() noexcept
    {
        std::cout << "Deconstructed " << *this;
        if (pointer)
        {
            delete pointer;
            std::cout << " pointer deleted";
        }
        std::cout << std::endl;
    }

    /// @brief 指针成员比较的是指针指向的值,而不是指针存的地址
    bool operator==(const Element &other) const
    {

        return
            // 比较值成员
            value == other.value &&
            // 比较指针成员：
            // 如果一个指针有效一个无效，则不相同
            // 如果指针都无效，或都有效且指向元素值相同，则相同
            (!pointer ? !other.pointer : *pointer == *other.pointer);
    }

public:
    auto operator<=>(const Element &other) const
    {//比较原则同operator==
        auto compare_value = value <=> other.value;

        if (compare_value != std::strong_ordering::equal)
            return compare_value;

        if (!pointer)
            return other.pointer ? std::strong_ordering::less : std::strong_ordering::equal;
        else if (!other.pointer)
            return std::strong_ordering::greater;
        else
            return *pointer <=> *other.pointer;
    }
};
template <typename T>
std::ostream &operator<<(std::ostream &os, const Element<T> &element)
{
    os << '[' << element.id << '-' << element.id_copy << '-' << element.id_move << "]:{" << element.value << ',';
    if (!element.pointer)
        os << "Null}";
    else
        os << *element.pointer << '}';
    return os;
}
