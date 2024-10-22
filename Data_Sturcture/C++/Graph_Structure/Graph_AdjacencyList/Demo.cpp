#include "Graph_AdjacencyList.hpp"



int main(int argc, char const *argv[])
{
    // 初始化8个节点的无向无权图，用邻接矩阵g存储,初始无边(weight=0)
    Storage::Graph_AdjacencyList<int,false> graph;


    graph.Vertex_Add("a", 0);
    graph.Vertex_Add("b", 1);
    graph.Vertex_Add("c", 2);
    graph.Vertex_Add("d", 3);
    graph.Vertex_Add("e", 4);
    graph.Vertex_Add("f", 5);
    graph.Vertex_Add("g", 6);
    graph.Vertex_Add("h", 7);

    graph.Edge_Add("a", "b", 1);
    graph.Edge_Add("a", "c", 1);
    graph.Edge_Add("b", "d", 1);
    graph.Edge_Add("b", "e", 1);
    graph.Edge_Add("d", "h", 1);
    graph.Edge_Add("e", "h", 1);
    graph.Edge_Add("c", "g", 1);
    graph.Edge_Add("c", "f", 1);
    graph.Edge_Add("f", "g", 1);

    graph.Show();

    // std::cout << "DFS" << std::endl;
    // graph.Traverse_DFS(0);
    // // graph.Reset_VistedState();
    // std::cout << std::endl << "BFS" << std::endl;
    // graph.Traverse_BFS(0);

    return 0;
}
