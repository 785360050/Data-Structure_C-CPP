
#include <iostream>
#include <random>
#include <map>
#include <vector>

 #include <concepts>
 #include <functional>

 template <typename Method,typename Compare=std::less<>>
 concept Sort_Method = requires(Method method, std::vector<size_t> list) {
     // std::invocable<Method>;
     std::invoke(method, list,Compare{});
 };

void Swap(size_t& x,size_t& y)
{
    x = x ^ y;
    y = x ^ y;
    x = x ^ y;
}

template <size_t count,size_t min, size_t max>
struct Test_Case
{
    std::vector<size_t> values;
    std::map<size_t,size_t> counter;

public:
    Test_Case()
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<unsigned int> distribution(min,max);

        values.reserve(count);
        for (int i = 0; i < count; ++i)
        {
            size_t value = distribution(generator);
            values.emplace_back(value);
            counter[value]++;
        }
    }

// 拷贝待排序的数组给排序函数对象，处理完成后返回排序后的结果
    template <typename ElementType,Sort_Method Method>
    std::vector<size_t> Sort() const
    {
		Method< ElementType> method{};
        return method(std::vector<size_t>(values));//copy array
    }
    void Show() const
    {
        for (const auto& num: values) 
            std::cout << num << ' ';
        std::cout << std::endl;
        for (const auto &num : counter)
            std::cout << num.first << " : " << num.second << std::endl;
    }
    void Show_Result(std::vector<size_t> list, const std::string &info = "") const
    {
        if (!info.empty())
            std::cout << "[ " << info << " ]" << std::endl;
        for (const auto &num : list)
            std::cout << num << ' ';
        std::cout << std::endl;
    };
};



namespace Sort
{
    template <typename ElementType, typename Compare = std::less<>>
    struct Insert_Directly
    {
        std::vector<size_t> operator()(std::vector<size_t>& list,Compare compare=Compare{})
        {
            for (int i = 1; i < list.size(); i++)
                for (int n = i; n > 0; --n)
                    if (compare(list[n - 1], list[n]))
                        Swap(list[n - 1], list[n]);
            return list;
        };
        std::vector<size_t> operator()(std::vector<size_t> &&list_move, Compare compare = Compare{})
        {
            auto list = list_move;
            for (int i = 1; i < list.size(); i++)
                for (int n = i; n > 0; --n)
                    if (list[n - 1] > list[n])
                        Swap(list[n - 1], list[n]);
            return list;
        };
    };

} // namespace Sort


// void Sort_Insert_Direct(SortList *list)
// {
//     for (int i = 1; i < list->length; i++)
//         for (int n = i; n > 0; n--)
//             if (list->data[n - 1].key > list->data[n].key)
//                 Element_Swap(&list->data[n], &list->data[n - 1]);
// }

int main(int argc, char const *argv[])
{
    constexpr size_t min = 0, max = 10, count = 10;
     static_assert(Sort_Method<Sort::Insert_Directly<size_t>>);

    const Test_Case<count,min, max> list;
    list.Show();


    auto res=list.Sort<Sort::Insert_Directly>();
    list.Show_Result(res, "Insert Directly Sort");


    // demo
    std::vector<int> arr = {1, 2, 3, 4, 5, 6};
    Sort::Insert_Directly<int> method;
    std::vector<size_t> result = method(std::vector<int>(arr));
    for (const auto &x : result)
        std::cout << x << ' ';
    std::cout << std::endl;
    return 0;
}
