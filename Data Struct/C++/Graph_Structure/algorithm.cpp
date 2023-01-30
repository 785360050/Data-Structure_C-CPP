//
//#include <Windows.h>
//static bool  SetEncode(int EncodeId = 936)
//{
//	/// <summary>
//	/// EncodeId 是代码页，设置它等于设置我们指定的编码格式。
//	///	默认936为unicode编码
//	/// SetConsoleCP() 设置控制台输入时使用的编码。
//	///	SetConsoleOutputCP() 设置控制台输出时使用的编码。
//	/// </summary>
//	/// <param name="EncodeId"></param>
//	/// <returns></returns>
//	return SetConsoleCP(EncodeId) && SetConsoleOutputCP(EncodeId);
//}
//
//
//
//void TestMininumSpanningTree()
//{
//
//	/// Kruskal用边集数组存储方便
//	//int Sum = Graph_MininumSpanningTree_Kruskal(g, edgeset, 8, result);
//	//std::cout << "最小生成树权值为：" << Sum << std::endl;
//
//	Graph_matrix* g = new Graph_matrix;
//	Graph_Init(g, 7, false);//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
//	Graph_Edge_Add(g, 0, 1, 12);
//	Graph_Edge_Add(g, 0, 5, 16);
//	Graph_Edge_Add(g, 0, 6, 14);
//	Graph_Edge_Add(g, 1, 2, 10);
//	Graph_Edge_Add(g, 1, 5, 7);
//	Graph_Edge_Add(g, 6, 5, 9);
//	Graph_Edge_Add(g, 6, 4, 8);
//	Graph_Edge_Add(g, 5, 4, 2);
//	Graph_Edge_Add(g, 5, 2, 6);
//	Graph_Edge_Add(g, 2, 4, 5);
//	Graph_Edge_Add(g, 2, 3, 3);
//	Graph_Edge_Add(g, 3, 4, 4);
//
//
//	Graph_Show_Matrix(g);
//
//	Graph_matrix* minimum = Graph_MininumSpanningTree_Prim(*g, 0);
//	std::cout << "获得的最小生成树为：" << std::endl;
//	Graph_Show_Matrix(minimum);
//	Graph_Destroy(g);
//	Graph_Destroy(minimum);
//}
//
//void TestShortestPath()
//{
//	Graph_matrix* g = new Graph_matrix;
//	Graph_Init(g, 7, true);
//	Graph_Edge_Add(g, 0, 1, 4);
//	Graph_Edge_Add(g, 0, 2, 6);
//	Graph_Edge_Add(g, 0, 3, 6);
//	Graph_Edge_Add(g, 1, 2, 1);
//	Graph_Edge_Add(g, 1, 4, 7);
//	Graph_Edge_Add(g, 2, 4, 6);
//	Graph_Edge_Add(g, 2, 5, 4);
//	Graph_Edge_Add(g, 3, 2, 2);
//	Graph_Edge_Add(g, 3, 5, 5);
//	Graph_Edge_Add(g, 4, 6, 6);
//	Graph_Edge_Add(g, 5, 4, 1);
//	Graph_Edge_Add(g, 5, 6, 8);
//
//	Graph_Show_Matrix(g);
//	ShortestPath_Dijkstra(*g, 0);
//}
//
//void TestTopoSort()
//{
//	AdjacencyList* g = new AdjacencyList;
//	Graph_AdjacencyList_Init(g, 6, true);
//	Graph_AdjacencyList_Edge_Add(g, 0, 1, 1);
//	Graph_AdjacencyList_Edge_Add(g, 0, 2, 1);
//	Graph_AdjacencyList_Edge_Add(g, 0, 3, 1);
//	Graph_AdjacencyList_Edge_Add(g, 2, 1, 1);
//	Graph_AdjacencyList_Edge_Add(g, 2, 4, 1);
//	Graph_AdjacencyList_Edge_Add(g, 3, 4, 1);
//	Graph_AdjacencyList_Edge_Add(g, 5, 3, 1);
//	Graph_AdjacencyList_Edge_Add(g, 5, 4, 1);
//
//	Graph_Show_AdjacencyList(g);
//	TopoSort(g);
//}
//
//void TestCriticalPath()
//{
//	AdjacencyList* g = new AdjacencyList;
//	Graph_AdjacencyList_Init(g, 9, true);//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
//
//	Graph_AdjacencyList_Edge_Add(g, 0, 1, 6);
//	Graph_AdjacencyList_Edge_Add(g, 0, 2, 4);
//	Graph_AdjacencyList_Edge_Add(g, 0, 3, 5);
//	Graph_AdjacencyList_Edge_Add(g, 1, 4, 1);
//	Graph_AdjacencyList_Edge_Add(g, 2, 4, 1);
//	Graph_AdjacencyList_Edge_Add(g, 3, 5, 2);
//	Graph_AdjacencyList_Edge_Add(g, 4, 6, 9);
//	Graph_AdjacencyList_Edge_Add(g, 4, 7, 7);
//	Graph_AdjacencyList_Edge_Add(g, 5, 7, 4);
//	Graph_AdjacencyList_Edge_Add(g, 6, 8, 2);
//	Graph_AdjacencyList_Edge_Add(g, 7, 8, 4);
//	std::cout << "当前图的邻接表为：" << std::endl;
//	Graph_Show_AdjacencyList(g);
//
//	std::cout << "当前图的拓扑排序为：" << std::endl;
//	Graph_CriticalPath(g);
//
//	delete[] g->vertex;
//	delete g;
//}
//
//
//void main()
//{
//	SetEncode(65001);//设置控制台为utf-8编码格式
//
//}
//
