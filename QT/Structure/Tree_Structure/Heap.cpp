
#include "Heap.hpp"




Painter::Heap::Heap()
{
	for (int i = 1; i <= 10; ++i)
		heap.Push(i);


	for (int i = 0; i < 5; ++i)
		heap.Pop();

	container=heap.Capture_Snapshot();
	drawer.Update_Tree(container);
}

void Painter::Heap::Element_Push(int element)
{
	heap.Push(element);
	container=heap.Capture_Snapshot();
	drawer.Update_Tree(container);
}

void Painter::Heap::Element_Pop()
{
	heap.Pop();
	container=heap.Capture_Snapshot();
	drawer.Update_Tree(container);
}

int Painter::Heap::Get_Top()
{
	return heap.Get_Top();
}

