#include "../API/Graph_matrix.h"


static int Index(int x)
{
	return x - 1;
}

void Graph_Init
(
	Graph_matrix* graph, //传入图对象
	int num_vertex,//传入顶点数量
	bool directed //指定有/无向图
)
{///初始化num_vertex * num_vertex的矩阵空间，边权值默认为0，num_vertex个空间的顶点集合
	try
	{
		if (!graph)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Graph is not exist" << std::endl;
		return;
	}
	graph->directed = directed;
	graph->num_edge = 0;
	graph->num_vertex = num_vertex;
	//memset(graph->vertex, 0, sizeof(Vertex_Matrix)*num_vertex);//顶点集合置空
	//memset(graph->edge, 0, sizeof(int) * maxsize * maxsize);
	//char n = 'A';
	//for (int i = 0; i < num_vertex; i++)
	//{
	//	graph->vertex[i].no = i ;
	//	//graph->vertex[Index(i)].name = n + 1;
	//	//for (int column = 0; column < num_vertex; column++)
	//	//	graph->edge[i][i]
	//}
	graph->vertex = new Vertex_Matrix[num_vertex];
	graph->state_visited = new bool[num_vertex];
	for (int i = 0; i < num_vertex; i++)
	{
		graph->vertex[i].no = i;
		graph->state_visited[i] = 0;
	}
	//int(*graph->edge)[num_vertex] = new int[num_vertex][num_vertex];
	graph->edge = new int* [num_vertex];///分配指针数组空间
	for (int i = 0; i < num_vertex; i++)
	{///分配二位数组空间
		graph->edge[i] = new int[num_vertex];
		for (int c = 0; c < num_vertex; c++)///初始化为全0
			graph->edge[i][c] = 0;
	}

}

void Graph_Show_Matrix(Graph_matrix* graph)
{
	using namespace std;
	string d = graph->directed == true ? "有向图" : "无向图";
	cout << "顶点数：" << graph->num_vertex << endl
		<< "边数：" << graph->num_edge << endl
		<< d << '\t';
	for (int i = 0; i < graph->num_vertex; i++)
		cout << i << '\t';
	cout << endl;
	for (int l = 0; l < graph->num_vertex; l++)
	{
		cout << l << '\t';
		for (int c = 0; c < graph->num_vertex; c++)
			cout << graph->edge[l][c] << '\t';
		cout << endl;
	}
	std::cout << std::endl;
}

static bool CheckEdge_Infinit(int weight)
{///	<0的边权值视为∞;
	if (weight <= 0)
		return true;
	return false;
}
void Graph_Edge_Add(Graph_matrix* graph, int no_origin, int no_destination, int weight)
{
	try
	{
		if (no_origin < 0 || no_origin >= graph->num_vertex)
			throw 1;
		if (no_destination < 0 || no_destination > graph->num_vertex)
			throw 2;
		if (!CheckEdge_Infinit(graph->edge[no_origin][no_destination]))//边存在时候不添加
			throw 3;
	}
	catch (int a)
	{
		if (a == 1)
		{
			std::cout << "Index Origin is out of range!" << std::endl;
			return;
		}
		if (a == 2)
		{
			std::cout << "Index Destination is out of range!" << std::endl;
			return;
		}
		if (a == 3)
		{
			std::cout << "Edge already Existed"<< std::endl;
			return;
		}
	}
	
	graph->edge[no_origin][no_destination] = weight;//添加从x到y的一条边
	if(graph->directed==false)//有向图对称
		graph->edge[no_destination][no_origin] = weight;
	graph->num_edge++;
}


static void Visit(Graph_matrix_Vertex& vertex)
{
	std::cout << vertex.no << ' ';
}

//重置访问状态，用于辅助遍历
static void Clear_VistiedState(Graph_matrix* graph)
{
	for (int i = 0; i < graph->num_vertex; i++)
		graph->state_visited[i] = 0;
}

//static bool History_Visited[maxsize];
void Graph_Traverse_DFS(Graph_matrix* graph, int no_vertex)
{
	//Clear_VistiedState(graph);///BUG
	Visit(graph->vertex[no_vertex]);
	graph->state_visited[no_vertex] = true;//标记为已访问
	for (int i = 0; i <= graph->num_vertex; i++)
	{
		if
			(
				!CheckEdge_Infinit(graph->edge[no_vertex][i]) //判断存在边
				&& 
				!graph->state_visited[i]//判断未访问
			)
			Graph_Traverse_DFS(graph, i);
	}

}

#include <queue>
void Graph_Traverse_BFS(Graph_matrix* graph, int no_vertex)
{
	Clear_VistiedState(graph);
#define Standard_Queue
#ifdef Standard_Queue
	std::queue<int> q;
	int front;
	q.push(no_vertex);
	while (!q.empty())
	{
		std::cout << q.front() << ' ';
		graph->state_visited[q.front()] = true;
		front = q.front();
		q.pop();
		for (int i = 0; i <= graph->num_vertex; i++)
		{
			if (!CheckEdge_Infinit(graph->edge[front][i]) && !graph->state_visited[i])
			{
				q.push(i);
				graph->state_visited[i] = true;
			}
		}
	}

#endif // Standard_Queue


}

void Graph_Destroy(Graph_matrix* graph)
{
	try
	{
		if (!graph)
			throw 1;
	}
	catch (...)
	{
		std::cout << "Graph Destroy Failed: Graph is not exist" << std::endl;
		return;
	}
	for (int i = 0; i < graph->num_vertex; i++)
		delete[] graph->edge[i];
	delete graph;
}







