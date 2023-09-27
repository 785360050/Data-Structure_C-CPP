#include "Sequential_List.hpp"

//有Bug 不想写了
int main(int argc, char const *argv[])
{
    Sequential_List_Static<int, 5> array;
    array.List_Show("Init");
    std::cout << array.Size() << std::endl;
    std::cout << array.Capcity() << std::endl;

    for (size_t i = 0; i < 5; i++)
        // array[i] = i;//不要用这个，不会修改size
        array.Element_Insert(i, i);

    array.Element_Delete(0);
    array.List_Show("delete index 0");
    array.Element_Insert(array.Size() - 1,99);
    array.List_Show("Insert 99 at end");

    return 0;
}
