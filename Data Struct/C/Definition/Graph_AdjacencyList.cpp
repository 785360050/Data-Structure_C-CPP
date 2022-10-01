#include "../API/Graph_AdjacencyList.h"

void Graph_AdjacencyList_Init(AdjacencyList* graph, int num_vertex, bool directed)
{
	graph->directed = directed;
	graph->num_vertex = num_vertex;
	graph->num_edge = 0;
	memset(graph->vertex, 0, sizeof(graph->vertex));
	for (int i = 0; i < num_vertex; i++)
	{
		graph->vertex[i].index = i;
		graph->vertex[i].name = 'A' + i;
		graph->vertex[i].head = nullptr;
	}
}
static int Index(Vertex_AdjacencyList vertex)
{
	return vertex.index;
}
static Edge_Adj* Create_EdgeNode(int index, int weight)
{
	Edge_Adj* node = (Edge_Adj*)malloc(sizeof(Edge_Adj));
	node->index_vertex = index;
	node->weight = weight;
	node->next = nullptr;
	return node;
}
void Graph_AdjacencyList_Edge_Add(AdjacencyList* graph, int x, int y, int weight)
{
	try
	{
		if (x < 0 || Index(x) >= graph->num_vertex)
			throw 1;
		if (y < 0 || Index(y) >= graph->num_vertex)
			throw 2;
	}
	catch (int a)
	{
		if (a == 1)
		{
			std::cout << "Index X is out of range!" << std::endl;
			return;
		}
		if (a == 2)
		{
			std::cout << "Index Y is out of range!" << std::endl;
			return;
		}
	}
	Edge_Adj* node = Create_EdgeNode(y, weight);
	node->next = graph->vertex[x].head;///头插法插入新节点
	graph->vertex[x].head = node;
	graph->num_edge++;
	if (x != y && graph->directed == true)
	{///无向图新建插入两个节点
		node = Create_EdgeNode(x, weight);
		node->next = graph->vertex[y].head;///头插法插入新节点
		graph->vertex[y].head = node;
		graph->num_edge++;
	}
}



























