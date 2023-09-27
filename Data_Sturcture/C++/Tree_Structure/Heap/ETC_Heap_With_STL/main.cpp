#include <vector>
#include <list>
#include <iostream>



/// ============================================================================================================
/// 	    算法库中的heap相关算法，详见自制的Heap封装，Heap.hpp
/// ============================================================================================================
#include <vector>
#include <algorithm>
void Show_Heap(const std::vector<int>& ivec,const std::string& msg="")
{
    std::cout<<msg<<std::endl;
    for (int i = 0; i < ivec.size(); ++i)
        std::cout << ivec[i] << " ";
    std::cout << std::endl;
}
void Test_Heap()
{
    using namespace std;
    { // test heap (以vector完成)
        int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
        std::vector<int> ivec(ia, ia + 9);

        make_heap(ivec.begin(), ivec.end());
        Show_Heap(ivec,"make_heap to initialize a heap in vector");
        std::cout << "After initialized, is Heap? " << std::boolalpha << std::is_heap(ivec.begin(), ivec.end()) << std::endl;

        ivec.push_back(7);
        Show_Heap(ivec, "push_back element in vector");
        push_heap(ivec.begin(), ivec.end());
        Show_Heap(ivec, "push_heap to maintain heap");

        pop_heap(ivec.begin(), ivec.end());
        Show_Heap(ivec, "pop_heap bring top element to the last position of element");
        std::cout << "access last element which is the top,and then remove it" << std::endl;
        cout << ivec.back() << endl;
        ivec.pop_back();

        sort_heap(ivec.begin(), ivec.end());
        Show_Heap(ivec, "sort_heap to break the heap");

        std::cout<<"After Sorted, is Heap? "<<std::boolalpha<<std::is_heap(ivec.begin(), ivec.end())<<std::endl;
    }
}


/// ============================================================================================================
/// 		自制的Heap
/// ============================================================================================================
#include "Heap.hpp"
void Heap_Demo()
{
    STD::Heap heap{1, 9, 132, 54, 945, 5464, 8, 6143, 4};
    heap.Show("Heap initialized");

    heap.Element_Push(22);
    heap.Show("Push 22");

    std::cout << "Current Heap Top = " << heap.Heap_Top() << std::endl;

    heap.Element_Pop();
    heap.Show("Pop top");
}



/// ============================================================================================================
/// 		std::priority_queue
/// ============================================================================================================
template <typename DataType>
struct Priority
{
    bool operator()(const DataType& lhs,const DataType& other)
    {return lhs>other;}
};

#include <queue>

template <typename Compare_Functor>
void Show_Heap(const std::priority_queue<int, std::vector<int>, Compare_Functor> &heap, const std::string &msg = "")
{
    std::cout << msg << std::endl;
    auto temp = heap;
    while (!temp.empty())
    {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}
void Test_PriorityQueue()
{
    std::priority_queue<int, std::vector<int>, Priority<int>> heap;//使用自制的Funtor用于比较，实现小根堆
    for (auto x : {1, 9, 132, 54, 945, 5464, 8, 6143, 4})
        heap.push(x);
    Show_Heap(heap, "init");
    heap.push(2);

    std::cout << "Top = " << heap.top() << std::endl;

    heap.pop();
    Show_Heap(heap, "pop");
    std::priority_queue<int, std::vector<int>> max_heap;//默认调用std::less，所以是大根堆实现
    while (!heap.empty())
    {
        max_heap.push(heap.top());
        heap.pop();
    }

    Show_Heap(max_heap, "Convert into min heap");
}

int main(int argc, char const *argv[])
{
    Test_Heap();
    Heap_Demo();
    Test_PriorityQueue();
    return 0;
}
