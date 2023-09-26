
#include <concepts>


namespace ADT
{
	template <typename StructureType, typename ElementType>
	concept Liner_Sequential_List = requires(StructureType adt, ElementType element, std::size_t index) {
		adt.Is_Empty();
		adt.Size();
		adt.Capcity();
		adt.Clear();

		adt.Element_Insert(index, element);
		adt.Element_Delete(index);
		adt[index];
		adt.Element_Update(index, element);
	};
};