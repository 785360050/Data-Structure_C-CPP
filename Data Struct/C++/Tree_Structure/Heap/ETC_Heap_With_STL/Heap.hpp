#include <algorithm>


/// ============================================================================================================
/// 		algorithm中的heap接口
/// ============================================================================================================
/// make_heap(begin,end)    将begin,end范围中的元素调整为堆
/// push_heap(begin,end)    将end-1(末尾)元素插入到堆中，实际上就是堆的自调整
/// pop_heap(begin,end)     将堆顶元素移到末尾元素位置，执行后需要底层容器再处理
/// sort_heap(begin,end)    将范围中的元素升序排序，这不和std::sort一样吗
/// is_heap(begin,end)      判断是否为堆
/// is_heap_until(begin,end)    查找满足堆性质的最大范围，返回iterartor:end表示从begin到end为堆
/// ============================================================================================================

#include <vector>
#include <exception>

namespace STD
{



template <typename ElementType>
class Heap
{
private:
    std::vector<ElementType> heap{};

public:
    Heap()
    {
        std::cout << "Default Constructed " << std::endl;

    }
    Heap(std::initializer_list<ElementType> init)
    {
        heap = init;
        std::make_heap(heap.begin(), heap.end());
        if (!Is_Heap())
            throw std::runtime_error("Make heap Failed!");
    }

    Heap(const Heap &other)
    {
        std::cout << "Copy Constructed " << std::endl;
        heap=other.heap;
    }
    Heap operator=(const Heap &other)
    {
        std::cout << "Copy Assignment " << std::endl;
        heap = other.heap;
    }

    Heap(Heap &&other)
    {
        std::cout << "Move Constructed " << std::endl;
        std::swap(heap, other.heap);
    }

    
    ~Heap() noexcept
    {
        std::cout << "Deconstructed " << std::endl;
    }
public:
    void Element_Push(ElementType element)
    {
        heap.emplace_back(element);
        std::push_heap(heap.begin(), heap.end());
    }
    void Element_Pop()
    {
        std::pop_heap(heap.begin(), heap.end());
        heap.pop_back();
    }
    ElementType Heap_Top()
    {
        return heap[0];
    }

    bool Is_Heap() { return std::is_heap(heap.begin(), heap.end()); }

    void Show(const std::string& info="")
    {
        std::cout << "[ " << info << " ]" << std::endl;
        for (const auto& e: heap) 
            std::cout << e << ' ';
        std::cout << std::endl;
    }
};


}