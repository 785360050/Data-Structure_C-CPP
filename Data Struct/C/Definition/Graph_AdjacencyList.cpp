#include "../API/Graph_AdjacencyList.h"
#include <queue>
#include "../API/Liner_Queue.h"

void Graph_AdjacencyList_Init(AdjacencyList* graph, int num_vertex, bool directed)
{
	graph->directed = directed;
	graph->num_vertex = num_vertex;
	graph->num_edge = 0;
	graph->state_visited = new bool[num_vertex];
	graph->vertex = new AdjacencyList_Vertex[num_vertex];
	Reset_VistedState(graph);
	memset(graph->vertex, 0, sizeof(AdjacencyList_Vertex)* num_vertex);
	for (int i = 0; i < num_vertex; i++)
	{
		graph->vertex[i].no = i;
		//graph->vertex[i].name = 'A' + i;
		graph->vertex[i].head_edge = nullptr;
	}
}

void Graph_AdjacencyList_Destroy(AdjacencyList* graph)
{
	try
	{
		if (!graph)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Destroy Failed: Graph is not exist!" << std::endl;
		return;
	}
	delete[] graph->state_visited;
	delete[] graph->vertex;
	delete graph;
}

static int Index(Vertex_AdjacencyList vertex)
{
	return vertex.no;
}
static Edge_Adj* Create_EdgeNode(int index, int weight)
{
	Edge_Adj* node = (Edge_Adj*)malloc(sizeof(Edge_Adj));
	node->index_vertex = index;
	node->weight = weight;
	node->next = nullptr;
	return node;
}
void Graph_AdjacencyList_Edge_Add(AdjacencyList* graph, int no_origin, int no_destination, int weight)
{
	try
	{
		if (no_origin < 0 || no_origin >= graph->num_vertex)
			throw 1;
		if (no_destination < 0 || no_destination >= graph->num_vertex)
			throw 2;
	}
	catch (int a)
	{
		if (a == 1)
		{
			std::cout << "Index no_origin is out of range!" << std::endl;
			return;
		}
		if (a == 2)
		{
			std::cout << "Index no_destination is out of range!" << std::endl;
			return;
		}
	}
	Edge_Adj* node = Create_EdgeNode(no_destination, weight);
	node->next = graph->vertex[no_origin].head_edge;///头插法插入新节点
	graph->vertex[no_origin].head_edge = node;
	graph->num_edge++;
	if (no_origin != no_destination && graph->directed == false)
	{///无向图新建插入两个节点
		node = Create_EdgeNode(no_origin, weight);
		node->next = graph->vertex[no_destination].head_edge;///头插法插入新节点
		graph->vertex[no_destination].head_edge = node;
	}
}


void Graph_AdjacencyList_Traverse_DFS(AdjacencyList* graph, int no_vertex)
{
	
	Edge_Adj* e;
	std::cout << graph->vertex[no_vertex].no << ' ';
	graph->state_visited[no_vertex] = true;
	e = graph->vertex[no_vertex].head_edge;
	while (e)
	{
		if (graph->state_visited[e->index_vertex] == false)
			Graph_AdjacencyList_Traverse_DFS(graph, graph->vertex[e->index_vertex].no);
		e = e->next;
	}

}


void Graph_AdjacencyList_Traverse_BFS(AdjacencyList* graph, int no_vertex)
{

	Reset_VistedState(graph);
#define Standard_Queue
#ifdef Standard_Queue
	std::queue<int> q;
	q.push(no_vertex);
	while (!q.empty())
	{

		int x = q.front();
		std::cout << x << ' ';
		q.pop();
		graph->state_visited[x] = true;
		Edge_Adj* e = graph->vertex[x].head_edge;
		while (e)
		{///下一层全入队
			if (graph->state_visited[e->index_vertex] == false)
			{
				q.push(e->index_vertex);
				graph->state_visited[e->index_vertex] = true;
			}
			e = e->next;
		}
	}
#endif // Standard_Queue


}

void Graph_Show_AdjacencyList(AdjacencyList* graph)
{
	using namespace std;
	string d = graph->directed == true ? "有向图" : "无向图";
	cout << "顶点数：" << graph->num_vertex << endl
		<< "边数：" << graph->num_edge << endl
		<< d << endl;
	for (int i = 0; i < graph->num_vertex; i++)
	{
		AdjacencyList_Vertex v = graph->vertex[i];
		Edge_Adj* e= v.head_edge;
		cout << v.no << "->";
		while (e)
		{
			cout << graph->vertex[e->index_vertex].no << "->";
			e = e->next;
		}
		cout << "NULL\n";
	}
}



















