
#include "Graph_Structure.h"

#include "Graph_Matrix/Graph_Matrix.h"
#include "Graph_Matrix/Vertex_Matrix.h"
#include "Graph_AdjacencyList/Graph_AdjacencyList.h"
#include "Graph_EdgeSetList/Graph_EdgeSetList.h"

#include <Windows.h>
static bool  SetEncode(int EncodeId = 936)
{
	/// <summary>
	/// EncodeId 是代码页，设置它等于设置我们指定的编码格式。
	///	默认936为unicode编码
	/// SetConsoleCP() 设置控制台输入时使用的编码。
	///	SetConsoleOutputCP() 设置控制台输出时使用的编码。
	/// </summary>
	/// <param name="EncodeId"></param>
	/// <returns></returns>
	return SetConsoleCP(EncodeId) && SetConsoleOutputCP(EncodeId);
}


void TestMatrixGraph()
{
	//初始化8个节点的无向无权图，用邻接矩阵graph存储,初始无边(weight=0)
	Graph_Matrix<int> graph(false,8);
	graph.Graph_Edge_Add(0, 1, 1);
	graph.Graph_Edge_Add(0, 2, 1);
	graph.Graph_Edge_Add(1, 3, 1);
	graph.Graph_Edge_Add(1, 4, 1);
	graph.Graph_Edge_Add(2, 5, 1);
	graph.Graph_Edge_Add(2, 6, 1);
	graph.Graph_Edge_Add(3, 7, 1);
	graph.Graph_Edge_Add(4, 7, 1);
	graph.Graph_Edge_Add(5, 6, 1);


	graph.Graph_Show();

	std::cout << "DFS" << std::endl;
	graph.Graph_Traverse_DFS(0);
	std::cout << std::endl << "BFS" << std::endl;
	graph.Graph_Traverse_BFS(0);

}

void TestAdjacencyListGraph()
{
	//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
	Graph_AdjacencyList<int> graph(false,8);
	graph.Graph_Edge_Add(0, 1, 1);
	graph.Graph_Edge_Add(0, 2, 1);
	graph.Graph_Edge_Add(1, 3, 1);
	graph.Graph_Edge_Add(1, 4, 1);
	graph.Graph_Edge_Add(3, 7, 1);
	graph.Graph_Edge_Add(4, 7, 1);
	graph.Graph_Edge_Add(2, 6, 1);
	graph.Graph_Edge_Add(2, 5, 1);
	graph.Graph_Edge_Add(5, 6, 1);

	graph.Graph_Show();

	std::cout << "DFS" << std::endl;
	graph.Graph_Traverse_DFS(0);
	//graph.Reset_VistedState();
	std::cout << std::endl << "BFS" << std::endl;
	graph.Graph_Traverse_BFS(0);

}

void TestEdgeSetListGraph()
{
	//初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
	Graph_EdgeSet<int> graph(false, 8);
	graph.Graph_Edge_Add(0, 1, 1);
	graph.Graph_Edge_Add(0, 2, 1);
	graph.Graph_Edge_Add(1, 3, 1);
	graph.Graph_Edge_Add(1, 4, 1);
	graph.Graph_Edge_Add(3, 7, 1);
	graph.Graph_Edge_Add(4, 7, 1);
	graph.Graph_Edge_Add(2, 6, 1);
	graph.Graph_Edge_Add(2, 5, 1);
	graph.Graph_Edge_Add(5, 6, 1);

	graph.Graph_Show();

	//std::cout << "DFS" << std::endl;
	//graph.Graph_Traverse_DFS(0);
	//graph.Reset_VistedState();
	//std::cout << std::endl << "BFS" << std::endl;
	//graph.Graph_Traverse_BFS(0);

}




#define directed	
void TestPolymorphic()
{
#ifndef directed	///无向图
	//Graph_Structure<Vertex_Matrix<int>,int>* graph=new Graph_Matrix<int>(false, 8);
	//Graph_Structure<Vertex_AdjacencyList<int>,int>* graph=new Graph_AdjacencyList<int>(false, 8);
	Graph_Structure<int,int>* graph=new Graph_EdgeSet<int>(false, 8);
	graph->Graph_Edge_Add(0, 1, 1);
	graph->Graph_Edge_Add(0, 2, 1);
	graph->Graph_Edge_Add(1, 3, 1);
	graph->Graph_Edge_Add(1, 4, 1);
	graph->Graph_Edge_Add(2, 5, 1);
	graph->Graph_Edge_Add(2, 6, 1);
	graph->Graph_Edge_Add(3, 7, 1);
	graph->Graph_Edge_Add(4, 7, 1);
	graph->Graph_Edge_Add(5, 6, 1);


	graph->Graph_Show();

	std::cout << "DFS" << std::endl;
	graph->Graph_Traverse_DFS(0);
	std::cout << std::endl << "BFS" << std::endl;
	graph->Graph_Traverse_BFS(0);
#endif // !directed

#ifdef directed		///有向图
	Graph_Structure<Vertex_Matrix<int>,int>* graph=new Graph_Matrix<int>(true, 7);
	//Graph_Structure<Vertex_AdjacencyList<int>,int>* graph=new Graph_AdjacencyList<int>(true, 7);
	//Graph_Structure<int, int>* graph = new Graph_EdgeSet<int>(true, 7);
	graph->Graph_Edge_Add(0, 1, 4);
	graph->Graph_Edge_Add(0, 2, 6);
	graph->Graph_Edge_Add(0, 3, 6);
	graph->Graph_Edge_Add(1, 2, 1);
	graph->Graph_Edge_Add(1, 4, 7);
	graph->Graph_Edge_Add(2, 4, 6);
	graph->Graph_Edge_Add(2, 5, 4);
	graph->Graph_Edge_Add(3, 2, 2);
	graph->Graph_Edge_Add(3, 5, 5);
	graph->Graph_Edge_Add(4, 6, 6);
	graph->Graph_Edge_Add(5, 4, 1);
	graph->Graph_Edge_Add(5, 6, 8);

	graph->Graph_Show();

	std::cout << "DFS" << std::endl;
	graph->Graph_Traverse_DFS(0);
	std::cout << std::endl << "BFS" << std::endl;
	graph->Graph_Traverse_BFS(0);
#endif // directed
	delete graph;
}


void main()
{
	SetEncode(65001);//设置控制台为utf-8编码格式
	//TestMatrixGraph();
	//TestAdjacencyListGraph();
	//TestEdgeSetListGraph();
	TestPolymorphic();
}

