


#include <concepts>
template <typename StructureType>
concept Liner_Structure = requires(StructureType adt) 
{
	{adt.Empty()}->std::same_as<bool>;
	
};

template<typename DataType >
struct cls
{
    bool Empty()
    {return true;}
};


#include <cassert>
int main(int argc, char const *argv[])
{
    static_assert(Liner_Structure<cls<int>>);

    return 0;
}
