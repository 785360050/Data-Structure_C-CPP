#include "Search_Tree.hpp"





Painter::Search_Tree::Search_Tree()
{
	// auto a = tree.Node_Create("8");
	// auto b = tree.Node_Create("5");
	// auto c = tree.Node_Create("15");
	// auto d = tree.Node_Create("12");
	// auto e = tree.Node_Create("19");
	// auto f = tree.Node_Create("9");
	// auto g = tree.Node_Create("13");
	// auto h = tree.Node_Create("23");

	// // tree.Tree_Set_Root(a);

	// container.Set_Level(4);
	// container.Set(a,1,0);
	// container.Set(b,2,0);
	// container.Set(c,2,1);
	// container.Set(d,3,2);
	// container.Set(e,3,3);
	// container.Set(f,4,4);
	// container.Set(g,4,5);
	// container.Set(h,4,7);
	tree.Element_Insert_NonRecursive(4);
	tree.Element_Insert_NonRecursive(2);
	tree.Element_Insert_NonRecursive(1);
	tree.Element_Insert_NonRecursive(3);
	tree.Element_Insert_NonRecursive(6);
	tree.Element_Insert_NonRecursive(5);
	tree.Element_Insert_NonRecursive(7);

	// tree.Element_Delete(2);
	// tree.Element_Delete(4);
	std::cout << "Depth = " + std::to_string(tree.Get_Depth(tree.root)) << std::endl;

	container=tree.Capture_Snapshot();
	drawer.Update_Tree(container);

}


