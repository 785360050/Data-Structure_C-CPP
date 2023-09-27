/// ============================================================================================================
/// 		这些接口类意图就是用于规范接口
/// c++20中有专门的特性表示抽象数据类型ADT : concept
/// ============================================================================================================



#include <concepts>
template <typename StructureType>
concept Liner_Structure = requires(StructureType adt) {
    {
        adt.Empty()
    } -> std::same_as<bool>;
};

#include <vector>
template <typename T>
concept Hashable = requires(T a) {
    {
        std::vector<T>{}(a)
    } -> std::convertible_to<std::size_t>;
};
